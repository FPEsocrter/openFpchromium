// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/public/common/fingerprint/fingerprint_mojom_traits.h"
#include "third_party/blink/public/common/user_agent/user_agent_mojom_traits.h"
#include <string>

namespace mojo {

bool StructTraits<blink::mojom::ConsistencyDataView, ::blink::fp::Consistency>::Read(
    blink::mojom::ConsistencyDataView data, ::blink::fp::Consistency* out) {

    out->type = data.type();

    std::vector<std::string> urlList;
    if (!data.ReadUrlList(&urlList)) {
        return false;
    }
    out->urlList = std::move(urlList);

    return true;
}

bool StructTraits<blink::mojom::UADataView, ::blink::fp::UA>::Read(
    blink::mojom::UADataView data, ::blink::fp::UA* out) {

    out->type = data.type();

    if (!data.ReadUserAgent(&out->userAgent)) {
        return false;
    }

    return true;
}

bool StructTraits<blink::mojom::UaMetadataDataView, ::blink::fp::UaMetadata>::Read(
    blink::mojom::UaMetadataDataView data, ::blink::fp::UaMetadata* out) {

    out->type = data.type();

    if (!data.ReadUserAgentMetadata(&out->userAgentMetadata)) {
        return false;
    }

    return true;
}

bool StructTraits<blink::mojom::WebRTCDataView, ::blink::fp::WebRTC>::Read(
    blink::mojom::WebRTCDataView data, ::blink::fp::WebRTC* out) {

    out->type = data.type();

    if (!data.ReadPrivateIp(&out->privateIp)) {
        return false;
    }

    if (!data.ReadPublicIp(&out->publicIp)) {
        return false;
    }
   
    return true;
}

bool StructTraits<blink::mojom::TimeZoneDataView, ::blink::fp::TimeZone>::Read(
    blink::mojom::TimeZoneDataView data, ::blink::fp::TimeZone* out) {

    out->type = data.type();

    if (!data.ReadGmt(&out->gmt)) {
        return false;
    }
  
    return true;
}

bool StructTraits<blink::mojom::LocationDataView, ::blink::fp::Location>::Read(
    blink::mojom::LocationDataView data, ::blink::fp::Location* out) {
    out->type = data.type();
    out->permissions=data.permissions();
    out->latitude = data.latitude();

    out->longitude = data.longitude();

    out->accuracy = data.accuracy();

    return true;
}

bool StructTraits<blink::mojom::LanguageDataView, ::blink::fp::Language>::Read(
    blink::mojom::LanguageDataView data, ::blink::fp::Language* out) {

    out->type = data.type();

    if (!data.ReadInterfaceLanguage(&out->interfaceLanguage)) {
        return false;
    }
    
    std::vector<std::string> languages;
    if (!data.ReadLanguages(&languages)) {
        return false;
    }
    out->languages = std::move(languages);
    
    return true;
}

bool StructTraits<blink::mojom::ResolutionDataView, ::blink::fp::Resolution>::Read(
    blink::mojom::ResolutionDataView data, ::blink::fp::Resolution* out) {

    out->type = data.type();

    out->windowWidth = data.windowWidth();

    out->windowHeight = data.windowHeight();

    out->monitorWidth = data.monitorWidth();

    out->monitorHeight = data.monitorHeight();

    return true;
}

bool StructTraits<blink::mojom::FontInfoDataView, ::blink::fp::FontInfo>::Read(
    blink::mojom::FontInfoDataView data, ::blink::fp::FontInfo* out) {

    out->id = data.id();    
    out->width = data.width();
    out->height = data.height();
    out->actualBoundingBoxAscent = data.actualBoundingBoxAscent();
    out->actualBoundingBoxDescent = data.actualBoundingBoxDescent();
    out->actualBoundingBoxLeft = data.actualBoundingBoxLeft();
    out->actualBoundingBoxRight = data.actualBoundingBoxRight();
    out->fontBoundingBoxAscent = data.fontBoundingBoxAscent();
    out->fontBoundingBoxDescent = data.fontBoundingBoxDescent();

    std::vector<std::string> filePaths;
    if (!data.ReadFilePaths(&filePaths)) {
        return false;
    }
    out->filePaths = std::move(filePaths);
   
    return true;
}

bool StructTraits<blink::mojom::FontDataView, ::blink::fp::Font>::Read(
    blink::mojom::FontDataView data, ::blink::fp::Font* out) {

    out->type = data.type();
    out->maxId = data.maxId();
    out->defaultId = data.defaultId();
    if (!data.ReadDefaultName(&out->defaultName)) {
        return false;
    }
    std::vector<std::string> filePaths;
    if (!data.ReadDefaultPaths(&filePaths)) {
        return false;
    }
    out->defaultPaths = std::move(filePaths);

    base::flat_map<std::string, ::blink::fp::FontInfo> fontMap;
    if (!data.ReadFontMap(&fontMap)) {
        return false;
    }
    out->fontMap = std::move(fontMap);

    base::flat_map<int, std::string> fontIdMap;
    if (!data.ReadFontIdMap(&fontIdMap)) {
        return false;
    }
    out->fontIdMap = std::move(fontIdMap);


    return true;
}

bool StructTraits<blink::mojom::ColoredPointDataView, ::blink::fp::ColoredPoint>::Read(
    blink::mojom::ColoredPointDataView data, ::blink::fp::ColoredPoint* out) {

    out->row = data.row();

    out->column = data.column();

    out->red = data.red();

    out->green = data.green();

    out->blue = data.blue();

    out->alpha = data.alpha();

    return true;
}

bool StructTraits<blink::mojom::CanvasDataView, ::blink::fp::Canvas>::Read(
    blink::mojom::CanvasDataView data, ::blink::fp::Canvas* out) {

    out->type = data.type();

    std::vector<::blink::fp::ColoredPoint> coloredPointList;
    if (!data.ReadColoredPointList(&coloredPointList)) {
        return false;
    }
    out->coloredPointList = std::move(coloredPointList);

    return true;
}

bool StructTraits<blink::mojom::WebGLDeviceDataView, ::blink::fp::WebGLDevice>::Read(
    blink::mojom::WebGLDeviceDataView data, ::blink::fp::WebGLDevice* out) {

    out->type = data.type();

    if (!data.ReadVendors(&out->vendors)) {
        return false;
    }

    if (!data.ReadRenderer(&out->renderer)) {
        return false;
    }

    if (!data.ReadGpuVendors(&out->gpuVendors)) {
        return false;
    }
    
    if (!data.ReadGpuArchitecture(&out->gpuArchitecture)) {
        return false;
    }
    return true;
}

bool StructTraits<blink::mojom::AudioContextDataView, ::blink::fp::AudioContext>::Read(
    blink::mojom::AudioContextDataView data, ::blink::fp::AudioContext* out) {
    out->type = data.type();

    std::vector<double> noise;
    if (!data.ReadNoise(&noise)) {
        return false;
    }
    out->noise = std::move(noise);

    return true;
}

bool StructTraits<blink::mojom::MediaEquipmentInfoDataView, ::blink::fp::MediaEquipmentInfo>::Read(
    blink::mojom::MediaEquipmentInfoDataView data, ::blink::fp::MediaEquipmentInfo* out) {
    out->type = data.type();    
    if (!data.ReadLabel(&out->label)) {
        return false;
    }

    if (!data.ReadDeviceId(&out->deviceId)) {
        return false;
    }

    if (!data.ReadGroupId(&out->groupId)) {
        return false;
    }
    
    return true;
}

bool StructTraits<blink::mojom::MediaEquipmentDataView, ::blink::fp::MediaEquipment>::Read(
    blink::mojom::MediaEquipmentDataView data, ::blink::fp::MediaEquipment* out) {

    out->type = data.type();

    std::vector<::blink::fp::MediaEquipmentInfo> list;
    if (!data.ReadList(&list)) {
        return false;
    }
    out->list = std::move(list);

    return true;
}

bool StructTraits<blink::mojom::ClientRectsDataView, ::blink::fp::ClientRects>::Read(
    blink::mojom::ClientRectsDataView data, ::blink::fp::ClientRects* out) {

    out->type = data.type();

    out->x = data.x();

    out->y = data.y();

    out->width = data.width();

    out->height = data.height();

    return true;
}

bool StructTraits<blink::mojom::SpeechVoicesInfoDataView, ::blink::fp::SpeechVoicesInfo>::Read(
    blink::mojom::SpeechVoicesInfoDataView data, ::blink::fp::SpeechVoicesInfo* out) {

    if (!data.ReadVoiceUri(&out->voiceUri)) {
        return false;
    }

    if (!data.ReadName(&out->name)) {
        return false;
    }
      
    if (!data.ReadLang(&out->lang)) {
        return false;
    }

    out->isLocalService = data.isLocalService();

    out->isDefault = data.isDefault();

    return true;
}

bool StructTraits<blink::mojom::SpeechVoicesDataView, ::blink::fp::SpeechVoices>::Read(
    blink::mojom::SpeechVoicesDataView data, ::blink::fp::SpeechVoices* out) {
    out->type = data.type();

    std::vector<::blink::fp::SpeechVoicesInfo> list;
    if (!data.ReadList(&list)) {
        return false;
    }
    out->list = std::move(list);

    return true;
}

bool StructTraits<blink::mojom::ResourceInfoDataView, ::blink::fp::ResourceInfo>::Read(
    blink::mojom::ResourceInfoDataView data, ::blink::fp::ResourceInfo* out) {
    out->type = data.type();

    out->cpu = data.cpu();

    out->memory = data.memory();

    return true;
}

bool StructTraits<blink::mojom::DoNotTrackDataView, ::blink::fp::DoNotTrack>::Read(
    blink::mojom::DoNotTrackDataView data, ::blink::fp::DoNotTrack* out) {
    out->type = data.type();

    out->flag = data.flag();

    return true;
}

bool StructTraits<blink::mojom::OpenPortDataView, ::blink::fp::OpenPort>::Read(
    blink::mojom::OpenPortDataView data, ::blink::fp::OpenPort* out) {
    out->type = data.type();

    std::vector<int> openPort;
    if (!data.ReadOpenPort(&openPort)) {
        return false;
    }
    out->openPort = std::move(openPort);

    if (!data.ReadUrl(&out->url)) {
        return false;
    }

    return true;
}


bool StructTraits<blink::mojom::FingerprintDataView, ::blink::fp::Fingerprint>::Read(
blink::mojom::FingerprintDataView data, ::blink::fp::Fingerprint* out) {
out->init = data.init();

if (!data.ReadConsistency(&out->consistency)) {
    return false;
}

if (!data.ReadUa(&out->ua)) {
    return false;
}

if (!data.ReadUaMetadata(&out->uaMetadata)) {
    return false;
}

if (!data.ReadTimeZone(&out->timeZone)) {
    return false;
}

if (!data.ReadWebRtc(&out->webRTC)) {
    return false;
}

if (!data.ReadLocation(&out->location)) {
    return false;
}

if (!data.ReadLanguage(&out->language)) {
    return false;
}

if (!data.ReadResolution(&out->resolution)) {
    return false;
}

if (!data.ReadFont(&out->font)) {
    return false;
}

if (!data.ReadCanvas(&out->canvas)) {
    return false;
}

if (!data.ReadWebGl(&out->webGL)) {
    return false;
}

if (!data.ReadGupGl(&out->gupGL)) {
    return false;
}

if (!data.ReadWebGlDevice(&out->webGLDevice)) {
    return false;
}

if (!data.ReadAudioContext(&out->audioContext)) {
    return false;
}

if (!data.ReadMediaEquipment(&out->mediaEquipment)) {
    return false;
}

if (!data.ReadClientRects(&out->clientRects)) {
    return false;
}

if (!data.ReadSpeechVoices(&out->speechVoices)) {
    return false;
}

if (!data.ReadResourceInfo(&out->resourceInfo)) {
    return false;
}

if (!data.ReadDoNotTrack(&out->doNotTrack)) {
    return false;
}

if (!data.ReadOpenPort(&out->openPort)) {
    return false;
}

return true;
}

}  // namespace mojo
