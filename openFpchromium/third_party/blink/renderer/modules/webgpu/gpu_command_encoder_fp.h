// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_COMMAND_ENCODER_FP_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_COMMAND_ENCODER_FP_H_

void fpCopyTextureToBuffer(){ //todo
  // 暂时发现api可以直接读取临时暂存 
  // const void* map_data_const = getProcs.bufferGetConstMappedRange(handle, 0, range_size);
  // if (!map_data_const) {
  //   return;
  // }
  // uint8_t* map_data =const_cast<uint8_t*>(static_cast<const uint8_t*>(map_data_const));

}

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_WEBGPU_GPU_COMMAND_ENCODER_FP_H_
