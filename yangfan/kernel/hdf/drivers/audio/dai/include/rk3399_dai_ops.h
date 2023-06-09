/*
 * Copyright (c) 2021 iSoftStone Device Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#ifndef RK3399_DAI_OPS_H
#define RK3399_DAI_OPS_H

#include "audio_core.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

int32_t DaiDeviceInit(struct AudioCard *audioCard, const struct DaiDevice *dai);
int32_t DaiStartup(const struct AudioCard *card, const struct DaiDevice *device);
int32_t DaiHwParams(const struct AudioCard *card, const struct AudioPcmHwParams *param);
int32_t DaiTrigger(const struct AudioCard *card, int cmd, const struct DaiDevice *device);
int32_t DaiDeviceReadReg(unsigned long virtualAddress, uint32_t reg, uint32_t *val);
int32_t DaiDeviceWriteReg(unsigned long virtualAddress, uint32_t reg, uint32_t value);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* HI3516_CODEC_OPS_H */
