#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_FP_ELECMENT_OFFSET_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_FP_ELECMENT_OFFSET_H_


#include "third_party/blink/renderer/platform/fonts/font_family.h"
#include "third_party/blink/renderer/core/layout/layout_box_model_object.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"


int fpOffsetWidth(const blink::LayoutBoxModelObject* layout_object, String tagName,int result){
   if(!tagName.EndsWithIgnoringCase("span")){
      return result;
   }
   base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
      if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1){
         base::flat_map<std::string, blink::fp::FontInfo> fontMap = t_fingerprint.font.fontMap;
         const blink::FontFamily& fontFamily = layout_object->Style()->GetFont().GetFontDescription().FirstFamily();
         std::string fontName = fontFamily.FamilyName().Utf8();
         std::transform(fontName.begin(), fontName.end(), fontName.begin(), ::tolower);
         auto iter = fontMap.find(fontName);
         if (iter != fontMap.end()) {
             blink::fp::FontInfo fontInfo = iter->second;
             if (fontInfo.id>0) {
                 return static_cast<int>(result * fontInfo.width);
             }
         }
      }


  return result;
}

int fpOffsetHeight(const blink::LayoutBoxModelObject* layout_object, String tagName,int result){

    if (!tagName.EndsWithIgnoringCase("span")) {
        return result;
    }
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1) {
        base::flat_map<std::string, blink::fp::FontInfo> fontMap = t_fingerprint.font.fontMap;
        const blink::FontFamily& fontFamily = layout_object->Style()->GetFont().GetFontDescription().FirstFamily();
        std::string fontName = fontFamily.FamilyName().Utf8();
        std::transform(fontName.begin(), fontName.end(), fontName.begin(), ::tolower);
        auto iter = fontMap.find(fontName);
        if (iter != fontMap.end()) {
            blink::fp::FontInfo fontInfo = iter->second;
            if (fontInfo.id > 0) {
                return static_cast<int>(result * fontInfo.height);
            }
        }
    }


    return result;
}

#endif // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_FP_ELECMENT_OFFSET_H_