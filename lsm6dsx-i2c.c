#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/regmap.h>
#include "st_lsm6dsx.h"

static int st_lsm6dsx_i2c_probe(struct i2c_client *client)
{
	int hw_id = (kernel_ulong_t)device_get_match_data(&client->dev);
	if (!hw_id)
		hw_id = i2c_client_get_device_id(client)->driver_data;
	if (!hw_id)
		return -EINVAL;

	struct regmap *regmap = devm_regmap_init_i2c(client, &((struct regmap_config){ .reg_bits = 8, .val_bits = 8 }));
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return st_lsm6dsx_probe(&client->dev, client->irq, hw_id, regmap);
}

static const struct of_device_id st_lsm6dsx_i2c_of_match[] = {};
MODULE_DEVICE_TABLE(of, st_lsm6dsx_i2c_of_match);

static const struct acpi_device_id st_lsm6dsx_i2c_acpi_match[] = {
	{ "SMO8B30", ST_LSM6DS3TRC_ID },
	{}
};
MODULE_DEVICE_TABLE(acpi, st_lsm6dsx_i2c_acpi_match);

static const struct i2c_device_id st_lsm6dsx_i2c_id_table[] = {};
MODULE_DEVICE_TABLE(i2c, st_lsm6dsx_i2c_id_table);

static struct i2c_driver st_lsm6dsx_driver = {
	.driver = {
		.name = "st_lsm6dsx_i2c",
		.pm = pm_sleep_ptr(&st_lsm6dsx_pm_ops),
		.of_match_table = st_lsm6dsx_i2c_of_match,
		.acpi_match_table = st_lsm6dsx_i2c_acpi_match,
	},
	.probe = st_lsm6dsx_i2c_probe,
	.id_table = st_lsm6dsx_i2c_id_table,
};

module_i2c_driver(st_lsm6dsx_driver);
