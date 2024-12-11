#ifndef COMPONENTS_LANGUAGE_CORE_BROWSER_FP_LANGUAGE_H_
#define COMPONENTS_LANGUAGE_CORE_BROWSER_FP_LANGUAGE_H_

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

void setLlanguage(PrefService* user_prefs) {
    //在启动的时候  需要加上 --lang=en-US  t_fingerprint.interfaceLanguage
    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.language.type>1){
            std::string languages;
            for (const std::string& t_language : t_fingerprint.language.languages) {
                languages.append(t_language);
                languages.append(",");
            }
            languages = languages.substr(0, languages.length() - 1);
            user_prefs->SetString(language::prefs::kAcceptLanguages,languages);
        }

}
#endif // COMPONENTS_LANGUAGE_CORE_BROWSER_FP_LANGUAGE_H_