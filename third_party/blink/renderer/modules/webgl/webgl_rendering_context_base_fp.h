#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGL_WEBGL_RENDERING_CONTEXT_BASE_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGL_WEBGL_RENDERING_CONTEXT_BASE_FP_H_

#include "stdint.h"
#include "third_party/khronos/GLES2/gl2.h"
#include "third_party/blink/renderer/core/typed_arrays/dom_array_buffer_view.h"
#include "third_party/blink/renderer/core/html/canvas/html_canvas_element_fp.h"

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

void fpReadPixelsHelper(GLint x,GLint y,
                        GLsizei width, GLsizei height,
                        GLenum format,GLenum type,
                        blink::DOMArrayBufferView* pixels,int64_t offset,
                        int canvasWidth,int canvasHeight){
                          
  if(x>0||y>0||width<canvasWidth||height<canvasHeight){
       return;
  }                        
  auto bufferType = pixels->GetType();
  if(format!=GL_RGBA||type!=GL_UNSIGNED_BYTE||
    (bufferType != blink::DOMArrayBufferView::kTypeUint8 && bufferType != blink::DOMArrayBufferView::kTypeUint8Clamped)){
    return;
  }

  base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
  blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
  if (base::SingletonFingerprint::GetInit(t_singletonFingerprint)&&t_fingerprint.webGL.type > 1) {
    base::CheckedNumeric<GLuint> offset_in_bytes = offset;
    uint8_t* data = static_cast<uint8_t*>(pixels->BaseAddressMaybeShared()) + offset_in_bytes.ValueOrDie();
    if (strlen((char*)data)<32){
      return;
    }
    std::vector<blink::fp::ColoredPoint>  coloredPointList= t_fingerprint.webGL.coloredPointList;
    blink::CanvasFpIng::fpPixel(data, coloredPointList, 4, canvasWidth, canvasHeight);

  }

   
}

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGL_WEBGL_RENDERING_CONTEXT_BASE_FP_H_
