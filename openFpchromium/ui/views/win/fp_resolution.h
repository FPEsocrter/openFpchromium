#ifndef UI_VIEWS_WIN_FP_RESOLUTION_H_
#define UI_VIEWS_WIN_FP_RESOLUTION_H_

#include "ui/gfx/geometry/rect.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

void fpMonitorAndRects(gfx::Rect* monitor_rect,gfx::Rect* work_area){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resolution.type>1){
            monitor_rect->set_width(t_fingerprint.resolution.monitorWidth);     
            monitor_rect->set_height(t_fingerprint.resolution.monitorHeight);         
            work_area->set_width(t_fingerprint.resolution.windowWidth);     
            work_area->set_height(t_fingerprint.resolution.windowHeight);    
        }
    
}

void pfIsFullscreen(gfx::Rect& monitor_rect) {
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resolution.type > 1) {
        monitor_rect.set_width(t_fingerprint.resolution.monitorWidth);
        monitor_rect.set_height(t_fingerprint.resolution.monitorHeight);

    }
}

void pfIsMaximized(gfx::Rect& work_rect) {
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resolution.type > 1) {
        work_rect.set_width(t_fingerprint.resolution.windowWidth);
        work_rect.set_height(t_fingerprint.resolution.windowHeight);
    }

}

void fpWindowPosChanging(WINDOWPOS* window_pos){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    base::SingletonFingerprint::GetInit(t_singletonFingerprint);
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resolution.type > 1) {
        
        if (window_pos->cx > t_fingerprint.resolution.windowWidth || window_pos->cy > t_fingerprint.resolution.windowHeight) {
                window_pos->cx = t_fingerprint.resolution.windowWidth;
                window_pos->cy = t_fingerprint.resolution.windowHeight;
        }
        
    }

    
}


#endif // UI_VIEWS_WIN_FP_RESOLUTION_H_