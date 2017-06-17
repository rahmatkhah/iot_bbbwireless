/*
 * AD1938/AD1939 audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 *
 * Licensed under the GPL-2.
 */

#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/regmap.h>

#include <sound/soc.h>

#include "ad193x.h"

static int ad193x_spi_probe(struct spi_device *spi)
{
	struct regmap_config config;

	config = ad193x_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 16;
	config.read_flag_mask = 0x09;
	config.write_flag_mask = 0x08;

	return ad193x_probe(&spi->dev, devm_regmap_init_spi(spi, &config));
}

static int ad193x_spi_remove(struct spi_device *spi)
{
	snd_soc_unregister_codec(&spi->dev);
	return 0;
}

static const struct spi_device_id ad193x_spi_id[] = {
	{ "ad1938", },
	{ "ad1939", },
	{ },
};
MODULE_DEVICE_TABLE(spi, ad193x_spi_id);

static const struct of_device_id ad193x_of_match[] = {
	{ .compatible = "analog,ad1938", },
	{ .compatible = "analog,ad1939", },
	{ }
};
MODULE_DEVICE_TABLE(of, ad193x_of_match);

static struct spi_driver ad193x_spi_driver = {
	.driver = {
		.name	= "ad193x",
		.owner	= THIS_MODULE,
		.of_match_table = ad193x_of_match,
	},
	.probe		= ad193x_spi_probe,
	.remove		= ad193x_spi_remove,
	.id_table	= ad193x_spi_id
};
module_spi_driver(ad193x_spi_driver);

MODULE_DESCRIPTION("ASoC AD1938/AD1939 audio CODEC driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
