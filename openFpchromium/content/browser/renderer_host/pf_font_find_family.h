#ifndef CONTENT_BROWSER_RENDERER_HOST_PF_FONT_FIND_FAMILY_H_
#define CONTENT_BROWSER_RENDERER_HOST_PF_FONT_FIND_FAMILY_H_

#include <string>
#include <stdint.h>
#include "base/containers/flat_map.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"



// #include <iostream>
// #include <fstream>

std::u16string toLower(const std::u16string& str) {
  std::u16string lowerStr;
  for (char16_t c : str) {
    if (c >= u'Ａ' && c <= u'Ｚ') {
      lowerStr.push_back(c + (u'ａ' - u'Ａ'));
    } else if (c >= u'A' && c <= u'Z') {
      lowerStr.push_back(c + (u'a' - u'A'));
    } else {
      lowerStr.push_back(c);
    }
  }
  return lowerStr;
}

std::string U16StringToUTF8(const std::u16string& u16str) {
    std::u16string result = toLower(u16str);
    std::string str;
    base::UTF16ToUTF8(result.data(), result.size(), &str);
    return str;
}



UINT32 fpFindFamily(const std::u16string& family_name, UINT32 family_index) {
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1){
        base::flat_map<std::string, blink::fp::FontInfo> fontMap = t_fingerprint.font.fontMap;
        std::string font = U16StringToUTF8(family_name);
        auto iter = fontMap.find(font);
        if (iter != fontMap.end()) {
          blink::fp::FontInfo fontInfo = iter->second;
          if (fontInfo.id>-1) {
            return fontInfo.id;
          }else{
              
              return family_index;
          }
        }else{
            // if(family_index==51){
            //     std::ofstream outputFile("D://output.txt", std::ios::app);
            //     if (outputFile.is_open()) {
            //         outputFile <<font<<":"<<family_index<<std::endl;
            //         outputFile.close();  
            //     }
            // }
            
            return UINT32_MAX; //UINT32_MAX
        }
    }
    return family_index; 
}


UINT32 fpGetFamilyCount(UINT32 count){
    // base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    // blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    // if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type ==2){
    //     return t_fingerprint.font.maxId;
    // }
    return count; 
}


UINT32 fpGetFontFileHandles(UINT32 index){
    // if(UINT32_MAX==index){
    //     return UINT32_MAX;
    // }
    // base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    // blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    // if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type ==2){
    //     base::flat_map<int,std::string> fontIdMap = t_fingerprint.font.fontIdMap;
    //     auto iter = fontIdMap.find(index);
    //     if (iter != fontIdMap.end()) {
    //         return (UINT32)t_fingerprint.font.defaultId;
    //     }else{
    //         return index;
    //     }
    // }
    return index; 
}

#endif  // CONTENT_BROWSER_RENDERER_HOST_PF_FONT_FIND_FAMILY_H_
/*
#include <iostream>
#include <fstream>
std::ofstream outputFile("D://output.txt", std::ios::app);
 if (outputFile.is_open()) {
       outputFile << "\""+ font+"\":\"\"" << std::endl;
       outputFile.close();  }
*/

