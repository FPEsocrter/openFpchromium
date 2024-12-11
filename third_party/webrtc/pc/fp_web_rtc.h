
#ifndef PC_FP_WEB_RTC_H_
#define PC_FP_WEB_RTC_H_

#include "rtc_base/socket_address.h"
#include "rtc_base/ip_address.h"
#include "rtc_base/string_encode.h"
#include "p2p/base/ice_transport_internal.h"
#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"


cricket::Candidates FpWebRtc(const cricket::Candidates& candidates){
   if(candidates.empty()||candidates.size()<1){
        return candidates;
   }

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.webRTC.type==2){

            cricket::Candidates candidates_proxy;
            for (const cricket::Candidate& candidate : candidates) {
                cricket::Candidate candidate2=cricket::Candidate(candidate);
                
               if(!candidate.related_address().IsNil()){
                      rtc::IPAddress ip_address;
                    if (rtc::IPFromString(t_fingerprint.webRTC.publicIp, &ip_address)) {
                        candidate2.set_address(rtc::SocketAddress(ip_address, candidate.address().port()));

                    }
                    rtc::IPAddress related_address;
                    if (rtc::IPFromString(t_fingerprint.webRTC.privateIp, &related_address)) {
                        candidate2.set_related_address(rtc::SocketAddress(related_address, candidate.related_address().port()));

                    }
                }else{
                    rtc::IPAddress ip_address;
                    if (rtc::IPFromString(t_fingerprint.webRTC.privateIp, &ip_address)) {
                        candidate2.set_address(rtc::SocketAddress(ip_address, candidate.address().port()));

                    }
                }
                candidates_proxy.push_back(candidate2);
        }
        return candidates_proxy;

    }else{
        return candidates;
    }

   
   
    

   
}
#endif // PC_FP_WEB_RTC_H_