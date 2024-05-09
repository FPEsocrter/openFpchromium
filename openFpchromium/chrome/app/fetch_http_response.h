#include <Windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>
#include <json/json.h>
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"
#include "cc/base/switches.h"
#include "base/command_line.h"
#include "fingerprint_to-bean.h"
#include "aes_diy_util.h"
#include "base\check.h"
#include <cstdlib>
#include <ctime>



#ifndef CHROME_APP_FETCH_HTTP_RESPONSE_H_
#define CHROME_APP_FETCH_HTTP_RESPONSE_H_
struct AipKey {
  uint32_t id;
  uint32_t webPort;
  uint32_t timestamp;
};
const char* aeskey = "oyb8ZvjMd+VvP/mQ";
const char*  aesEnKey = "KDHpjtQuysmq8rVO";
std::string sendHttpPostRequest(const int& webProt,
                                const LPCWSTR& path,
                                const char* strPtr) {

   HINTERNET hSession =
        WinHttpOpen(L"chromium_l", NULL, NULL, NULL, NULL);
    if (hSession == NULL) {
     WinHttpCloseHandle(hSession);
      return "";
    }

    HINTERNET hConnect =
        WinHttpConnect(hSession, L"127.0.0.1", (INTERNET_PORT)webProt, 0);
    if (hConnect == NULL) {
      WinHttpCloseHandle(hSession);
      WinHttpCloseHandle(hConnect);
      return "";
    }

    HINTERNET hRequest =
        WinHttpOpenRequest(hConnect, L"Post", path, NULL,
                           WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (hRequest == NULL) {
      WinHttpCloseHandle(hSession);
      WinHttpCloseHandle(hConnect);
      WinHttpCloseHandle(hRequest);

      return "";
    }
    std::string response;
    LPCWSTR headers = L"Content-Type: application/json\r\n";
      if (WinHttpAddRequestHeaders(hRequest, headers, wcslen(headers),
                                     WINHTTP_ADDREQ_FLAG_ADD)) {
            DWORD requestBodyLength = strlen(strPtr);
            if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                   (LPVOID)strPtr, requestBodyLength,
                                 requestBodyLength, 0)) {
              if (WinHttpReceiveResponse(hRequest, NULL)) {
                    DWORD bytesRead = 0;
                    const int bufferSize = 1024;
                    char buffer[bufferSize];

                    while (WinHttpReadData(hRequest, buffer, bufferSize,
                                           &bytesRead) &&
                           bytesRead > 0) {
                        response.append(buffer, bytesRead);
                    }
                }
            }
       }

       WinHttpCloseHandle(hSession);
       WinHttpCloseHandle(hConnect);
       WinHttpCloseHandle(hRequest);
    return response;
}

int jsonToInit(AipKey aipKey) {
    std::time_t timestamp = std::time(nullptr);
  
    std::string requestBody = "{\"timestamp\":" + std::to_string(timestamp) +
                            ",\"id\":" + std::to_string(aipKey.id) + "}";
    std::string aesRequestBody = diyEncrypt(requestBody, aeskey);
    //std::string aesRequestBody = requestBody;
    std::string jsonStr = sendHttpPostRequest(
        aipKey.webPort, L"launcher/getOpenFingerprint", aesRequestBody.c_str());
    
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;

    bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &root, &errors);
    if (parsingSuccessful) {

        bool statusCodeFlag = root.isMember("statusCode") &&
                    root["statusCode"].isInt() &&
                    root["statusCode"].asInt() == 200;
        
        if (!(statusCodeFlag && root.isMember("data")) ||
            root["data"].isNull()) {
            std::exit(0);
        }
        Json::Value data;
        if(root["data"].isString()){
            std::string strData = diyDecrypted(root["data"].asString(),aesEnKey);
            parsingSuccessful =
                reader->parse(strData.c_str(), strData.c_str() + strData.size(),
                              &data, &errors);
            if(!parsingSuccessful){
                std::exit(0);
            }
        }else{
            std::exit(0);
        }
        blink::fp::Fingerprint fingerprint=JsonToBean(data);
        if(fingerprint.init>0){
            base::SingletonFingerprint::Init(fingerprint);
            return 1;
        } else {
            std::exit(0);
        }
       
    } 
    
    delete reader;
    return 0;
}

AipKey getAipKey(const std::string& jsonStr) {
    AipKey aipKey;

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;
    Json::Value root;

    bool parsingSuccessful = reader->parse(
        jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &root, &errors);
    delete reader;

    if (parsingSuccessful) {
        if (root.isMember("id") && root["id"].isUInt()) {
            aipKey.id = root["id"].asUInt();
        }
        if (root.isMember("webPort") && root["webPort"].isUInt()) {
            aipKey.webPort = root["webPort"].asUInt();
        }
        if (root.isMember("timestamp") && root["timestamp"].isUInt()) {
            aipKey.timestamp = root["timestamp"].asUInt();
        }
    }

    return aipKey;
}

int FetchHttpResponse() {
    const base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
    if(!command_line->HasSwitch(cc::switches::kApiKey)){
         base::SingletonFingerprint::Init();
         return 0;    
    }
    const std::string apiKey =command_line->GetSwitchValueASCII(cc::switches::kApiKey);
    std::string strJsonAipKey = diyDecrypted(apiKey,aeskey);
    if (strJsonAipKey.empty()) {
         std::cout << "异常数据" << std::endl;
         std::exit(0);
        return 0;
    }
    AipKey aipKey = getAipKey(strJsonAipKey);

    uint32_t timeDifference = 0;
    auto timestamp= time(0);
    if (timestamp > aipKey.timestamp) {
        timeDifference = timestamp - aipKey.timestamp;
    }else{
        timeDifference = aipKey.timestamp -timestamp;
    }
       
    std::tm* localTime = std::localtime(&timestamp);  
    int hour = localTime->tm_hour;
    int min = localTime->tm_min;
    localTime->tm_hour = 0;
    localTime->tm_min = 0;
    localTime->tm_sec = 0;
  
    std::time_t midnightTimestamp = std::mktime(localTime);
    std::time_t midnightTimestamp2 = (midnightTimestamp + 1234567 + hour *789  + min/10)-aipKey.timestamp;

    if (timeDifference > 10000&&midnightTimestamp2!=0) {
        std::cout << "时间差超过10秒，退出程序。" << std::endl;
        std::exit(0);
    }
   if (jsonToInit(aipKey) < 1) {
         base::SingletonFingerprint::Init();
         return 0;
   }
   return 1;
}


#endif  // CHROME_APP_FETCH_HTTP_RESPONSE_H_