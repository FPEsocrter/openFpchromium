#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_FP_TEXTMETRICS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_FP_TEXTMETRICS_H_



#include "ui/gfx/geometry/rect.h"
#include "third_party/blink/renderer/platform/fonts/font.h"
#include "third_party/blink/renderer/platform/fonts/font_family.h"
#include "base/singleton_fingerprint.h"
//#include "third_party/blink/renderer/core/html/canvas/text_metrics.h"

namespace blink {

    namespace fp {

        struct FpTextMetrics {
            double actual_bounding_box_left_;  
            double actual_bounding_box_right_;
            double font_bounding_box_ascent_;
            double font_bounding_box_descent_;
            double actual_bounding_box_ascent_;
            double actual_bounding_box_descent_;

        };

    }
}

bool fpTextMetricsCypher(blink::fp::FpTextMetrics& textMetric, const blink::Font& font, gfx::RectF& glyph_bounds, float dx,
                        float ascent, float descent, float baseline_y){

     base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
     blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
      if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1){
         base::flat_map<std::string, blink::fp::FontInfo> fontMap = t_fingerprint.font.fontMap;
         const blink::FontFamily& fontFamily = font.GetFontDescription().FirstFamily();
         std::string fontName = fontFamily.FamilyName().Utf8();
         auto iter = fontMap.find(fontName);
         if (iter != fontMap.end()) {
             blink::fp::FontInfo fontInfo = iter->second;
             if (fontInfo.id>0) {
                glyph_bounds.set_x(glyph_bounds.x() * fontInfo.width);
                glyph_bounds.set_y(glyph_bounds.y() * fontInfo.height);
                glyph_bounds.set_height(glyph_bounds.height() * fontInfo.height);
                glyph_bounds.set_width(glyph_bounds.width() * fontInfo.width);
                 
                dx = dx * fontInfo.width;

                textMetric.actual_bounding_box_left_ = -glyph_bounds.x() + dx+fontInfo.actualBoundingBoxLeft;
                textMetric.actual_bounding_box_right_ = glyph_bounds.right() - dx+fontInfo.actualBoundingBoxRight;

                ascent = ascent * fontInfo.height;
                
                textMetric.font_bounding_box_ascent_ = static_cast<int>(ascent - baseline_y+fontInfo.fontBoundingBoxAscent);
                textMetric.font_bounding_box_descent_ = static_cast<int>(descent + baseline_y+fontInfo.fontBoundingBoxDescent);
                textMetric.actual_bounding_box_ascent_ = static_cast<int>(-glyph_bounds.y() - baseline_y+fontInfo.actualBoundingBoxAscent);
                textMetric.actual_bounding_box_descent_ = static_cast<int>(glyph_bounds.bottom() + baseline_y+fontInfo.actualBoundingBoxDescent);

                 return true;
             }
         }
      }
    return false;
}


  

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_FP_TEXTMETRICS_H_