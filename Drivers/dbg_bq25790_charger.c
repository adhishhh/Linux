// SPDX-License-Identifier: GPL-2.0
// TLV320ADCX140 Sound driver
// Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/

#include <linux/device.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/regmap.h>
#include <linux/slab.h>

#include "bq25790_charger.h"

/* The registers can be accessed via
 * cat /sys/class/i2c-adapter/i2c-2/2-00xx/registers
 * And written through echo for example
 * echo "V_LIM_MSB 0x01" > /sys/class/i2c-adapter/i2c-2/2-00xx/registers
 */
struct bq25790_reg {
	const char *name;
	uint8_t reg;
	int writeable;
} bq25790_regs[] = {
	{ "MIN_SYS_V", BQ25790_MIN_SYS_V, 1 },
	{ "V_LIM_MSB", BQ25790_CHRG_V_LIM_MSB, 1 },
	{ "V_LIM_LSB", BQ25790_CHRG_V_LIM_LSB, 1 },
	{ "I_LIM_MSB", BQ25790_CHRG_I_LIM_MSB, 1 },
	{ "I_LIM_LSB", BQ25790_CHRG_I_LIM_LSB, 1 },
	{ "V_LIM_INPUT", BQ25790_INPUT_V_LIM, 1 },
	{ "I_LIM_INPUT_MSB", BQ25790_INPUT_I_LIM_MSB, 1 },
	{ "I_LIM_INPUT_LSB", BQ25790_INPUT_I_LIM_LSB, 1 },
	{ "PRECHG_CTRL", BQ25790_PRECHRG_CTRL, 1 },
	{ "TERM_CTRL", BQ25790_TERM_CTRL, 1 },
	{ "RECHRG_CTRL", BQ25790_RECHRG_CTRL, 1 },
	{ "VOTG_REG", BQ25790_VOTG_REG, 1 },
	{ "IOTG_REG", BQ25790_IOTG_REG, 1 },
	{ "TIMER_CTRL", BQ25790_TIMER_CTRL, 1 },
	{ "CHRG_CTRL_0", BQ25790_CHRG_CTRL_0, 1 },
	{ "CHRG_CTRL_1", BQ25790_CHRG_CTRL_1, 1 },
	{ "CHRG_CTRL_2", BQ25790_CHRG_CTRL_2, 1 },
	{ "CHRG_CTRL_3", BQ25790_CHRG_CTRL_3, 1 },
	{ "CHRG_CTRL_4", BQ25790_CHRG_CTRL_4, 1 },
	{ "CHRG_CTRL_5", BQ25790_CHRG_CTRL_5, 1 },
	{ "MPPT_CTRL", BQ25790_MPPT_CTRL, 1 },
	{ "TEMP_CTRL", BQ25790_TEMP_CTRL, 1 },
	{ "NTC_CTRL_0", BQ25790_NTC_CTRL_0, 1 },
	{ "NTC_CTRL_1", BQ25790_NTC_CTRL_1, 1 },
	{ "ICO_I_LIM", BQ25790_ICO_I_LIM, 1 },
	{ "CHRG_STAT_0", BQ25790_CHRG_STAT_0, 0 },
	{ "CHRG_STAT_1", BQ25790_CHRG_STAT_1, 0 },
	{ "CHRG_STAT_2", BQ25790_CHRG_STAT_2, 0 },
	{ "CHRG_STAT_3", BQ25790_CHRG_STAT_3, 0 },
	{ "CHRG_STAT_4", BQ25790_CHRG_STAT_4, 0 },
	{ "FAULT_STAT_0", BQ25790_FAULT_STAT_0, 0 },
	{ "FAULT_STAT_1", BQ25790_FAULT_STAT_1, 0 },
	{ "CHRG_FLAG_0", BQ25790_CHRG_FLAG_0, 0 },
	{ "CHRG_FLAG_1", BQ25790_CHRG_FLAG_1, 0 },
	{ "CHRG_FLAG_2", BQ25790_CHRG_FLAG_2, 0 },
	{ "CHRG_FLAG_3", BQ25790_CHRG_FLAG_3, 0 },
	{ "FAULT_FLAG_0", BQ25790_FAULT_FLAG_0, 0 },
	{ "FAULT_FLAG_1", BQ25790_FAULT_FLAG_1, 0 },
	{ "CHRG_MSK_0", BQ25790_CHRG_MSK_0, 1 },
	{ "CHRG_MSK_1", BQ25790_CHRG_MSK_1, 1 },
	{ "CHRG_MSK_2", BQ25790_CHRG_MSK_2, 1 },
	{ "CHRG_MSK_3", BQ25790_CHRG_MSK_3, 1 },
	{ "FAULT_MSK_0", BQ25790_FAULT_MSK_0, 1 },
	{ "FAULT_MSK_1", BQ25790_FAULT_MSK_1, 1 },
	{ "ADC_CTRL", BQ25790_ADC_CTRL, 1 },
	{ "FN_DISABE_0", BQ25790_FN_DISABE_0, 1 },
	{ "FN_DISABE_1", BQ25790_FN_DISABE_1, 1 },
	{ "ADC_IBUS", BQ25790_ADC_IBUS, 1 },
	{ "ADC_IBAT_MSB", BQ25790_ADC_IBAT_MSB, 1 },
	{ "ADC_IBAT_LSB", BQ25790_ADC_IBAT_LSB, 1 },
	{ "ADC_VBUS", BQ25790_ADC_VBUS, 1 },
	{ "ADC_VAC1", BQ25790_ADC_VAC1, 1 },
	{ "ADC_VAC2", BQ25790_ADC_VAC2, 1 },
	{ "ADC_VBAT_MSB", BQ25790_ADC_VBAT_MSB, 1 },
	{ "ADC_VBAT_LSB", BQ25790_ADC_VBAT_LSB, 1 },
	{ "ADC_VSYS_MSB", BQ25790_ADC_VSYS_MSB, 1 },
	{ "ADC_VSYS_LSB", BQ25790_ADC_VSYS_LSB, 1 },
	{ "ADC_TS", BQ25790_ADC_TS, 1 },
	{ "ADC_TDIE", BQ25790_ADC_TDIE, 1 },
	{ "ADC_DP", BQ25790_ADC_DP, 1 },
	{ "ADC_DM", BQ25790_ADC_DM, 1 },
	{ "DAPM_DRV", BQ25790_DPDM_DRV, 1 },
	{ "PART_INFO", BQ25790_PART_INFO, 0 }
};

