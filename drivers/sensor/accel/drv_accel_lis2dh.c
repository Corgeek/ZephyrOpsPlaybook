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
#include "drivers/sensor/accel/drv_accel_lis2dh.h"

const struct gpio_dt_spec s_accel0_spec = GPIO_DT_SPEC_GET(DT_ALIAS(accel0), irq_gpios);

int get_accel_xyz(struct sensor_value *ax, struct sensor_value *ay, struct sensor_value *az)
{
    assert(ax);
    assert(ay);
    assert(az);

    struct sensor_value accel[3];
    int ret;

    ret = sensor_sample_fetch(s_accel0_spec.port);
    if (ret < 0) {
		printk("%s: sensor_sample_fetch() failed: %d\n", s_accel0_spec.port->name, ret);
		return ret;
	}

    ret = sensor_channel_get(s_accel0_spec.port, SENSOR_CHAN_ACCEL_XYZ, accel);
    if (ret < 0) {
        printk("%s: sensor_channel_get(XYZ) failed: %d\n", s_accel0_spec.port->name, ret);
        return ret;
    }

    *ax = accel[0];
    *ay = accel[1];
    *az = accel[2];

    return 0;
}

bool drv_init_accel(void)
{
    if (device_is_ready(s_accel0_spec.port) == false) {
        printk("%s: sensor device is not ready.\n", s_accel0_spec.port->name);
        return false;
    }

    struct sensor_value odr;

    if (sensor_attr_get(s_accel0_spec.port, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr) != 0) {
        printk("%s : failed to get sampling frequency\n", s_accel0_spec.port->name);
        return false;
    }

    odr.val1 = SENSOR_ACCEL_FREQ_HZ;
    odr.val2 = 0;
    if (sensor_attr_set(s_accel0_spec.port, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr) != 0) {
        printk("%s : failed to set sampling frequency\n", s_accel0_spec.port->name);
        return false;
    }

    return true;
}
