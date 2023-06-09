/*
 *
 * Copyright (C) 2015 Allwinnertech Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SUNXI_LRADC_H
#define SUNXI_LRADC_H

#define INPUT_DEV_NAME          ("sunxi-keyboard")

#define KEY_MAX_CNT             (13)

#define LRADC_CTRL              (0x00)
#define LRADC_INTC              (0x04)
#define LRADC_INT_STA           (0x08)
#define LRADC_DATA0             (0x0c)
#define LRADC_DATA1             (0x10)

#define FIRST_CONVERT_DLY       (0<<24)
#define CHAN                    (0x0)
#define ADC_CHAN_SELECT         (CHAN<<22)
#define LRADC_KEY_MODE          (0)
#define KEY_MODE_SELECT         (LRADC_KEY_MODE<<12)
#define LRADC_HOLD_KEY_EN	(0<<7)
#define LRADC_HOLD_EN	        (1<<6)
#define LEVELB_CNT		(0<<8)
#define LEVELB_VOL              (0<<4)
#define LRADC_SAMPLE_32HZ       (3<<2)
#define LRADC_SAMPLE_62HZ       (2<<2)
#define LRADC_SAMPLE_125HZ      (1<<2)
#define LRADC_SAMPLE_250HZ      (0<<2)
#define LRADC_EN                (1<<0)

#define FIRST_CONVERT_DLY_MASK  (0xff<<24)
#define KEY_MODE_SELECT_MASK    (0x03<<12)
#define LRADC_HOLD_KEY_EN_MASK	(0x01<<7)
#define LRADC_HOLD_EN_MASK      (0x01<<6)
#define LEVELB_CNT_MASK		(0x0f<<8)
#define LEVELB_VOL_MASK	        (0x03<<4)
#define LRADC_SAMPLE_250HZ_MASK (0x03<<2)
#define LRADC_EN_MASK	        (0x01<<0)

#define LRADC_ADC1_UP_EN        (1<<12)
#define LRADC_ADC1_DOWN_EN      (1<<9)
#define LRADC_ADC1_DATA_EN      (1<<8)

#define LRADC_ADC0_UP_EN        (1<<4)
#define LRADC_ADC0_DOWN_EN      (1<<1)
#define LRADC_ADC0_DATA_EN      (1<<0)

#define LRADC_ADC0_UP_EN_MASK	(0x01<<4)
#define LRADC_ADC0_DOWN_EN_MASK	(0x01<<1)
#define LRADC_ADC0_DATA_EN_MASK	(0x01<<1)

#define LRADC_ADC1_UPPEND       (1<<12)
#define LRADC_ADC1_DOWNPEND     (1<<9)
#define LRADC_ADC1_DATAPEND     (1<<8)


#define LRADC_ADC0_UPPEND       (1<<4)
#define LRADC_ADC0_DOWNPEND     (1<<1)
#define LRADC_ADC0_DATAPEND     (1<<0)

#define ONE_CHANNEL
#define MODE_0V2

#ifdef MODE_0V2
/* standard of key maping
 * 0.2V mode
 */
#define REPORT_KEY_LOW_LIMIT_COUNT  (1)

#endif

struct sunxi_adc_disc {
	u32 measure;
	u32 resol;
};

#endif