#include "third_party/blink/renderer/modules/canvas/canvas2d/canvas_rendering_context_2d_fp.h"

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "third_party/blink/renderer/core/html/canvas/html_canvas_element_fp.h"

#include <cmath>
#include "third_party/blink/renderer/modules/canvas/canvas2d/canvas_rendering_context_2d.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_float32array_uint16array_uint8clampedarray.h"
#include "third_party/blink/renderer/bindings/modules/v8/v8_typedefs.h"


namespace blink {

namespace fp { 

void fpGetImageData(blink::ImageData* imageData,bool flag,
     double x, double y, double width, double height,
     int canvasX, int canvasY, int canvasWidth, int canvasHeight){
    if(!flag){
        return;
    }
    if(canvasX>0||canvasY>0||x>0||y>0||width<canvasWidth||height<canvasHeight){
        return;
    }
    if (imageData==nullptr) {
        return;
    }
    const blink::V8ImageDataArray* v8data = imageData->data();
    if (!v8data->IsUint8ClampedArray()) {
        return;
    }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.canvas.type > 0) {
        std::vector<blink::fp::ColoredPoint>  coloredPointList= t_fingerprint.canvas.coloredPointList;
        const unsigned char* data = v8data->GetAsUint8ClampedArray()->Data();
        unsigned char* mutablePixels = const_cast<unsigned char*>(data);
        CanvasFpIng::fpPixel(mutablePixels, coloredPointList, 4, canvasWidth, canvasHeight);//todo
    }

}
void fpFullCoverage(blink::CanvasRenderingContext* ctx ,
                 double x, double y, double width, double height,
                 double canvasX, double canvasY,double canvasWidth, double canvasHeight) {
    if (!ctx->getFpCanvas()) {
        return;
    }
    if(canvasX>0.5||canvasY>0.5||x>0.5||y>0.5||width<canvasWidth-0.5||height<canvasHeight-0.5){
        return;
    }
    ctx->setFpCanvas(false);
}


bool fpValidLine(const SkPoint& startPoint, const SkPoint& endPoint) {
    if (startPoint.x()== endPoint.x()|| startPoint.y() == endPoint.y()) {
        return true;
    }
    float  dx = endPoint.x() - startPoint.x();
    float  dy = endPoint.y() - startPoint.y();
    float  radians = std::atan2(dy, dx);
    float  degrees = radians * 180.0 / M_PI;
    if (std::abs(degrees - 45.0 * std::round(degrees / 45.0)) > 0.01) {
        return false;
    }

    return true;
}

bool fpCanvas(blink::CanvasRenderingContext* ctx, const blink::CanvasRenderingContext2DState& state, bool isFill) {
    if (ctx->getFpCanvas()) {
        return true;
    }
    blink::CanvasStyle* style;
    if (isFill) {
        style = state.FillStyle();
    }else {
        style = state.StrokeStyle();
    }

    if (style->GetCanvasGradient()) {
        return true;
    }
    else if (style->GetCanvasPattern()) {
        return true;
    }

    if (!isFill) {
        double lineWidth = state.LineWidth();
        if (lineWidth > 1) {
            blink::LineCap lineCap = state.GetLineCap();
            if (lineCap == blink::LineCap::kRoundCap || lineCap == blink::LineCap::kSquareCap) {
                return true;
            }
        }

        blink::LineJoin lineJoin = state.GetLineJoin();
        if (lineJoin == blink::LineJoin::kRoundJoin || lineJoin == blink::LineJoin::kBevelJoin) {
            return true;
        }

    }

    blink::AffineTransform t = state.GetTransform();
    double rotation = std::atan2(t.B(), t.A());
    double rotationDegrees = rotation * 180.0 / M_PI;
    if (std::abs(rotationDegrees - 45.0 * std::round(rotationDegrees / 45.0)) > 0.01) {
        return true;
    }

    bool hasShadow = state.ShouldDrawShadows();
    if (hasShadow) {
        double shadowBlur = state.ShadowBlur();
        if (shadowBlur > 0.001) {
            return true;
        }

    }

    return false;
}

bool fpCanvas(blink::CanvasRenderingContext* ctx, const blink::CanvasRenderingContext2DState& state, const blink::CanvasPath& path, bool isFill) {

    if (ctx->getFpCanvas()) {
        return true;
    }

    if (path.IsEmpty()) {
        return false;
    }

    gfx::RectF bounds(path.BoundingRect());
    if (std::isnan(bounds.x()) || std::isnan(bounds.y()) ||
        std::isnan(bounds.width()) || std::isnan(bounds.height())) {
        return false;
    }

    if (fpCanvas(ctx, state, isFill)) {
        return true;
    }

    if (!path.IsLine()) {
        return true;
    }

    SkPath skPath = path.GetPath().GetSkPath();
    SkPath::Iter iter(skPath, true);

    SkPath::Verb verb;
    SkPoint pts[4];

    while ((verb = iter.next(pts)) != SkPath::kDone_Verb) {
        if (verb == SkPath::kQuad_Verb|| 
            verb == SkPath::kConic_Verb ||
            verb == SkPath::kCubic_Verb ) {
            return true;
        }
    }

    iter.setPath(skPath, true);
    while ((verb = iter.next(pts)) != SkPath::kDone_Verb) {
        if (verb == SkPath::kLine_Verb && !fpValidLine(pts[0], pts[1])) {
            return true;
        }
    }

    return false;
}

}   // namespace fp
    
} // namespace 
