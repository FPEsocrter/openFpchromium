// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/navigator_concurrent_hardware.h"

#include "base/system/sys_info.h"

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

namespace blink {

unsigned NavigatorConcurrentHardware::hardwareConcurrency() const {
     base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
     blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
     if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.resourceInfo.type>1){
        return static_cast<unsigned>(t_fingerprint.resourceInfo.cpu);
     }
  return static_cast<unsigned>(base::SysInfo::NumberOfProcessors());
}

}  // namespace blink
