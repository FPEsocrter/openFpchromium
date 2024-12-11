#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ELEMENT_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ELEMENT_FP_H_


#include <random>
#include <cmath>
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/geometry/dom_rect_list.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"
#include "ui/gfx/geometry/rect_f.h"


double fpfracPart(double number, double fp) {
    if(!(number>0)||!(fp>0)){
        return number; 
    }

    double intPart;
    double fracPart = modf(number, &intPart);
    if (fracPart == 0.0) {
        return number; 
    }
    double t_fracPart = floor(fracPart*pow(10,7))/pow(10,7);
    if(fracPart==t_fracPart){
      return number; 
    }

    double c_Number = number * 10000;

    number = intPart + t_fracPart;

    c_Number = modf(c_Number, &intPart);

    fracPart = modf(fp*(c_Number+0.123456789123456), &intPart);
    
    return number+(fracPart/pow(10,8));
}

bool isTransform(blink::Element* element){
    //旋转多次和 旋转角度 后续需要追加
    blink::Element* t_ele = element;
    while (t_ele) {
      const blink::ComputedStyle* style = t_ele->GetComputedStyle();
      if (style) {
        if (style->HasTransform()) {
          return true;
         }
      }
      t_ele = t_ele->parentElement();
    }
  return false;
}

void fpDOMRect(blink::DOMRect* dOMRect,blink::fp::ClientRects clientRects){
    dOMRect->setX(fpfracPart(dOMRect->x(), clientRects.x));
    dOMRect->setY(fpfracPart(dOMRect->y(), clientRects.y));
    dOMRect->setWidth(fpfracPart(dOMRect->width(), clientRects.width));
    dOMRect->setHeight(fpfracPart(dOMRect->height(), clientRects.height));
}

void fpGetClientRects(blink::DOMRectList* domRectList, blink::Element* element){
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.clientRects.type > 1 &&
      isTransform(element)){
        for (unsigned i = 0; i < domRectList->length(); ++i) {
          fpDOMRect(domRectList->item(i),t_fingerprint.clientRects);
        }
    }
}

void fpGetBoundingClientRect(blink::DOMRect* dOMRect, blink::Element* element){
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.clientRects.type > 1 &&
      isTransform(element)){
        fpDOMRect(dOMRect,t_fingerprint.clientRects);
    }

}






#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ELEMENT_FP_H_
