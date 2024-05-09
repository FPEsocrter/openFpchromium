#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_GEOLOCATION_FP_GEOLOCATION_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_GEOLOCATION_FP_GEOLOCATION_H_

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

#include "third_party/blink/renderer/modules/geolocation/geoposition.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/modules/geolocation/geolocation_coordinates.h"
#include "third_party/blink/renderer/core/timing/epoch_time_stamp.h"
#include "base/time/time.h"

bool fpOnPositionUpdated(){
  base::SingletonFingerprint* t_singletonFingerprint =base::SingletonFingerprint::ForCurrentProcess();
  blink::fp::Fingerprint t_fingerprint =t_singletonFingerprint->GetFingerprint();
  if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.location.type > 1) {
    return true;
  }
  return false;
}


blink::Geoposition* fpCreateGeoposition() {

  base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
  blink::fp::Fingerprint t_fingerprint =t_singletonFingerprint->GetFingerprint();
  blink::fp::Location location = t_fingerprint.location;
    
  blink::GeolocationCoordinates* coordinates = blink::MakeGarbageCollected<blink::GeolocationCoordinates>(
      location.latitude, location.longitude, false, 0.0, location.accuracy,
      false, 0.0,
      false, 0.0,
      false, 0.0);
 
	return blink::MakeGarbageCollected<blink::Geoposition>(coordinates, blink::ConvertTimeToEpochTimeStamp(base::Time::Now()));

} 

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_GEOLOCATION_FP_GEOLOCATION_H_
