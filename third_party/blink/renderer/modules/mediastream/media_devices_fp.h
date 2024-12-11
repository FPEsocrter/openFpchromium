
#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIASTREAM_MEDIA_DEVICES_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIASTREAM_MEDIA_DEVICES_FP_H_



#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "third_party/blink/public/common/mediastream/media_devices.h"
#include "third_party/blink/public/mojom/mediastream/media_devices.mojom-blink-forward.h"

#include "third_party/blink/renderer/modules/mediastream/media_device_info.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/modules/mediastream/input_device_info.h"

void fpDevicesEnumerated(WTF::Vector<blink::mojom::blink::VideoInputDeviceCapabilitiesPtr>
                              video_input_capabilities,
                        WTF::Vector<blink::mojom::blink::AudioInputDeviceCapabilitiesPtr>
                              audio_input_capabilities,
                          blink::MediaDeviceInfoVector& media_devices1,
                          blink::MediaDeviceInfoVector& media_devices2){
    if (media_devices1.size()==1) {
        if (media_devices1[0]->label() == "" ||
            media_devices1[0]->deviceId() == "" ||
            media_devices1[0]->groupId() == "") {
    
            media_devices2.push_back(media_devices1[0]);
          return;
            
        }
      
    }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) &&
        t_fingerprint.mediaEquipment.type > 1) {

        std::vector<blink::fp::MediaEquipmentInfo>  list = t_fingerprint.mediaEquipment.list;
       
        for (std::size_t i = 0; i < list.size(); ++i) 
        {
          blink::fp::MediaEquipmentInfo t_tmp=list[i];
          blink::mojom::blink::MediaDeviceType device_type=static_cast<blink::mojom::blink::MediaDeviceType>(t_tmp.type);
          blink::InputDeviceInfo* input_device_info = blink::MakeGarbageCollected<blink::InputDeviceInfo>(
                      String::FromUTF8(t_tmp.deviceId), String::FromUTF8(t_tmp.label),
                      String::FromUTF8(t_tmp.groupId), device_type);
          media_devices2.push_back(input_device_info);
        }
    }
    else {
        for (const auto& deviceInfo : media_devices1) {
            
            media_devices2.push_back(deviceInfo);
        }
    
    
    
    }


}




#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIASTREAM_MEDIA_DEVICES_FP_H_
