#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_WIN_FONT_CACHE_SKIA_WIN_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_WIN_FONT_CACHE_SKIA_WIN_FP_H_

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "third_party/blink/renderer/platform/fonts/font_selection_types.h"


void fpCreateFontPlatformData(blink::FontSelectionValue& variant_stretch,
                              blink::FontSelectionValue Tvariant_stretch,
                              std::string fontName ) {

      base::SingletonFingerprint* t_singletonFingerprint =base::SingletonFingerprint::ForCurrentProcess();
      blink::fp::Fingerprint t_fingerprint = t_singletonFingerprint->GetFingerprint();
      if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1) {
        base::flat_map<std::string, blink::fp::FontInfo> fontMap =t_fingerprint.font.fontMap;
        std::transform(fontName.begin(), fontName.end(), fontName.begin(),::tolower);
        auto iter = fontMap.find(fontName);
        if (iter == fontMap.end()) {
          variant_stretch = Tvariant_stretch;
        }
        
      }
    
}


#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_WIN_FONT_CACHE_SKIA_WIN_FP_H_
