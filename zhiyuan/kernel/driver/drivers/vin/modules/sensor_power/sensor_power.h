/*
 * cameras power on and off drivers.
 *
 * Copyright (c) 2019 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Authors:  Zheng ZeQun <zequnzheng@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SENSOR__POWER__H__
#define __SENSOR__POWER__H__

#include <linux/gpio.h>
#include <sunxi-gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/pinconf.h>
#include <linux/regulator/consumer.h>

#define SENSOR_DBG_EN   0
#if (SENSOR_DBG_EN == 1)
#define sensor_power_dbg(x, arg...) printk(KERN_DEBUG "[sensor_power_debug]" x, ## arg)
#else
#define sensor_power_dbg(x, arg...)
#endif

#define sensor_power_err(x, arg...) pr_err("[sensor_power_err]" x, ## arg)
#define sensor_power_warn(x, arg...) pr_warn("[sensor_power_warn] "x, ##arg)
#define sensor_power_print(x, arg...) pr_info("[sensor_power]" x, ## arg)

#define SENSOR_GPIO_HIGH     1
#define SENSOR_GPIO_LOW     0
#define MCLK_POWER_3300 0
#define MCLK_POWER_1800 1

struct sensor_power_cfg {
	struct regulator *pmic;
	int power_vol;
};

enum sensor_pmic_channel {
	IOVDD = 0,
	AVDD,
	DVDD,
	AFVDD,
	FLVDD,
	CAMERAVDD,
	MAX_POW_NUM,
};

enum sensor_gpio_type {
	POWER_EN = 0,
	PWDN,
	RESET,
	SM_HS,
	SM_VS,
	AF_PWDN,
	FLASH_EN,
	FLASH_MODE,
	MAX_GPIO_NUM,
};

enum sensor_gpio_fun {
	GPIO_INPUT = 0,
	GPIO_OUTPUT = 1,
	GPIO_DISABLE = 7,
};

enum sensor_on_off {
	OFF,
	ON,
};

struct sensor_mclk_info {
	struct clk *mclk;
	struct clk *clk_24m;
	struct clk *clk_pll;
	struct pinctrl *pin;
	int mclk_id;
	int use_count;
	unsigned long frequency;
};

struct sensor_power_dev {
	struct sensor_power_cfg power[MAX_POW_NUM];
	int gpio[MAX_GPIO_NUM];
	struct sensor_mclk_info mclk;
	struct platform_device *pdev;
	int id;
};

extern int sunxi_sel_pio_mode(struct pinctrl *pinctrl, u32 pm_sel);

#endif

