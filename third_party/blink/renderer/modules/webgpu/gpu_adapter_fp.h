#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_ADAPTER_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_ADAPTER_FP_H_

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

#include "third_party/blink/renderer/modules/webgpu/gpu_adapter_info.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

blink::GPUAdapterInfo* fpRequestAdapterInfo(blink::GPUAdapterInfo* adapter_info,bool flag){
        base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
        blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.webGLDevice.type>1){
                blink::GPUAdapterInfo* T_adapter_info;
                
                if (flag) {
                    T_adapter_info = blink::MakeGarbageCollected<blink::GPUAdapterInfo>(
                         WTF::String(t_fingerprint.webGLDevice.gpuVendors.c_str(), t_fingerprint.webGLDevice.gpuVendors.length()),
                         WTF::String(t_fingerprint.webGLDevice.gpuArchitecture.c_str(), t_fingerprint.webGLDevice.gpuArchitecture.length()),
                         adapter_info->device(), adapter_info->description(), adapter_info->driver());
                } else {
                    T_adapter_info = blink::MakeGarbageCollected<blink::GPUAdapterInfo>(
                        WTF::String(t_fingerprint.webGLDevice.gpuVendors.c_str(), t_fingerprint.webGLDevice.gpuVendors.length()),
                        WTF::String(t_fingerprint.webGLDevice.gpuArchitecture.c_str(), t_fingerprint.webGLDevice.gpuArchitecture.length())
                    );
                }
                return T_adapter_info;
        }

      return  adapter_info;

}

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_ADAPTER_FP_H_
