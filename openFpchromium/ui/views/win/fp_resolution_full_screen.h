#ifndef UI_VIEWS_WIN_FP_RESOLUTION_FULL_SCREEN_H_
#define UI_VIEWS_WIN_FP_RESOLUTION_FULL_SCREEN_H_

#include "ui/gfx/geometry/rect.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

void fpProcessFullscreen(gfx::Rect& window_rect){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resolution.type>1){
            window_rect.set_width(t_fingerprint.resolution.monitorWidth);     
            window_rect.set_height(t_fingerprint.resolution.monitorHeight);         
        }
    
}


#endif // UI_VIEWS_WIN_FP_RESOLUTION_FULL_SCREEN_H_