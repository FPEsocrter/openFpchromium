#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_CANVAS_CANVAS2D_CANVAS_RENDERING_CONTEXT_2D_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_CANVAS_CANVAS2D_CANVAS_RENDERING_CONTEXT_2D_FP_H_

#include "third_party/blink/renderer/core/html/canvas/html_canvas_element_fp.h"
#include "third_party/blink/renderer/modules/canvas/canvas2d/path_2d.h"
#include "third_party/blink/renderer/core/html/canvas/image_data.h"
#include "third_party/blink/renderer/modules/canvas/canvas2d/canvas_rendering_context_2d_state.h"


namespace blink {

namespace fp {

void fpGetImageData(blink::ImageData* imageData, bool flag, double x, double y, double width, double height, int canvasX, int canvasY, int canvasWidth, int canvasHeight);
void fpFullCoverage(blink::CanvasRenderingContext* ctx, double x, double y, double width, double height, double canvasX, double canvasY, double canvasWidth, double canvasHeight);
bool fpValidLine(const SkPoint& startPoint, const SkPoint& endPoint);
bool fpCanvas(blink::CanvasRenderingContext* ctx, const blink::CanvasRenderingContext2DState& state, bool isFill);
bool fpCanvas(blink::CanvasRenderingContext* ctx, const blink::CanvasRenderingContext2DState& state, const blink::CanvasPath& path, bool isFill);

} // namespace fp

} // namespace blink

#endif // THIRD_PARTY_BLINK_RENDERER_MODULES_CANVAS_CANVAS2D_CANVAS_RENDERING_CONTEXT_2D_FP_H_