static ssize_t bq25790_registers_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned i, n, reg_count;
	unsigned int read_buf;
	struct bq25790_device *data = dev_get_drvdata(dev);

	reg_count = sizeof(bq25790_regs) / sizeof(bq25790_regs[0]);
	for (i = 0, n = 0; i < reg_count; i++) {
		regmap_read(data->regmap, bq25790_regs[i].reg, &read_buf);
		n += scnprintf(buf + n, PAGE_SIZE - n,
			       "%-20s = 0x%02X\n",
			       bq25790_regs[i].name,
			       read_buf);
	}
	return n;
}

static ssize_t bq25790_registers_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	unsigned i, reg_count, value;
	int error = 0;
	char name[30];
	struct bq25790_device *data = dev_get_drvdata(dev);

	if (count >= 30) {
		pr_err("%s:input too long\n", __func__);
		return -1;
	}

	if (sscanf(buf, "%s %x", name, &value) != 2) {
		pr_err("%s:unable to parse input\n", __func__);
		return -1;
	}

	reg_count = sizeof(bq25790_regs) / sizeof(bq25790_regs[0]);
	for (i = 0; i < reg_count; i++) {
		if (!strcmp(name, bq25790_regs[i].name)) {
			if (bq25790_regs[i].writeable == 1) {
				error = regmap_write(data->regmap, bq25790_regs[i].reg, value);
				if (error) {
					pr_err("%s:Failed to write %s\n",
						__func__, name);
					return -1;
				}
			} else {
				pr_err("%s:Register %s is not writeable\n",
						__func__, name);
					return -1;
			}
			return count;
		}
	}
	pr_err("%s:no such register %s\n", __func__, name);
	return -1;
}

static DEVICE_ATTR(registers, S_IWUSR | S_IRUGO,
		bq25790_registers_show, bq25790_registers_store);

static struct attribute *bq25790_attrs[] = {
	&dev_attr_registers.attr,
	NULL
};

static const struct attribute_group bq25790_attr_group = {
	.attrs = bq25790_attrs,
};

int bq25790_init_debug(struct bq25790_device *bq25790)
{
	int ret;
	struct bq25790_device *dbg_bq25790 = bq25790;

	ret = sysfs_create_group(&dbg_bq25790->dev->kobj, &bq25790_attr_group);
	if (ret < 0)
		dev_err(dbg_bq25790->dev, "Failed to create sysfs: %d\n", ret);

	return ret;
}
EXPORT_SYMBOL_GPL(bq25790_init_debug);

MODULE_DESCRIPTION("BQ25790 debug");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
