#ifndef CONTENT_CHILD_DWRITE_FONT_PROXY_FP_DWITE_FONT_H_
#define CONTENT_CHILD_DWRITE_FONT_PROXY_FP_DWITE_FONT_H_

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

void fpLoadFamilyCoreLockRequired(UINT32* index,std::u16string* name){
    // base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    // blink::fp::Fingerprint t_fingerprint = t_singletonFingerprint->GetFingerprint();
    
    // if (base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type ==3) {
    //     base::flat_map<int, std::string>& fontIdMap = t_fingerprint.font.fontIdMap;
    //     auto iter = fontIdMap.find(*index);
        
    //     if (iter != fontIdMap.end()) {
    //         *index = static_cast<UINT32>(t_fingerprint.font.defaultId);
    //         *name = std::u16string(t_fingerprint.font.defaultName.begin(), t_fingerprint.font.defaultName.end());
    //     }
    // }
}
#endif // CONTENT_CHILD_DWRITE_FONT_PROXY_FP_DWITE_FONT_H_