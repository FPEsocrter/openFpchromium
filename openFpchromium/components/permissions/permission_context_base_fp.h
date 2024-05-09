#ifndef COMPONENTS_PERMISSIONS_PERMISSION_CONTEXT_BASE_FP_H_
#define COMPONENTS_PERMISSIONS_PERMISSION_CONTEXT_BASE_FP_H_

#include "base/singleton_fingerprint.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "third_party/blink/public/mojom/permissions_policy/permissions_policy_feature.mojom-forward.h"

bool requestPermissionFp(
    blink::mojom::PermissionsPolicyFeature permissions_policy_feature_) {
    if (blink::mojom::PermissionsPolicyFeature::kGeolocation != permissions_policy_feature_) {
      return false;
    }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint t_fingerprint = t_singletonFingerprint->GetFingerprint();

    if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) &&
        t_fingerprint.location.type > 1 && t_fingerprint.location.permissions) {
            return true;
     }
    return false;
}

#endif // COMPONENTS_PERMISSIONS_PERMISSION_CONTEXT_BASE_FP_H_

