#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_HTML_CANVAS_ELEMENT_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_HTML_CANVAS_ELEMENT_FP_H_


#include "third_party/blink/public/platform/web_common.h"
#include "third_party/blink/renderer/core/html/canvas/canvas_rendering_context.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "third_party/blink/renderer/platform/graphics/image_data_buffer.h"



namespace blink{
  
class BLINK_EXPORT CanvasFpIng{
public: 
    static void fpPixel(unsigned char* mutablePixels, std::vector<fp::ColoredPoint> list, int bytesPerPixel, int width, int height);
    static void fpToDataURLInternal(ImageDataBuffer* data_buffer, CanvasRenderingContext* canvasRenderingContext, SkImageInfo skImageInfo, ImageEncodingMimeType encoding_mime_type, bool isCanvas, bool isWebGL, bool isGpuGL);
    static scoped_refptr<StaticBitmapImage> fpToBlob(scoped_refptr<StaticBitmapImage> image_bitmap, CanvasRenderingContext* canvasRenderingContext, ImageEncodingMimeType encoding_mime_type, bool isCanvas, bool isWebGL, bool isGpuGL);
};
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_CANVAS_HTML_CANVAS_ELEMENT_FP_H_
