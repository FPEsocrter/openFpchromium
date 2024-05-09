// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_FP_PROXYING_URL_LOADER_FACTORY_H_
#define CHROME_BROWSER_NET_FP_PROXYING_URL_LOADER_FACTORY_H_

#include "base/memory/weak_ptr.h"
#include "mojo/public/cpp/bindings/receiver_set.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "mojo/public/cpp\bindings\pending_remote.h"
#include "services/network/public/mojom/url_loader_factory.mojom.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/mojom/url_loader.mojom.h"

#include "url/gurl.h"

namespace embedder_support {
class WebResourceResponse;
}

namespace fp {

class FpProxyingURLLoaderFactoryImpl : public network::mojom::URLLoaderFactory {
 public:
  FpProxyingURLLoaderFactoryImpl(
      mojo::PendingReceiver<network::mojom::URLLoaderFactory> loader_receiver,
      mojo::PendingRemote<network::mojom::URLLoaderFactory> target_factory_remote);

  FpProxyingURLLoaderFactoryImpl(const FpProxyingURLLoaderFactoryImpl&) = delete;
  FpProxyingURLLoaderFactoryImpl& operator=(const FpProxyingURLLoaderFactoryImpl&) = delete;

  void CreateLoaderAndStart(
      mojo::PendingReceiver<network::mojom::URLLoader> loader,
      int32_t request_id,
      uint32_t options,
      const network::ResourceRequest& request,
      mojo::PendingRemote<network::mojom::URLLoaderClient> client,
      const net::MutableNetworkTrafficAnnotationTag& traffic_annotation) override;

  void Clone(mojo::PendingReceiver<network::mojom::URLLoaderFactory> loader_receiver) override;

 private:
  ~FpProxyingURLLoaderFactoryImpl() override;
  void OnTargetFactoryError();
  void OnProxyBindingError();
  

  mojo::ReceiverSet<network::mojom::URLLoaderFactory> proxy_receivers_;
  mojo::Remote<network::mojom::URLLoaderFactory> target_factory_;
  
  base::WeakPtrFactory<FpProxyingURLLoaderFactoryImpl> weak_factory_;
};

}  // namespace fp

#endif  // CHROME_BROWSER_NET_FP_PROXYING_URL_LOADER_FACTORY_H_
