#ifndef  THIRD_PARTY_BLINK_PUBLIC_COMMON_FINGERPRINT_FINGERPRINT_METADATA_H_
#define  THIRD_PARTY_BLINK_PUBLIC_COMMON_FINGERPRINT_FINGERPRINT_METADATA_H_

#include <string>
#include <vector>

#include "base/containers/flat_map.h"

#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"


#include "third_party/abseil-cpp/absl/types/optional.h"
#include "third_party/blink/public/common/common_export.h"

namespace blink {

namespace fp {
    
    /* 0 跟随ip   1 关闭  2 噪音  3 噪音   0和1  都是关闭
    后期启动的同步,用户画图和声音指纹 
     Canvas canvas;
     Canvas webGL;
     Canvas gupGL;
     AudioContext audioContext;
     暂时可以为空
    */
    struct BLINK_COMMON_EXPORT Consistency { 
        public:
            int type = 0; 
            std::vector<std::string> urlList; 
    };

    /* 0 跟随ip   1 关闭  2 噪音  3 噪音 
    ua 默认不读取 只是正常传
    */
    struct BLINK_COMMON_EXPORT UA{
        public:
            int type = 0; 
            std::string userAgent;  
    };

    /* 0 跟随ip   1 关闭  2 噪音  3 噪音 
    */
    struct BLINK_COMMON_EXPORT UaMetadata{
        public:
            int type = 0; 
            blink::UserAgentMetadata userAgentMetadata;
    };

    struct BLINK_COMMON_EXPORT WebRTC {
        public:
            int type = 0; 
            std::string  privateIp;
            std::string  publicIp;
    };

    struct BLINK_COMMON_EXPORT TimeZone {
        public:
            int type = 0; 
            std::string gmt;
    };

    struct BLINK_COMMON_EXPORT Location {
        public:
            int type = 0;
            bool  permissions;
            double latitude ;
            double longitude ;
            double accuracy ;
    };

    struct BLINK_COMMON_EXPORT Language {
        public:
            int type = 0; 
            std::string interfaceLanguage;
            std::vector<std::string>  languages;
    };
    

    struct BLINK_COMMON_EXPORT Resolution {  
        public:
            int type = 0; 
            int windowWidth;
            int windowHeight;

            int monitorWidth;
            int monitorHeight;

    };

    struct BLINK_COMMON_EXPORT FontInfo { 
        public:
            int  id = 0;
            double width;
            double height;
            double actualBoundingBoxAscent;
            double actualBoundingBoxDescent;
            double actualBoundingBoxLeft;
            double actualBoundingBoxRight;
            double fontBoundingBoxAscent;
            double fontBoundingBoxDescent;
            std::vector<std::string> filePaths;
    };

    struct BLINK_COMMON_EXPORT Font {
        public:
            int type = 0;
            int maxId = 0;
            int defaultId = 0;
            std::string defaultName;
            std::vector<std::string> defaultPaths;
            base::flat_map<std::string, FontInfo> fontMap;
            base::flat_map<int, std::string> fontIdMap;
    };

    struct BLINK_COMMON_EXPORT ColoredPoint{
        public:
            int row;
            int column;
            int red;  
            int green;
            int blue;
            int alpha;
    };

    struct BLINK_COMMON_EXPORT Canvas { 
        public:
            int type = 0; 
            std::vector<ColoredPoint>  coloredPointList; 
            
    };

    struct BLINK_COMMON_EXPORT WebGLDevice {
        public:
            int type = 0; 
            std::string  vendors;
            std::string  renderer;
            std::string  gpuVendors;
            std::string  gpuArchitecture;
    };

    struct BLINK_COMMON_EXPORT AudioContext {
        public:
            int type = 0;  
            std::vector<double> noise;
    };

    struct BLINK_COMMON_EXPORT MediaEquipmentInfo {
        public:
            int type = 0;  //0 是麦克风   1 摄像头  2  音响
            std::string label;
            std::string deviceId;
            std::string groupId;
    
    };

    struct BLINK_COMMON_EXPORT MediaEquipment {
        public:
            int type = 0; 
            std::vector<MediaEquipmentInfo> list;
    };


    struct BLINK_COMMON_EXPORT ClientRects {
        public:
            int type = 0; // 0 默认  1.噪音  ,2. 系统默认， 3.关闭 
            double x;   //可以存任意的数字 这里放的是倍数,只影响小数后7位
            double y;
            double width;
            double height;
    };

    struct BLINK_COMMON_EXPORT SpeechVoicesInfo {
        public:
            std::string voiceUri;
            std::string name;
            std::string lang;
            bool isLocalService;
            bool isDefault;
    };

    struct BLINK_COMMON_EXPORT SpeechVoices {
        public:         
            int type = 0; 
            std::vector<SpeechVoicesInfo> list;
    };

    struct BLINK_COMMON_EXPORT ResourceInfo {
        public:
            int type = 0; 
            int cpu; 
            float memory;      
    };

    struct BLINK_COMMON_EXPORT DoNotTrack {
        public:
            int type = 0; 
            bool flag;
    };

  struct BLINK_COMMON_EXPORT OpenPort{
        public:
            int type = 0; 
            std::vector<int> openPort;
            std::string url;
  };



    struct BLINK_COMMON_EXPORT Fingerprint {
        public:
            int init = 0;  //0 默认，1 关闭  2 噪音（启动） 0和1  都是关闭  其他都不会生效
            Consistency  consistency;
            UA ua;
            UaMetadata uaMetadata;
            TimeZone timeZone;
            WebRTC webRTC;
            Location location;
            Language language;
            Resolution resolution;
            Font font;
            Canvas canvas;
            Canvas webGL;
            Canvas gupGL;
            WebGLDevice webGLDevice;
            AudioContext audioContext;
            MediaEquipment mediaEquipment;
            ClientRects clientRects;
            SpeechVoices speechVoices;
            ResourceInfo resourceInfo;
            DoNotTrack doNotTrack;
            OpenPort openPort;
    };
} // namespace pf
}  // namespace blink    



#endif  // THIRD_PARTY_BLINK_PUBLIC_COMMON_FINGERPRINT_FINGERPRINT_METADATA_H_