#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_OFFLINE_AUDIO_CONTEXT_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_OFFLINE_AUDIO_CONTEXT_FP_H_

#include <cmath>
#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

#include "third_party/blink/renderer/modules/webaudio/audio_buffer.h"
#include "third_party/blink/renderer/core/typed_arrays/dom_typed_array.h"
 
float fpfracPart(float number, float fp, uint32_t length) {

   
    if (number == 0.0f || fp == 0.0f) {
        return number;
    }

    float intPart;
    float fracPart = modf(number, &intPart);
    if (fracPart == 0.0) {
        return number;
    }

    float t_fracPart = floor(fracPart * 10000) / 10000;

    float c_Number = number * 10000;

    number = intPart + t_fracPart;

    c_Number = modf(c_Number, &intPart);

    

    fracPart = modf(fp * (c_Number + 0.264984637498f), &intPart);

    if (length % 79 == 0 && number < 0.7f ) {
        number = number + 0.223456789123;
    }
    return number + (fracPart / pow(10, 6));
}


void fpFireCompletionEvent(blink::AudioBuffer* rendered_buffer){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.audioContext.type > 1 ){

        std::vector<double>& noise = t_fingerprint.audioContext.noise;
        size_t noiseSize = noise.size();
        for (unsigned int j = 0; j < rendered_buffer->length(); j++) {
            blink::DOMFloat32Array* arrayPtr =rendered_buffer->getChannelData(j).Get();
            if (arrayPtr) {
                float* data = arrayPtr->Data();
                for (size_t i = 0; i < arrayPtr->length(); ++i) {
                    uint32_t noiseIndex = static_cast<uint32_t>(i) % static_cast<uint32_t>(noiseSize);
                    data[i] = fpfracPart(data[i], noise[noiseIndex], static_cast<uint32_t>(i));
                }
            }
        }
    }
   

}


#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_OFFLINE_AUDIO_CONTEXT_FP_H_
