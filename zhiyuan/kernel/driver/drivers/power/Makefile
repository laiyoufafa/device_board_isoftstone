# SPDX-License-Identifier: GPL-2.0-only

obj-$(CONFIG_AW_MFD_AXP2101)		+= mfd/axp2101.o
obj-$(CONFIG_AW_MFD_AXP2101_I2C)	+= mfd/axp2101-i2c.o

obj-$(CONFIG_AW_REGULATOR_AXP2101)	+= regulator/axp2101-regulator.o

obj-$(CONFIG_AW_AXP803_POWER)		+= supply/axp803_usb_power.o
obj-$(CONFIG_AW_AXP803_POWER)		+= supply/axp803_ac_power.o
obj-$(CONFIG_AW_AXP803_POWER)		+= supply/axp803_battery.o
obj-$(CONFIG_AW_AXP2202_POWER)		+= supply/axp2202_usb_power.o
obj-$(CONFIG_AW_AXP2202_POWER)		+= supply/axp2202_battery.o
obj-$(CONFIG_AW_AXP2202_GPIO_POWER) += supply/axp2202_gpio_power.o

obj-$(CONFIG_AW_INPUT_AXP2101_PEK)	+= power_key/axp2101-pek.o

ccflags-y += -I $(srctree)/include/linux/power