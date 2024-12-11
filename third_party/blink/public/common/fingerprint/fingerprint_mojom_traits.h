#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_FINGERPRINT_FINGERPRINT_MOJOM_TRAITS_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_FINGERPRINT_FINGERPRINT_MOJOM_TRAITS_H_


#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"

#include <string>

#include "mojo/public/cpp/bindings/struct_traits.h"
#include "third_party/blink/public/common/common_export.h"
#include "third_party/blink/public/mojom/fingerprint/fingerprint.mojom-shared.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

namespace mojo {

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::ConsistencyDataView,
                                        ::blink::fp::Consistency> {
  static int32_t type(const ::blink::fp::Consistency& data) { return data.type; }
  static const std::vector<std::string>& urlList(
      const ::blink::fp::Consistency& data) {
    return data.urlList;
  }

  static bool Read(blink::mojom::ConsistencyDataView data,
                   ::blink::fp::Consistency* out);
}; 

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::UADataView,
                                        ::blink::fp::UA> {
  static int32_t type(const ::blink::fp::UA& data) { return data.type; }
  static const std::string& userAgent(const ::blink::fp::UA& data) {
    return data.userAgent;
  }

  static bool Read(blink::mojom::UADataView data, ::blink::fp::UA* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::UaMetadataDataView,
                                        ::blink::fp::UaMetadata> {
  static int32_t type(const ::blink::fp::UaMetadata& data) { return data.type; }
  static const ::blink::UserAgentMetadata& userAgentMetadata(
      const ::blink::fp::UaMetadata& data) {
    return data.userAgentMetadata;
  }

  static bool Read(blink::mojom::UaMetadataDataView data,
                   ::blink::fp::UaMetadata* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::WebRTCDataView,
                                        ::blink::fp::WebRTC> {
  static int32_t type(const ::blink::fp::WebRTC& data) { return data.type; }
  static const std::string& privateIp(const ::blink::fp::WebRTC& data) {
    return data.privateIp;
  }
  static const std::string& publicIp(const ::blink::fp::WebRTC& data) {
    return data.publicIp;
  }

  static bool Read(blink::mojom::WebRTCDataView data, ::blink::fp::WebRTC* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::TimeZoneDataView,
                                        ::blink::fp::TimeZone> {
  static int32_t type(const ::blink::fp::TimeZone& data) { return data.type; }
  static const std::string& gmt(const ::blink::fp::TimeZone& data) {
    return data.gmt;
  }

  static bool Read(blink::mojom::TimeZoneDataView data, ::blink::fp::TimeZone* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::LocationDataView,
                                        ::blink::fp::Location> {
  static int32_t type(const ::blink::fp::Location& data) { return data.type; }
  static bool  permissions(const ::blink::fp::Location& data){return data.permissions;}
  static double latitude(const ::blink::fp::Location& data) { return data.latitude; }
  static double longitude(const ::blink::fp::Location& data) {
    return data.longitude;
  }
  static double accuracy(const ::blink::fp::Location& data) { return data.accuracy; }

  static bool Read(blink::mojom::LocationDataView data, ::blink::fp::Location* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::LanguageDataView,
                                        ::blink::fp::Language> {
  static int32_t type(const ::blink::fp::Language& data) { return data.type; }
  static const std::string& interfaceLanguage(const ::blink::fp::Language& data) {
    return data.interfaceLanguage;
  }
  static const std::vector<std::string>& languages(
      const ::blink::fp::Language& data) {
    return data.languages;
  }

  static bool Read(blink::mojom::LanguageDataView data, ::blink::fp::Language* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::ResolutionDataView,
                                        ::blink::fp::Resolution> {
  static int32_t type(const ::blink::fp::Resolution& data) { return data.type; }
  static int32_t windowWidth(const ::blink::fp::Resolution& data) {
    return data.windowWidth;
  }
  static int32_t windowHeight(const ::blink::fp::Resolution& data) {
    return data.windowHeight;
  }
  static int32_t monitorWidth(const ::blink::fp::Resolution& data) {
    return data.monitorWidth;
  }
  static int32_t monitorHeight(const ::blink::fp::Resolution& data) {
    return data.monitorHeight;
  }

  static bool Read(blink::mojom::ResolutionDataView data,
                   ::blink::fp::Resolution* out);
};


template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::FontInfoDataView,
                                        ::blink::fp::FontInfo> {

  static double id(const ::blink::fp::FontInfo& data) { return data.id; }                                      
  static double width(const ::blink::fp::FontInfo& data) { return data.width; }
  static double height(const ::blink::fp::FontInfo& data) { return data.height; }
  static double actualBoundingBoxAscent(const ::blink::fp::FontInfo& data) {
    return data.actualBoundingBoxAscent;
  }
  static double actualBoundingBoxDescent(const ::blink::fp::FontInfo& data) {
    return data.actualBoundingBoxDescent;
  }
  static double actualBoundingBoxLeft(const ::blink::fp::FontInfo& data) {
    return data.actualBoundingBoxLeft;
  }
  static double actualBoundingBoxRight(const ::blink::fp::FontInfo& data) {
    return data.actualBoundingBoxRight;
  }
  static double fontBoundingBoxAscent(const ::blink::fp::FontInfo& data) {
    return data.fontBoundingBoxAscent;
  }
  static double fontBoundingBoxDescent(const ::blink::fp::FontInfo& data) {
    return data.fontBoundingBoxDescent;
  }
  static const std::vector<std::string>& filePaths(const ::blink::fp::FontInfo& data) {
    return data.filePaths;
  }
  

  static bool Read(blink::mojom::FontInfoDataView data,
                   ::blink::fp::FontInfo* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::FontDataView,
                                        ::blink::fp::Font> {
  static int32_t type(const ::blink::fp::Font& data) { return data.type; }
  static int32_t maxId(const ::blink::fp::Font& data) { return data.maxId; }
  static int32_t defaultId(const ::blink::fp::Font& data) { return data.defaultId; }
  static std::string defaultName(const ::blink::fp::Font& data) { return data.defaultName; }
  static const std::vector<std::string>& defaultPaths(
      const ::blink::fp::Font& data) {
    return data.defaultPaths;
  }
  static const base::flat_map<std::string, ::blink::fp::FontInfo>& fontMap(
      const ::blink::fp::Font& data) {
    return data.fontMap;
  }
  static const base::flat_map<int, std::string>& fontIdMap(
      const ::blink::fp::Font& data) {
    return data.fontIdMap;
  }


  static bool Read(blink::mojom::FontDataView data, ::blink::fp::Font* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::ColoredPointDataView,
                                        ::blink::fp::ColoredPoint> {
  static int32_t row(const ::blink::fp::ColoredPoint& data) { return data.row; }
  static int32_t column(const ::blink::fp::ColoredPoint& data) { return data.column; }
  static int32_t red(const ::blink::fp::ColoredPoint& data) { return data.red; }
  static int32_t green(const ::blink::fp::ColoredPoint& data) { return data.green; }
  static int32_t blue(const ::blink::fp::ColoredPoint& data) { return data.blue; }
  static int32_t alpha(const ::blink::fp::ColoredPoint& data) { return data.alpha; }

  static bool Read(blink::mojom::ColoredPointDataView data, ::blink::fp::ColoredPoint* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::CanvasDataView,
                                        ::blink::fp::Canvas> {
  static int32_t type(const ::blink::fp::Canvas& data) { return data.type; }
  static const std::vector<::blink::fp::ColoredPoint>& coloredPointList(
      const ::blink::fp::Canvas& data) {
    return data.coloredPointList;
  }

  static bool Read(blink::mojom::CanvasDataView data, ::blink::fp::Canvas* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::WebGLDeviceDataView,
                                        ::blink::fp::WebGLDevice> {
  static int32_t type(const ::blink::fp::WebGLDevice& data) { return data.type; }
  static const std::string& vendors(const ::blink::fp::WebGLDevice& data) {
    return data.vendors;
  }
  static const std::string& renderer(const ::blink::fp::WebGLDevice& data) {
    return data.renderer;
  }
  static const std::string& gpuVendors(const ::blink::fp::WebGLDevice& data) {
    return data.gpuVendors;
  }
  static const std::string& gpuArchitecture(const ::blink::fp::WebGLDevice& data) {
    return data.gpuArchitecture;
  }
  static bool Read(blink::mojom::WebGLDeviceDataView data,
                   ::blink::fp::WebGLDevice* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::AudioContextDataView,
                                        ::blink::fp::AudioContext> {
  static int32_t type(const ::blink::fp::AudioContext& data) { return data.type; }
  static const std::vector<double> noise(
      const ::blink::fp::AudioContext& data) {
    return data.noise;
  }
  static bool Read(blink::mojom::AudioContextDataView data,
                   ::blink::fp::AudioContext* out);
};

template <>
struct BLINK_COMMON_EXPORT
    StructTraits<blink::mojom::MediaEquipmentInfoDataView,
                 ::blink::fp::MediaEquipmentInfo> {
  static int32_t type(const ::blink::fp::MediaEquipmentInfo& data) {
    return data.type;
  }
  static const std::string& label(const ::blink::fp::MediaEquipmentInfo& data) {
    return data.label;
  }
  static const std::string& deviceId(const ::blink::fp::MediaEquipmentInfo& data) {
    return data.deviceId;
  }
  static const std::string& groupId(const ::blink::fp::MediaEquipmentInfo& data) {
    return data.groupId;
  }

  static bool Read(blink::mojom::MediaEquipmentInfoDataView data,
                   ::blink::fp::MediaEquipmentInfo* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::MediaEquipmentDataView,
                                        ::blink::fp::MediaEquipment> {
  static int32_t type(const ::blink::fp::MediaEquipment& data) { return data.type; }
  static const std::vector<::blink::fp::MediaEquipmentInfo>& list(
      const ::blink::fp::MediaEquipment& data) {
    return data.list;
  }

  static bool Read(blink::mojom::MediaEquipmentDataView data,
                   ::blink::fp::MediaEquipment* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::ClientRectsDataView,
                                        ::blink::fp::ClientRects> {
  static int32_t type(const ::blink::fp::ClientRects& data) { return data.type; }
  static double x(const ::blink::fp::ClientRects& data) { return data.x; }
  static double y(const ::blink::fp::ClientRects& data) { return data.y; }
  static double width(const ::blink::fp::ClientRects& data) { return data.width; }
  static double height(const ::blink::fp::ClientRects& data) {
    return data.height;
  }

  static bool Read(blink::mojom::ClientRectsDataView data,
                   ::blink::fp::ClientRects* out);
};

template <>
struct BLINK_COMMON_EXPORT
    StructTraits<blink::mojom::SpeechVoicesInfoDataView,
                 ::blink::fp::SpeechVoicesInfo> {
  static const std::string& voiceUri(const ::blink::fp::SpeechVoicesInfo& data) {
    return data.voiceUri;
  }
  static const std::string& name(const ::blink::fp::SpeechVoicesInfo& data) {
    return data.name;
  }
  static const std::string& lang(const ::blink::fp::SpeechVoicesInfo& data) {
    return data.lang;
  }
  static bool isLocalService(const ::blink::fp::SpeechVoicesInfo& data) {
    return data.isLocalService;
  }
  static bool isDefault(const ::blink::fp::SpeechVoicesInfo& data) {
    return data.isDefault;
  }

  static bool Read(blink::mojom::SpeechVoicesInfoDataView data,
                   ::blink::fp::SpeechVoicesInfo* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::SpeechVoicesDataView,
                                        ::blink::fp::SpeechVoices> {
  static int32_t type(const ::blink::fp::SpeechVoices& data) { return data.type; }

  static const std::vector<::blink::fp::SpeechVoicesInfo>& list(
      const ::blink::fp::SpeechVoices& data) {
    return data.list;
  }

  static bool Read(blink::mojom::SpeechVoicesDataView data,
                   ::blink::fp::SpeechVoices* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::ResourceInfoDataView,
                                        ::blink::fp::ResourceInfo> {
  static int32_t type(const ::blink::fp::ResourceInfo& data) { return data.type; }
  static int32_t cpu(const ::blink::fp::ResourceInfo& data) { return data.cpu; }
  static float memory(const ::blink::fp::ResourceInfo& data) { return data.memory; }

  static bool Read(blink::mojom::ResourceInfoDataView data,
                   ::blink::fp::ResourceInfo* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::DoNotTrackDataView,
                                        ::blink::fp::DoNotTrack> {
  static int32_t type(const ::blink::fp::DoNotTrack& data) { return data.type; }
  static bool flag(const ::blink::fp::DoNotTrack& data) { return data.flag; }

  static bool Read(blink::mojom::DoNotTrackDataView data,
                   ::blink::fp::DoNotTrack* out);
};

template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::OpenPortDataView,
                                        ::blink::fp::OpenPort> {
  static int32_t type(const ::blink::fp::OpenPort& data) { return data.type; }
  static const std::vector<int32_t>& openPort(const ::blink::fp::OpenPort& data) {
    return data.openPort;
  }
  static const std::string& url(const ::blink::fp::OpenPort& data) {
    return data.url;
  }
  static bool Read(blink::mojom::OpenPortDataView data,
                   ::blink::fp::OpenPort* out);
};


/**/
template <>
struct BLINK_COMMON_EXPORT StructTraits<blink::mojom::FingerprintDataView,
                                        ::blink::fp::Fingerprint> {
  static int32_t init(const ::blink::fp::Fingerprint& data) { return data.init; }
  static const ::blink::fp::Consistency& consistency(
      const ::blink::fp::Fingerprint& data) {
    return data.consistency;
  }
  static const ::blink::fp::UA& ua(const ::blink::fp::Fingerprint& data) {
    return data.ua;
  }
  static const ::blink::fp::UaMetadata& uaMetadata(
      const ::blink::fp::Fingerprint& data) {
    return data.uaMetadata;
  }
  static const ::blink::fp::TimeZone& timeZone(
      const ::blink::fp::Fingerprint& data) {
    return data.timeZone;
  }
  static const ::blink::fp::WebRTC& webRTC(const ::blink::fp::Fingerprint& data) {
    return data.webRTC;
  }
  static const ::blink::fp::Location& location(
      const ::blink::fp::Fingerprint& data) {
    return data.location;
  }
  static const ::blink::fp::Language& language(
      const ::blink::fp::Fingerprint& data) {
    return data.language;
  }
  static const ::blink::fp::Resolution& resolution(
      const ::blink::fp::Fingerprint& data) {
    return data.resolution;
  }
  static const ::blink::fp::Font& font(const ::blink::fp::Fingerprint& data) {
    return data.font;
  }
  static const ::blink::fp::Canvas& canvas(const ::blink::fp::Fingerprint& data) {
    return data.canvas;
  }
  static const ::blink::fp::Canvas& webGL(const ::blink::fp::Fingerprint& data) {
    return data.webGL;
  }
  static const ::blink::fp::Canvas& gupGL(const ::blink::fp::Fingerprint& data) {
    return data.gupGL;
  }
  static const ::blink::fp::WebGLDevice& webGLDevice(
      const ::blink::fp::Fingerprint& data) {
    return data.webGLDevice;
  }
  static const ::blink::fp::AudioContext& audioContext(
      const ::blink::fp::Fingerprint& data) {
    return data.audioContext;
  }
  static const ::blink::fp::MediaEquipment& mediaEquipment(
      const ::blink::fp::Fingerprint& data) {
    return data.mediaEquipment;
  }
  static const ::blink::fp::ClientRects& clientRects(
      const ::blink::fp::Fingerprint& data) {
    return data.clientRects;
  }
  static const ::blink::fp::SpeechVoices& speechVoices(
      const ::blink::fp::Fingerprint& data) {
    return data.speechVoices;
  }
  static const ::blink::fp::ResourceInfo& resourceInfo(
      const ::blink::fp::Fingerprint& data) {
    return data.resourceInfo;
  }
  static const ::blink::fp::DoNotTrack& doNotTrack(
      const ::blink::fp::Fingerprint& data) {
    return data.doNotTrack;
  }
  static const ::blink::fp::OpenPort& openPort(
      const ::blink::fp::Fingerprint& data) {
    return data.openPort;
  }
  static bool Read(blink::mojom::FingerprintDataView data,
                   ::blink::fp::Fingerprint* out);
};

}  // namespace mojo

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_FINGERPRINT_FINGERPRINT_MOJOM_TRAITS_H_
