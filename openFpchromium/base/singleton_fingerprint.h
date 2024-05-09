#ifndef BASE_SINGLETON_FINGERPRINT_H_
#define BASE_SINGLETON_FINGERPRINT_H_

#include <string>
#include "base/debug/debugging_buildflags.h"
//#include "build/build_config.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/base_export.h"


namespace base {

class BASE_EXPORT SingletonFingerprint {
public:
    SingletonFingerprint();
    SingletonFingerprint(const SingletonFingerprint& other);
    SingletonFingerprint& operator=(const SingletonFingerprint& other);
    ~SingletonFingerprint();

    bool GetInit() const { return init_; }
    const blink::fp::Fingerprint& GetFingerprint() const {
        return fingerprint_;
    }

    bool setFontDefaultInfo(int index, std::string name){
        fingerprint_.font.defaultId = index;
        fingerprint_.font.defaultName = name;
        return true;
    }
   
    static bool GetInit(SingletonFingerprint* singletonFingerprint){
        if(!singletonFingerprint->GetInit()){
            return false;
        }
        if(singletonFingerprint->GetFingerprint().init<2){
            return false;
        }
        return true; 
    
    }
    static bool Init();
    static bool Init(const blink::fp::Fingerprint& inputFingerprint);
    static SingletonFingerprint* ForCurrentProcess();

   
private:
    bool init_ = false;
    blink::fp::Fingerprint fingerprint_;
    static SingletonFingerprint* singletonFingerprint_;
    //InstanceBoundSequenceChecker sequence_checker_;

};
}  // namespace base
#endif  // BASE_SINGLETON_FINGERPRINT_H_

