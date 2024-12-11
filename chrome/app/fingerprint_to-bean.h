#include <json/json.h>
#include "third_party/blink/public/common/fingerprint/fingerprint.h"


blink::fp::Fingerprint JsonToBean(const Json::Value& fingerprintJson) {
    blink::fp::Fingerprint fingerprint_;

    fingerprint_.init = 1;
    if (!fingerprintJson.isMember("init") || !fingerprintJson["init"].isInt() || fingerprintJson["init"] < 1) {
        return fingerprint_;
    }

    if( !fingerprintJson.isMember("ua")||!fingerprintJson["ua"].isObject()||
        !fingerprintJson.isMember("uaMetadata")||!fingerprintJson["uaMetadata"].isObject()||
        !fingerprintJson.isMember("timeZone")||!fingerprintJson["timeZone"].isObject()||
        !fingerprintJson.isMember("webRTC")||!fingerprintJson["webRTC"].isObject()||
        !fingerprintJson.isMember("location")||!fingerprintJson["location"].isObject()||
        !fingerprintJson.isMember("language")||!fingerprintJson["language"].isObject()||
        !fingerprintJson.isMember("resolution")||!fingerprintJson["resolution"].isObject()||
        !fingerprintJson.isMember("font")||!fingerprintJson["font"].isObject()||
        !fingerprintJson.isMember("canvas")||!fingerprintJson["canvas"].isObject()||
        !fingerprintJson.isMember("webGL")||!fingerprintJson["webGL"].isObject()||
        !fingerprintJson.isMember("gupGL")||!fingerprintJson["gupGL"].isObject()||
        !fingerprintJson.isMember("webGLDevice")||!fingerprintJson["webGLDevice"].isObject()||
        !fingerprintJson.isMember("audioContext")||!fingerprintJson["audioContext"].isObject()||
        !fingerprintJson.isMember("mediaEquipment")||!fingerprintJson["mediaEquipment"].isObject()||
        !fingerprintJson.isMember("clientRects")||!fingerprintJson["clientRects"].isObject()||
        !fingerprintJson.isMember("speechVoices")||!fingerprintJson["speechVoices"].isObject()||
        !fingerprintJson.isMember("resourceInfo")||!fingerprintJson["resourceInfo"].isObject()||
        !fingerprintJson.isMember("doNotTrack")||!fingerprintJson["doNotTrack"].isObject()||
        !fingerprintJson.isMember("openPort")||!fingerprintJson["openPort"].isObject()){
            return fingerprint_;
        }

    //consistency
        if (fingerprintJson.isMember("consistency") &&
            fingerprintJson["consistency"].isObject() &&
            fingerprintJson["consistency"].isMember("type") &&
            fingerprintJson["consistency"]["type"].isInt()){

        fingerprint_.consistency.type = fingerprintJson["consistency"]["type"].asInt();
        if(fingerprint_.consistency.type>1){
            if(!fingerprintJson["consistency"].isMember("urlList")||!fingerprintJson["consistency"]["urlList"].isArray()){
                return fingerprint_;
            }
            for (const auto& url : fingerprintJson["consistency"]["urlList"]) {
                if (url.isString()) {
                    fingerprint_.consistency.urlList.push_back(url.asString());
                }
            }
        }
        //return fingerprint_;
    }
    

    //ua
    if(!fingerprintJson["ua"].isMember("type")||!fingerprintJson["ua"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.ua.type = fingerprintJson["ua"]["type"].asInt();
    if(fingerprint_.ua.type>1){
        if(!fingerprintJson["ua"].isMember("userAgent")||!fingerprintJson["ua"]["userAgent"].isString()){
            return fingerprint_;
        }
        fingerprint_.ua.userAgent = fingerprintJson["ua"]["userAgent"].asString();
    }

    //uaMetadata
    if(!fingerprintJson["uaMetadata"].isMember("type")||!fingerprintJson["uaMetadata"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.uaMetadata.type = fingerprintJson["uaMetadata"]["type"].asInt();
    if(fingerprint_.uaMetadata.type>1){
        if(!fingerprintJson["uaMetadata"].isMember("brandVersionList")||!fingerprintJson["uaMetadata"]["brandVersionList"].isArray()||
            !fingerprintJson["uaMetadata"].isMember("brandFullVersionList")||!fingerprintJson["uaMetadata"]["brandFullVersionList"].isArray()||
            !fingerprintJson["uaMetadata"].isMember("fullVersion")||!fingerprintJson["uaMetadata"]["fullVersion"].isString()||
            !fingerprintJson["uaMetadata"].isMember("platform")||!fingerprintJson["uaMetadata"]["platform"].isString()||
            !fingerprintJson["uaMetadata"].isMember("platformVersion")||!fingerprintJson["uaMetadata"]["platformVersion"].isString()||
            !fingerprintJson["uaMetadata"].isMember("architecture")||!fingerprintJson["uaMetadata"]["architecture"].isString()||
            !fingerprintJson["uaMetadata"].isMember("model") ||!(fingerprintJson["uaMetadata"]["model"].isNull()||fingerprintJson["uaMetadata"]["model"].isString()) ||
            !fingerprintJson["uaMetadata"].isMember("mobile")||!fingerprintJson["uaMetadata"]["mobile"].isBool()||
            !fingerprintJson["uaMetadata"].isMember("bitness")||!fingerprintJson["uaMetadata"]["bitness"].isString()||
            !fingerprintJson["uaMetadata"].isMember("wow64")||!fingerprintJson["uaMetadata"]["wow64"].isBool()){
                return fingerprint_;
            }
        for (const auto& brand : fingerprintJson["uaMetadata"]["brandVersionList"]) {
            if (!brand.isMember("brand")||!brand["brand"].isString()||
                !brand.isMember("version")||!brand["version"].isString()){
                continue;
            }
            blink::UserAgentBrandVersion brandVersion;
            brandVersion.brand = brand["brand"].asString();
            brandVersion.version = brand["version"].asString();
            fingerprint_.uaMetadata.userAgentMetadata.brand_version_list.push_back(brandVersion);
        }
        for (const auto& brand : fingerprintJson["uaMetadata"]["brandFullVersionList"]) {
            if (!brand.isMember("brand")||!brand["brand"].isString()||
                !brand.isMember("version")||!brand["version"].isString()){
                continue;
            }
            blink::UserAgentBrandVersion brandVersion;
            brandVersion.brand = brand["brand"].asString();
            brandVersion.version = brand["version"].asString();
            fingerprint_.uaMetadata.userAgentMetadata.brand_full_version_list.push_back(brandVersion);
        }
        fingerprint_.uaMetadata.userAgentMetadata.full_version = fingerprintJson["uaMetadata"]["fullVersion"].asString();
        fingerprint_.uaMetadata.userAgentMetadata.platform = fingerprintJson["uaMetadata"]["platform"].asString();
        fingerprint_.uaMetadata.userAgentMetadata.platform_version = fingerprintJson["uaMetadata"]["platformVersion"].asString();
        fingerprint_.uaMetadata.userAgentMetadata.architecture = fingerprintJson["uaMetadata"]["architecture"].asString();
        if (!fingerprintJson["uaMetadata"]["model"].isNull()) {
            fingerprint_.uaMetadata.userAgentMetadata.model = fingerprintJson["uaMetadata"]["model"].asString();
        }
       
        fingerprint_.uaMetadata.userAgentMetadata.mobile = fingerprintJson["uaMetadata"]["mobile"].asBool();
        fingerprint_.uaMetadata.userAgentMetadata.bitness = fingerprintJson["uaMetadata"]["bitness"].asString();
        fingerprint_.uaMetadata.userAgentMetadata.wow64 = fingerprintJson["uaMetadata"]["wow64"].asBool();
    }
     
    // Populate TimeZone
    if(!fingerprintJson["timeZone"].isMember("type")||!fingerprintJson["timeZone"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.timeZone.type = fingerprintJson["timeZone"]["type"].asInt();
    if (fingerprint_.timeZone.type>1) {
        if (!fingerprintJson["timeZone"].isMember("gmt") || !fingerprintJson["timeZone"]["gmt"].isString()) {
            return fingerprint_;
        }
        fingerprint_.timeZone.gmt = fingerprintJson["timeZone"]["gmt"].asString();
    }

    // Populate WebRTC
    if (!fingerprintJson["webRTC"].isMember("type")|| !fingerprintJson["webRTC"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.webRTC.type = fingerprintJson["webRTC"]["type"].asInt();
    if (fingerprint_.webRTC.type ==2) {
        if (!fingerprintJson["webRTC"].isMember("privateIp") || !fingerprintJson["webRTC"]["privateIp"].isString()||
            !fingerprintJson["webRTC"].isMember("publicIp") || !fingerprintJson["webRTC"]["publicIp"].isString()) {
            return fingerprint_;
        }
        fingerprint_.webRTC.privateIp = fingerprintJson["webRTC"]["privateIp"].asString();
        fingerprint_.webRTC.publicIp = fingerprintJson["webRTC"]["publicIp"].asString();
    }

    // Populate Location3
    if (!fingerprintJson["location"].isMember("type")|| !fingerprintJson["location"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.location.type = fingerprintJson["location"]["type"].asInt();
    if (fingerprint_.location.type>1 ) {
        if (!fingerprintJson["location"].isMember("latitude") || !fingerprintJson["location"]["latitude"].isDouble() ||
            !fingerprintJson["location"].isMember("longitude") ||!fingerprintJson["location"]["longitude"].isDouble() ||
            !fingerprintJson["location"].isMember("accuracy") || !fingerprintJson["location"]["accuracy"].isDouble()||
            !fingerprintJson["location"].isMember("permissions") || !fingerprintJson["location"]["permissions"].isBool()) {
            return fingerprint_;
        }
        fingerprint_.location.latitude = fingerprintJson["location"]["latitude"].asDouble();
        fingerprint_.location.longitude = fingerprintJson["location"]["longitude"].asDouble();
        fingerprint_.location.accuracy = fingerprintJson["location"]["accuracy"].asDouble();
        fingerprint_.location.permissions = fingerprintJson["location"]["permissions"].asBool();
    }
    
    // Populate Language
    if (!fingerprintJson["language"].isMember("type") || !fingerprintJson["language"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.language.type = fingerprintJson["language"]["type"].asInt();
    if (fingerprint_.language.type>1) {
        if (!fingerprintJson["language"].isMember("interfaceLanguage") ||!fingerprintJson["language"]["interfaceLanguage"].isString() ||
            !fingerprintJson["language"].isMember("languages") || !fingerprintJson["language"]["languages"].isArray()) {
            return fingerprint_;
        }
        fingerprint_.language.interfaceLanguage = fingerprintJson["language"]["interfaceLanguage"].asString();
        for (const auto& lang : fingerprintJson["language"]["languages"])
            if (lang.isString()) {
                fingerprint_.language.languages.push_back(lang.asString());
            }
    }

    // Populate Resolution
    if (!fingerprintJson["resolution"].isMember("type") || !fingerprintJson["resolution"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.resolution.type = fingerprintJson["resolution"]["type"].asInt();
    if (fingerprint_.resolution.type>1 ) {
        if (!fingerprintJson["resolution"].isMember("windowWidth") || !fingerprintJson["resolution"]["windowWidth"].isInt() ||
            !fingerprintJson["resolution"].isMember("windowHeight") ||!fingerprintJson["resolution"]["windowHeight"].isInt() ||
            !fingerprintJson["resolution"].isMember("monitorWidth") ||!fingerprintJson["resolution"]["monitorWidth"].isInt() || 
            !fingerprintJson["resolution"].isMember("monitorHeight")||!fingerprintJson["resolution"]["monitorHeight"].isInt()) {
            return fingerprint_;
        }
        fingerprint_.resolution.windowWidth = fingerprintJson["resolution"]["windowWidth"].asInt();
        fingerprint_.resolution.windowHeight = fingerprintJson["resolution"]["windowHeight"].asInt();
        fingerprint_.resolution.monitorWidth = fingerprintJson["resolution"]["monitorWidth"].asInt();
        fingerprint_.resolution.monitorHeight = fingerprintJson["resolution"]["monitorHeight"].asInt();
    }

    //Font
    if (!fingerprintJson["font"].isMember("type")|| !fingerprintJson["font"]["type"].isInt()) {
        return fingerprint_;
    }

    fingerprint_.font.type = fingerprintJson["font"]["type"].asInt();

    if (fingerprint_.font.type>1) {
        if (!fingerprintJson["font"].isMember("fontMap") || !fingerprintJson["font"]["fontMap"].isObject()) {
            return fingerprint_;
        }
        const Json::Value& fontMap =  fingerprintJson["font"]["fontMap"];
        int maxid = 0;
        for (const auto& key : fontMap.getMemberNames()) {
            const Json::Value& value = fontMap[key];
            if(value.isMember("id")&&value["id"].isInt()&&value["id"].asInt()==-1){
                blink::fp::FontInfo fontInfo;
                fontInfo.id = value["id"].asInt();
                fingerprint_.font.fontMap[key] = fontInfo;
                continue;
            }

            if (
                !value.isMember("width")  || !value["width"].isDouble()||
                !value.isMember("height") || !value["height"].isDouble()||
                !value.isMember("actualBoundingBoxAscent")|| !value["actualBoundingBoxAscent"].isDouble()||
                !value.isMember("actualBoundingBoxDescent")|| !value["actualBoundingBoxDescent"].isDouble()||
                !value.isMember("actualBoundingBoxLeft")|| !value["actualBoundingBoxLeft"].isDouble()||
                !value.isMember("actualBoundingBoxRight")|| !value["actualBoundingBoxRight"].isDouble()||
                !value.isMember("fontBoundingBoxAscent")|| !value["fontBoundingBoxAscent"].isDouble()||
                !value.isMember("fontBoundingBoxDescent")|| !value["fontBoundingBoxDescent"].isDouble()||
                !value.isMember("filePaths")|| !value["filePaths"].isArray()) {
                continue;
            }

            blink::fp::FontInfo fontInfo;
            fontInfo.id = value["id"].asInt();
            fontInfo.width = value["width"].asDouble();
            fontInfo.height = value["height"].asDouble();
            fontInfo.actualBoundingBoxAscent = value["actualBoundingBoxAscent"].asDouble();
            fontInfo.actualBoundingBoxDescent = value["actualBoundingBoxDescent"].asDouble();
            fontInfo.actualBoundingBoxLeft = value["actualBoundingBoxLeft"].asDouble();
            fontInfo.actualBoundingBoxRight = value["actualBoundingBoxRight"].asDouble();
            fontInfo.fontBoundingBoxAscent = value["fontBoundingBoxAscent"].asDouble();
            fontInfo.fontBoundingBoxDescent = value["fontBoundingBoxDescent"].asDouble();
            for (const auto& path : value["filePaths"]) {
                if (path.isString()) {
                    fontInfo.filePaths.push_back(path.asString());
                }
            }
            if(fontInfo.id>maxid){
                maxid = fontInfo.id+1;
            }
            fingerprint_.font.fontMap[key] = fontInfo;
            fingerprint_.font.fontIdMap[fontInfo.id] = key;
       } 
       fingerprint_.font.maxId = maxid;
    }
        

    
    // Populate Canvas
    if (!fingerprintJson["canvas"].isMember("type")|| !fingerprintJson["canvas"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.canvas.type = fingerprintJson["canvas"]["type"].asInt();
    if(fingerprint_.canvas.type>1){
         if(!fingerprintJson["canvas"].isMember("coloredPointList")||!fingerprintJson["canvas"]["coloredPointList"].isArray()){
             return fingerprint_;
         }
        for (const auto& point : fingerprintJson["canvas"]["coloredPointList"]) {
            if (!point.isMember("row")|| !point["row"].isInt()||
                !point.isMember("column")|| !point["column"].isInt()||
                !point.isMember("red")||  !point["red"].isInt()||
                !point.isMember("green")|| !point["green"].isInt()||
                !point.isMember("blue")|| !point["blue"].isInt()||
                !point.isMember("alpha")||!point["alpha"].isInt()){
                    continue;
                }
                blink::fp::ColoredPoint coloredPoint;
                coloredPoint.row = point["row"].asInt();
                coloredPoint.column = point["column"].asInt();
                coloredPoint.red = point["red"].asInt();
                coloredPoint.green = point["green"].asInt();
                coloredPoint.blue = point["blue"].asInt();
                coloredPoint.alpha = point["alpha"].asInt();
                fingerprint_.canvas.coloredPointList.push_back(coloredPoint);
            }
    }

    
    // Populate WebGL
    if (!fingerprintJson["webGL"].isMember("type")|| !fingerprintJson["webGL"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.webGL.type = fingerprintJson["webGL"]["type"].asInt();
    if(fingerprint_.webGL.type>1){
         if(!fingerprintJson["webGL"].isMember("coloredPointList")||!fingerprintJson["webGL"]["coloredPointList"].isArray()){
             return fingerprint_;
         }
         for (const auto& point : fingerprintJson["webGL"]["coloredPointList"]) {
            if (!point.isMember("row")|| !point["row"].isInt()||
                !point.isMember("column")|| !point["column"].isInt()||
                !point.isMember("red")||  !point["red"].isInt()||
                !point.isMember("green")|| !point["green"].isInt()||
                !point.isMember("blue")|| !point["blue"].isInt()||
                !point.isMember("alpha")||!point["alpha"].isInt()){
                    continue;
                }
                blink::fp::ColoredPoint coloredPoint;
                coloredPoint.row = point["row"].asInt();
                coloredPoint.column = point["column"].asInt();
                coloredPoint.red = point["red"].asInt();
                coloredPoint.green = point["green"].asInt();
                coloredPoint.blue = point["blue"].asInt();
                coloredPoint.alpha = point["alpha"].asInt();
                fingerprint_.webGL.coloredPointList.push_back(coloredPoint);
            }
    }

    // Populate gupGL
    if (!fingerprintJson["gupGL"].isMember("type")|| !fingerprintJson["gupGL"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.gupGL.type = fingerprintJson["gupGL"]["type"].asInt();
    if(fingerprint_.gupGL.type>1){
         if(!fingerprintJson["gupGL"].isMember("coloredPointList")||!fingerprintJson["gupGL"]["coloredPointList"].isArray()){
             return fingerprint_;
         }
         for (const auto& point : fingerprintJson["gupGL"]["coloredPointList"]) {
            if (!point.isMember("row")|| !point["row"].isInt()||
                !point.isMember("column")|| !point["column"].isInt()||
                !point.isMember("red")||  !point["red"].isInt()||
                !point.isMember("green")|| !point["green"].isInt()||
                !point.isMember("blue")|| !point["blue"].isInt()||
                !point.isMember("alpha")||!point["alpha"].isInt()){
                    continue;
                }
                blink::fp::ColoredPoint coloredPoint;
                coloredPoint.row = point["row"].asInt();
                coloredPoint.column = point["column"].asInt();
                coloredPoint.red = point["red"].asInt();
                coloredPoint.green = point["green"].asInt();
                coloredPoint.blue = point["blue"].asInt();
                coloredPoint.alpha = point["alpha"].asInt();
                fingerprint_.gupGL.coloredPointList.push_back(coloredPoint);
            }
    }

    // Populate webGLDevice
    if (!fingerprintJson["webGLDevice"].isMember("type")||!fingerprintJson["webGLDevice"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.webGLDevice.type = fingerprintJson["webGLDevice"]["type"].asInt();
    if(fingerprint_.webGLDevice.type>1){
            if (!fingerprintJson["webGLDevice"].isMember("vendors")||!fingerprintJson["webGLDevice"]["vendors"].isString()||
                !fingerprintJson["webGLDevice"].isMember("renderer")||!fingerprintJson["webGLDevice"]["renderer"].isString()||
                !fingerprintJson["webGLDevice"].isMember("gpuVendors")||!fingerprintJson["webGLDevice"]["gpuVendors"].isString()||
                !fingerprintJson["webGLDevice"].isMember("gpuArchitecture")||!fingerprintJson["webGLDevice"]["gpuArchitecture"].isString() ){
                    return fingerprint_;
                }
            fingerprint_.webGLDevice.vendors = fingerprintJson["webGLDevice"]["vendors"].asString();
            fingerprint_.webGLDevice.renderer = fingerprintJson["webGLDevice"]["renderer"].asString();
            fingerprint_.webGLDevice.gpuVendors = fingerprintJson["webGLDevice"]["gpuVendors"].asString();
            fingerprint_.webGLDevice.gpuArchitecture = fingerprintJson["webGLDevice"]["gpuArchitecture"].asString();
    }

    // Populate AudioContext
    if (!fingerprintJson["audioContext"].isMember("type")||!fingerprintJson["audioContext"]["noise"].isArray()){
        return fingerprint_;
    }
    fingerprint_.audioContext.type = fingerprintJson["audioContext"]["type"].asInt();
    if (fingerprint_.audioContext.type>1)
    {
        if (!fingerprintJson["audioContext"].isMember("noise")||!fingerprintJson["audioContext"]["noise"].isArray()){
                return fingerprint_;
            }
        for (const auto& noise : fingerprintJson["audioContext"]["noise"]){
                if(noise.isDouble()){
                fingerprint_.audioContext.noise.push_back(noise.asDouble());     
                }
        }
                
    }


    // Populate MediaEquipment
    if (!fingerprintJson["mediaEquipment"].isMember("type")||!fingerprintJson["mediaEquipment"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.mediaEquipment.type = fingerprintJson["mediaEquipment"]["type"].asInt();
    if(fingerprint_.mediaEquipment.type >0){
        if(!fingerprintJson["mediaEquipment"].isMember("list")||!fingerprintJson["mediaEquipment"]["list"].isArray()){
            return fingerprint_;
        }
        for (const auto& equip : fingerprintJson["mediaEquipment"]["list"]) {
            if (!equip.isMember("type")|| !equip["type"].isInt()||
                !equip.isMember("label")||  !equip["label"].isString()||
                !equip.isMember("deviceId")||!equip["deviceId"].isString()||
                !equip.isMember("groupId")|| !equip["groupId"].isString()){
                    continue;
                }
                blink::fp::MediaEquipmentInfo equipInfo;
                equipInfo.type = equip["type"].asInt();
                equipInfo.label = equip["label"].asString();
                equipInfo.deviceId = equip["deviceId"].asString();
                equipInfo.groupId = equip["groupId"].asString();
                fingerprint_.mediaEquipment.list.push_back(equipInfo);
            }
    }

    // Populate ClientRects
    if(!fingerprintJson["clientRects"].isMember("type")||!fingerprintJson["clientRects"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.clientRects.type = fingerprintJson["clientRects"]["type"].asInt();
    if(fingerprint_.clientRects.type>1){
        if (!fingerprintJson["clientRects"].isMember("x")|| !fingerprintJson["clientRects"]["x"].isDouble()||
            !fingerprintJson["clientRects"].isMember("y")||  !fingerprintJson["clientRects"]["y"].isDouble()||
            !fingerprintJson["clientRects"].isMember("width")|| !fingerprintJson["clientRects"]["width"].isDouble()||
            !fingerprintJson["clientRects"].isMember("height")||!fingerprintJson["clientRects"]["height"].isDouble()){
                    return fingerprint_;
            }
        fingerprint_.clientRects.x = fingerprintJson["clientRects"]["x"].asDouble();
        fingerprint_.clientRects.y = fingerprintJson["clientRects"]["y"].asDouble();
        fingerprint_.clientRects.width = fingerprintJson["clientRects"]["width"].asDouble();
        fingerprint_.clientRects.height = fingerprintJson["clientRects"]["height"].asDouble();
    }

    // Populate SpeechVoices
    if (!fingerprintJson["speechVoices"].isMember("type")|| !fingerprintJson["speechVoices"]["type"].isInt()){
        return fingerprint_;
    }
    fingerprint_.speechVoices.type = fingerprintJson["speechVoices"]["type"].asInt();
    if (fingerprint_.speechVoices.type>1) {
        if (!fingerprintJson["speechVoices"].isMember("list") || !fingerprintJson["speechVoices"]["list"].isArray()) {
            return fingerprint_;
        }
        for (const auto& voice : fingerprintJson["speechVoices"]["list"]) {
            if ( !voice.isMember("voiceUri")|| !voice["voiceUri"].isString()||
                !voice.isMember("name")||  !voice["name"].isString()|| 
                !voice.isMember("lang")||!voice["lang"].isString()||
                !voice.isMember("isLocalService")||!voice["isLocalService"].isBool()||
                !voice.isMember("isDefault")||!voice["isDefault"].isBool() ) {
                continue;
            }
            blink::fp::SpeechVoicesInfo voiceInfo;
            voiceInfo.voiceUri = voice["voiceUri"].asString();
            voiceInfo.name = voice["name"].asString();
            voiceInfo.lang = voice["lang"].asString();
            voiceInfo.isLocalService = voice["isLocalService"].asBool();
            voiceInfo.isDefault = voice["isDefault"].asBool();
            fingerprint_.speechVoices.list.push_back(voiceInfo);
        }
        
    }

    //ResourceInfo
    if (!fingerprintJson["resourceInfo"].isMember("type")|| !fingerprintJson["resourceInfo"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.resourceInfo.type =fingerprintJson["resourceInfo"]["type"].asInt();
    if (fingerprint_.resourceInfo.type>1) {
        if (!fingerprintJson["resourceInfo"].isMember("cpu") || !fingerprintJson["resourceInfo"]["cpu"].isInt()||
            !fingerprintJson["resourceInfo"].isMember("memory") || !fingerprintJson["resourceInfo"]["memory"].isDouble()) {
            return fingerprint_;
        }
        fingerprint_.resourceInfo.cpu = fingerprintJson["resourceInfo"]["cpu"].asInt();
        fingerprint_.resourceInfo.memory = fingerprintJson["resourceInfo"]["memory"].asDouble();
    }
    
    //DoNotTrack
    if (!fingerprintJson["doNotTrack"].isMember("type")|| !fingerprintJson["doNotTrack"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.doNotTrack.type = fingerprintJson["doNotTrack"]["type"].asInt();
    if (fingerprint_.doNotTrack.type>1) {
        fingerprint_.doNotTrack.flag = true;
    }else{
        fingerprint_.doNotTrack.flag = false;
    }

    //OpenPort
    if (!fingerprintJson["openPort"].isMember("type")|| !fingerprintJson["openPort"]["type"].isInt()) {
        return fingerprint_;
    }
    fingerprint_.openPort.type = fingerprintJson["openPort"]["type"].asInt();
    if (fingerprint_.openPort.type>1) {
        if (!fingerprintJson["openPort"].isMember("list") || !fingerprintJson["openPort"]["list"].isArray()||
            !fingerprintJson["openPort"].isMember("url") || !fingerprintJson["openPort"]["url"].isString()) {
            return fingerprint_;
        }
        for (const auto& port : fingerprintJson["openPort"]["list"]) {
            if (port.isInt()) {
                fingerprint_.openPort.openPort.push_back(port.asInt());
            }
        }
         fingerprint_.openPort.url=fingerprintJson["openPort"]["url"].asString();
    }
    fingerprint_.init = fingerprintJson["init"].asInt();
    return fingerprint_;
}