#include "base/singleton_fingerprint.h"

#include "base/check_op.h"
#include <json/json.h>
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"


namespace base{


SingletonFingerprint* SingletonFingerprint::singletonFingerprint_= nullptr;

namespace {

}  // namespace

SingletonFingerprint::SingletonFingerprint() = default;

SingletonFingerprint::SingletonFingerprint(const SingletonFingerprint& other) = default;

SingletonFingerprint& SingletonFingerprint::operator=(const SingletonFingerprint& other) = default;

SingletonFingerprint::~SingletonFingerprint() = default;

// static
bool SingletonFingerprint::Init() {
    if (singletonFingerprint_) {
        return false;
    }
    singletonFingerprint_ = new SingletonFingerprint();
    blink::fp::Fingerprint fingerprint;
    fingerprint.init = 0;
    singletonFingerprint_->fingerprint_ =fingerprint;
    singletonFingerprint_->init_ = true;
    return true;
}

// static
bool SingletonFingerprint::Init(const blink::fp::Fingerprint& inputFingerprint) {
    if (!singletonFingerprint_) {
        singletonFingerprint_ = new SingletonFingerprint();
    }
    singletonFingerprint_->fingerprint_ = inputFingerprint;
    singletonFingerprint_->init_ = true;
    return true;
}

// static
SingletonFingerprint* SingletonFingerprint::ForCurrentProcess(){
  /*  if (singletonFingerprint_) {
        return singletonFingerprint_;
    }
    singletonFingerprint_ = new SingletonFingerprint();
    blink::fp::Fingerprint fingerprint;
    fingerprint.init = 0;
    singletonFingerprint_->fingerprint_ = fingerprint;
    singletonFingerprint_->init_ = true;*/
    DCHECK(singletonFingerprint_);
   return singletonFingerprint_;    
}

}  // namespace base

