#
# Makefile for the kernel mixer device drivers.
#

include ${obj}/g2d_rcq/Makefile

include ${obj}/g2d_legacy/Makefile


obj-$(CONFIG_AW_G2D) += g2d_sunxi.o

g2d_sunxi-$(CONFIG_G2D_RCQ) += ${rcq_obj}
g2d_sunxi-$(CONFIG_G2D_LEGACY) += ${legacy_obj}

g2d_sunxi-$(CONFIG_G2D_SYNCFENCE) += syncfence.o
