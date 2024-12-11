#ifndef  COMPONENTS_EMBEDDER_SUPPORT_PF_USER_AGENT_METADATA_H_
#define  COMPONENTS_EMBEDDER_SUPPORT_PF_USER_AGENT_METADATA_H_

#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

blink::UserAgentMetadata fpUserAgentMetadata() {
   blink::UserAgentMetadata metadata;
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.uaMetadata.type>1){
          blink::UserAgentMetadata t_metadata = t_fingerprint.uaMetadata.userAgentMetadata;
           for (const blink::UserAgentBrandVersion& brand_version : t_metadata.brand_version_list) {
            metadata.brand_version_list.push_back(brand_version);
          }
          for (const blink::UserAgentBrandVersion& brand_full_version : t_metadata.brand_full_version_list) {
            metadata.brand_full_version_list.push_back(brand_full_version);
          }
          metadata.full_version = t_metadata.full_version;
          metadata.platform = t_metadata.platform;
          metadata.platform_version = t_metadata.platform_version;
          metadata.architecture = t_metadata.architecture;
          metadata.model = t_metadata.model;
          metadata.mobile = t_metadata.mobile;
          metadata.bitness = t_metadata.bitness;
        }

   return metadata;
 
}


#endif // COMPONENTS_EMBEDDER_SUPPORT_PF_USER_AGENT_METADATA_H_