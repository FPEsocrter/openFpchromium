#ifndef CHROME_BROWSER_FP_PROFILE_H_
#define CHROME_BROWSER_FP_PROFILE_H_

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "third_party/blink/public/common/peerconnection/webrtc_ip_handling_policy.h"

void fpInitFontDefaultInfo(){
    
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.font.type > 1){
        t_singletonFingerprint->setFontDefaultInfo(30, "Microsoft YaHei");
    }
   

}

void fpDoNotTrack(Profile* profile){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.doNotTrack.type >1 ){
         profile->GetPrefs()->SetBoolean(prefs::kEnableDoNotTrack,t_fingerprint.doNotTrack.flag);
    }

}

void fpWebRtc(Profile* profile){

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.webRTC.type >1 ){
         if (t_fingerprint.webRTC.type == 3) {
             profile->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy,
                          blink::kWebRTCIPHandlingDisableNonProxiedUdp); //直接udp代理 参考Brave 
        } else if (t_fingerprint.webRTC.type == 4) {
              profile->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy,
                          blink::kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces); //处理默认和私有端口 参考Brave 
        } else if (t_fingerprint.webRTC.type == 5) {
              profile->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy, 
                          blink::kWebRTCIPHandlingDefaultPublicInterfaceOnly); //处理私有端口  参考Brave 
        }else{
            profile->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy,blink::kWebRTCIPHandlingDefault); 
        }
       
    }else{
         profile->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy,blink::kWebRTCIPHandlingDefault); 
    }
}


void fpProfile(Profile* profile){
    fpInitFontDefaultInfo();
    fpDoNotTrack(profile);
    fpWebRtc(profile);
}

#endif  // CHROME_BROWSER_FP_PROFILE_H_