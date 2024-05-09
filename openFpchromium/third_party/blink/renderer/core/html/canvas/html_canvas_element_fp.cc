#include "third_party/blink/renderer/core/html/canvas/html_canvas_element_fp.h"

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"

#include "base/memory/scoped_refptr.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/blink/renderer/platform/graphics/image_data_buffer.h"
#include "third_party/blink/renderer/platform/graphics/static_bitmap_image.h"
#include "third_party/blink/renderer/core/html/canvas/canvas_rendering_context.h"

namespace blink {




void CanvasFpIng::fpPixel(unsigned char* mutablePixels,std::vector<blink::fp::ColoredPoint> list,int bytesPerPixel,int width,int height) {
       
        int start=list[0].row;
        int end = start;
        for (std::size_t i = 0; i < list.size(); ++i) {
            blink::fp::ColoredPoint coloredPoint = list[0];
            
            int  zend = coloredPoint.row%height;
            if(zend>start&&zend>=end){
               end=zend;
            }else if(zend<start&&start<end&&zend>end){
               end=zend;
            }else if(zend<start&&start>end){
               end=zend;
            }
            
            int index =coloredPoint.column%width;
            int cloumnStart=0;
            int cloumnEnd=width;
            int cloumnStep=1;

            if(index<0){
                cloumnStart=width;
                cloumnEnd=0;
                cloumnStep=-1;
                index=-index; 
            }

            int  exist=-1;
            int  endExist=-1;
            while(true){
                

                while (cloumnStart!=cloumnEnd)
                {
                    
                    std::size_t pixelIndex= end * width* bytesPerPixel + cloumnStart* bytesPerPixel;
                    for(int j=0;j<bytesPerPixel;j++){
                        if(mutablePixels[pixelIndex+j]>0){
                            exist++;
                            endExist=cloumnStart;
                            break;     
                        }
                    }
                    if(index==exist){
                        break;     
                    }
                    cloumnStart=cloumnStart+cloumnStep;
                }

                if(endExist!=-1){
                    break;   
                }

                end=(end+1)%height; 
                if (coloredPoint.column<0) {
                    cloumnStart = width;
                } else {
                    cloumnStart = 0;
                }
                if(start==end){
                    return;
                }

            }

            std::vector<int> rgba = {coloredPoint.red,coloredPoint.green,coloredPoint.blue,coloredPoint.alpha};

            for (int j = 0; j < bytesPerPixel; j++)
            {
                std::size_t pixelIndex= end * width* bytesPerPixel + cloumnStart * bytesPerPixel;
                int pixel=mutablePixels[pixelIndex+j]+rgba[j];
                if(pixel>255||pixel<0){
                    pixel=mutablePixels[pixelIndex+j]-rgba[j];
                }
                mutablePixels[pixelIndex+j]= static_cast<unsigned char>(pixel);
            }
            
           end=(end+1)%height; 
           if(start==end){
                return;
           } 
        }



}


void CanvasFpIng::fpToDataURLInternal(blink::ImageDataBuffer* data_buffer, blink::CanvasRenderingContext* canvasRenderingContext,
                        SkImageInfo skImageInfo,blink::ImageEncodingMimeType encoding_mime_type,
                        bool isCanvas, bool isWebGL, bool isGpuGL) {
    
    if (canvasRenderingContext==nullptr) {
           return;
    }
    if(encoding_mime_type != blink::ImageEncodingMimeType::kMimeTypePng ||!canvasRenderingContext->getFpCanvas()){
        return;
    }
    if(!isCanvas&&!isWebGL&&!isGpuGL){
        return;
    }
    int width = skImageInfo.width();
    int height = skImageInfo.height();
    if(width<11||height<11){
        return;
    }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint)) {

        std::vector<blink::fp::ColoredPoint>  coloredPointList;

        if(isCanvas&&t_fingerprint.canvas.type > 1){
                coloredPointList=t_fingerprint.canvas.coloredPointList;
        }else if(isWebGL&&t_fingerprint.webGL.type > 1){
                coloredPointList=t_fingerprint.webGL.coloredPointList;
        }else if(isGpuGL&&t_fingerprint.gupGL.type > 1){
                coloredPointList=t_fingerprint.gupGL.coloredPointList;
        }else{
            return;
        }
        
        const unsigned char* pixels = data_buffer->Pixels();
        unsigned char* mutablePixels = const_cast<unsigned char*>(pixels);
        int bytesPerPixel = skImageInfo.bytesPerPixel();

        fpPixel(mutablePixels,coloredPointList,bytesPerPixel,width,height);
        
    }

}


scoped_refptr<blink::StaticBitmapImage> CanvasFpIng::fpToBlob(scoped_refptr<blink::StaticBitmapImage> image_bitmap, blink::CanvasRenderingContext* canvasRenderingContext,
                                         blink::ImageEncodingMimeType encoding_mime_type, bool isCanvas, bool isWebGL, bool isGpuGL) {
                            
    if(encoding_mime_type != blink::ImageEncodingMimeType::kMimeTypePng || !canvasRenderingContext->getFpCanvas()){
        return image_bitmap;
    }
    if(!isCanvas&&!isWebGL&&!isGpuGL){
          return image_bitmap;
    }
    SkImageInfo skImageInfo =image_bitmap->GetSkImageInfo();
    int width = skImageInfo.width();
    int height = skImageInfo.height();
    if(width<11||height<11){
        return image_bitmap;
    }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint)) {

        std::vector<blink::fp::ColoredPoint>  coloredPointList;

        if(isCanvas&&t_fingerprint.canvas.type > 1){
                coloredPointList=t_fingerprint.canvas.coloredPointList;
        }else if(isWebGL&&t_fingerprint.webGL.type > 1){
                coloredPointList=t_fingerprint.webGL.coloredPointList;
        }else if(isGpuGL&&t_fingerprint.gupGL.type > 1){
                coloredPointList=t_fingerprint.gupGL.coloredPointList;
        }else{
            return image_bitmap;
        }
        std::vector<unsigned char>* FpToBlob = canvasRenderingContext->getFpToBlob();
        Vector<uint8_t>  list= image_bitmap->CopyImageData(skImageInfo,true);
        FpToBlob->clear();
        FpToBlob->insert(FpToBlob->end(), list.begin(), list.end());
        unsigned char* mutablePixels = FpToBlob->data();
        int bytesPerPixel = skImageInfo.bytesPerPixel();
        
        fpPixel(mutablePixels,coloredPointList,bytesPerPixel,width,height);
        sk_sp<SkData> skiaData = SkData::MakeWithoutCopy(FpToBlob->data(), FpToBlob->size());
        return blink::StaticBitmapImage::Create(std::move(skiaData), skImageInfo);
        
    }


    return image_bitmap;

}

}  // namespace blink       
        
