/*
 * Copyright (c) 2021 iSoftStone Device Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include "audio_dsp_base.h"
#include "audio_core.h"
#include "dsp_ops.h"
#include "audio_dsp_if.h"
#include "audio_driver_log.h"
#include "osal_io.h"

#define HDF_LOG_TAG dsp_adapter

struct DspData g_dspData = {
    .DspInit    = DspDeviceInit,
    .Read       = DspDeviceReadReg,
    .Write      = DspDeviceWriteReg,
    .Decode     = DspDecodeAudioStream,
    .Encode     = DspEncodeAudioStream,
    .Equalizer  = DspEqualizerActive,
};

struct AudioDaiOps g_dspDaiDeviceOps = {
    .Startup    = DspDaiStartup,
    .HwParams   = DspDaiHwParams,
};

struct DaiData g_dspDaiData = {
    .DaiInit    = DspDaiDeviceInit,
    .ops        = &g_dspDaiDeviceOps,
};

static int32_t DspDriverBind(struct HdfDeviceObject *device)
{
    struct AudioHost *audioHost;

    AUDIO_DRIVER_LOG_DEBUG("entry");

    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("device is NULL.");
        return HDF_ERR_INVALID_OBJECT;
    }

    audioHost = AudioHostCreateAndBind(device);
    if (audioHost == NULL) {
        AUDIO_DRIVER_LOG_ERR("audioHost create failed!");
        return HDF_FAILURE;
    }

    AUDIO_DRIVER_LOG_DEBUG("success");
    return HDF_SUCCESS;
}

static int32_t DspDriverInit(struct HdfDeviceObject *device)
{
    int32_t ret;

    AUDIO_DRIVER_LOG_DEBUG("entry");

    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("device is NULL.");
        return HDF_ERR_INVALID_OBJECT;
    }

    ret = DspGetServiceName(device, &g_dspData.drvDspName);
    if (ret != HDF_SUCCESS) {
        return ret;
    }

    ret = DspGetDaiName(device, &g_dspDaiData.drvDaiName);
    if (ret != HDF_SUCCESS) {
        return ret;
    }

    ret = AudioRegisterDsp(device, &g_dspData, &g_dspDaiData);
    if (ret !=  HDF_SUCCESS) {
        return ret;
    }

    AUDIO_DRIVER_LOG_DEBUG("success");
    return HDF_SUCCESS;
}


static void DspDriverRelease(struct HdfDeviceObject *device)
{
    struct DspHost *dspHost;

    AUDIO_DRIVER_LOG_DEBUG("entry");
    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("device is NULL");
        return;
    }

    dspHost = (struct DspHost *)device->service;
    if (dspHost == NULL) {
        AUDIO_DRIVER_LOG_ERR("DspHost is NULL");
        return;
    }
    if (dspHost->priv != NULL) {
        OsalMemFree(dspHost->priv);
    }
    OsalMemFree(dspHost);
    AUDIO_DRIVER_LOG_DEBUG("success");
}

/* HdfDriverEntry definitions */
struct HdfDriverEntry g_dspDriverEntry = {
    .moduleVersion  = 1,
    .moduleName     = "DSP_T507",
    .Bind           = DspDriverBind,
    .Init           = DspDriverInit,
    .Release        = DspDriverRelease,
};
HDF_INIT(g_dspDriverEntry);
