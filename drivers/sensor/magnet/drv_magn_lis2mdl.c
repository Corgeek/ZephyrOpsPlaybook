/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/rtio/rtio.h>
#include <zephyr/drivers/sensor.h>
#include <assert.h>
#include "drivers/sensor/magnet/drv_magn_lis2mdl.h"

const struct gpio_dt_spec *const magnet_spec(void)
{
    static struct gpio_dt_spec s_magn0_spec = GPIO_DT_SPEC_GET(DT_ALIAS(magn0), irq_gpios);
    return &s_magn0_spec;
}

int get_magnet_xyz(struct sensor_3axis *data)
{
    assert(data);
    int ret;

    ret = sensor_sample_fetch(magnet_spec()->port);
    if (ret < 0) {
		printk("%s: sensor_sample_fetch() failed: %d\n", magnet_spec()->port->name, ret);
		return ret;
	}

    ret = sensor_channel_get(magnet_spec()->port, SENSOR_CHAN_MAGN_XYZ, data->array);
    if (ret < 0) {
        printk("%s: sensor_channel_get(XYZ) failed: %d\n", magnet_spec()->port->name, ret);
        return ret;
    }

    return 0;
}

bool drv_init_magnet(void)
{
    if (device_is_ready(magnet_spec()->port) == false) {
        printk("%s: sensor device is not ready.\n", magnet_spec()->port->name);
        return false;
    }

    return true;
}
