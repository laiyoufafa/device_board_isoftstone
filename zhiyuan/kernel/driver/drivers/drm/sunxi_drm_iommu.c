/* sunxi_drm_iommu.c
 *
 * Copyright (C) 2022 Allwinnertech Co., Ltd.
 * Authors: hongyaobin <hongyaobin@allwinnertech.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */


#include <drm/drmP.h>
#include <uapi/drm/sunxi_drm.h>


#include <linux/dma-mapping.h>
#include <linux/iommu.h>

#include "sunxi_drm_drv.h"
#include "sunxi_drm_iommu.h"

/* dram space, according to the memory mapping spec */
#define SUNXI_DEV_ADDR_START	0x40000000

static inline int configure_dma_max_seg_size(struct device *dev)
{
	if (!dev->dma_parms)
		dev->dma_parms = kzalloc(sizeof(*dev->dma_parms), GFP_KERNEL);
	if (!dev->dma_parms)
		return -ENOMEM;

	dma_set_max_seg_size(dev, DMA_BIT_MASK(32));
	return 0;
}

static inline void clear_dma_max_seg_size(struct device *dev)
{
	kfree(dev->dma_parms);
	dev->dma_parms = NULL;
}

/*
 * sunxi_drm_create_iommu_mapping - create a mapping structure
 *
 * @drm_dev: DRM device
 */
int sunxi_drm_create_iommu_mapping(struct drm_device *drm_dev)
{
	struct sunxi_drm_private *priv = drm_dev->dev_private;

	return __sunxi_iommu_create_mapping(priv, SUNXI_DEV_ADDR_START,
					     SZ_4G);
}

/*
 * sunxi_drm_release_iommu_mapping - release iommu mapping structure
 *
 * @drm_dev: DRM device
 */
void sunxi_drm_release_iommu_mapping(struct drm_device *drm_dev)
{
	struct sunxi_drm_private *priv = drm_dev->dev_private;

	__sunxi_iommu_release_mapping(priv);
}

/*
 * sunxi_drm_iommu_attach_device- attach device to iommu mapping
 *
 * @drm_dev: DRM device
 * @subdrv_dev: device to be attach
 *
 * This function should be called by sub drivers to attach it to iommu
 * mapping.
 */
int sunxi_drm_iommu_attach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct sunxi_drm_private *priv = drm_dev->dev_private;
	int ret;

	if (get_dma_ops(drm_dev->dev) != get_dma_ops(subdrv_dev)) {
		DRM_ERROR("Device %s lacks support for IOMMU\n",
			  dev_name(subdrv_dev));
		return -EINVAL;
	}

	ret = configure_dma_max_seg_size(subdrv_dev);
	if (ret)
		return ret;

	ret = __sunxi_iommu_attach(priv, subdrv_dev);
	if (ret)
		clear_dma_max_seg_size(subdrv_dev);

	return 0;
}

/*
 * sunxi_drm_iommu_detach_device -detach device address space mapping from device
 *
 * @drm_dev: DRM device
 * @subdrv_dev: device to be detached
 *
 * This function should be called by sub drivers to detach it from iommu
 * mapping
 */
void sunxi_drm_iommu_detach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct sunxi_drm_private *priv = drm_dev->dev_private;

	__sunxi_iommu_detach(priv, subdrv_dev);
	clear_dma_max_seg_size(subdrv_dev);
}
