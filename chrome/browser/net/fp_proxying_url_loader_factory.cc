#include "chrome/browser/net/fp_proxying_url_loader_factory.h"

#include "third_party/blink/public/common/fingerprint/fingerprint.h"
#include "base/singleton_fingerprint.h"

#include "url/gurl.h"
#include "net/base/network_isolation_key.h"
#include <thread>
#include <random>
#include "net/base/url_util.h"
#include "url/third_party/mozilla/url_parse.h"
#include "services/network/public/cpp/url_loader_completion_status.h"


namespace fp {

FpProxyingURLLoaderFactoryImpl::FpProxyingURLLoaderFactoryImpl(
    mojo::PendingReceiver<network::mojom::URLLoaderFactory> loader_receiver,
    mojo::PendingRemote<network::mojom::URLLoaderFactory> target_factory_remote):weak_factory_(this){

  target_factory_.Bind(std::move(target_factory_remote));
  target_factory_.set_disconnect_handler( 
                  base::BindOnce(&FpProxyingURLLoaderFactoryImpl::OnTargetFactoryError,base::Unretained(this) ) );

  proxy_receivers_.Add(this, std::move(loader_receiver));
  proxy_receivers_.set_disconnect_handler(
                  base::BindRepeating(&FpProxyingURLLoaderFactoryImpl::OnProxyBindingError,base::Unretained(this) )  );
}

FpProxyingURLLoaderFactoryImpl::~FpProxyingURLLoaderFactoryImpl() = default;

void FpProxyingURLLoaderFactoryImpl::CreateLoaderAndStart(
    mojo::PendingReceiver<network::mojom::URLLoader> loader,
    int32_t request_id,
    uint32_t options,
    const network::ResourceRequest& request,
    mojo::PendingRemote<network::mojom::URLLoaderClient> client,
    const net::MutableNetworkTrafficAnnotationTag& traffic_annotation) {

  GURL request_url = request.url;
  GURL initiator_url = request.request_initiator.value_or(url::Origin()).GetURL();
   
  if (net::IsLocalhost(request_url) && !net::IsLocalhost(initiator_url)) {

    base::SingletonFingerprint* t_singletonFingerprint = base::SingletonFingerprint::ForCurrentProcess();
    blink::fp::Fingerprint  t_fingerprint = t_singletonFingerprint->GetFingerprint();
        
    if(base::SingletonFingerprint::GetInit(t_singletonFingerprint) && t_fingerprint.openPort.type>1){

      std::vector<int> openPort = t_fingerprint.openPort.openPort;
      int targetPort = request_url.EffectiveIntPort();
      bool portExists = (std::find(openPort.begin(), openPort.end(), targetPort) != openPort.end());
      if(!portExists){
        network::ResourceRequest& request2 =const_cast<network::ResourceRequest&>(request);
        request2.url = GURL(t_fingerprint.openPort.url);   
      }
    }
    
  }
  
  target_factory_->CreateLoaderAndStart(std::move(loader), request_id, options,
                                        request, std::move(client),
                                        traffic_annotation);
}

void FpProxyingURLLoaderFactoryImpl::Clone(mojo::PendingReceiver<network::mojom::URLLoaderFactory> loader_receiver) {

    proxy_receivers_.Add(this, std::move(loader_receiver));
}


void FpProxyingURLLoaderFactoryImpl::OnTargetFactoryError() {
  delete this;
}

void FpProxyingURLLoaderFactoryImpl::OnProxyBindingError() {
  if (proxy_receivers_.empty())
    delete this;
}


}  // namespace fp
