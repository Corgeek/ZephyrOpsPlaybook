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

bool drv_init_accel(const struct accel_ctx *ctx)
{
    if (device_is_ready(ctx->dev) == false) {
        printk("%s: sensor device is not ready.\n", ctx->dev->name);
        return false;
    }

    return true;
}

bool drv_accel_setup(const struct accel_ctx *ctx)
{
    struct sensor_value odr = { .val1 = 1000 / ctx->period_ms, .val2 = 0 };
    if (sensor_attr_set(ctx->dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr) != 0) {
        printk("%s : failed to set sampling frequency\n", ctx->dev->name);
        return false;
    }
    return true;
}

int32_t drv_accel_start(const struct accel_ctx *ctx)
{
    return 0;
}

int32_t drv_accel_stop(const struct accel_ctx *ctx)
{
    return 0;
}

int32_t drv_accel_fetch(const struct accel_ctx *ctx, struct sensor_3d *data)
{
    assert(ctx);
    assert(data);

    int32_t result;

    result = sensor_sample_fetch(ctx->dev);
    if (result < 0) {
		printk("%s: sensor_sample_fetch() failed: %d\n", ctx->dev->name, result);
		return result;
	}

    result = sensor_channel_get(ctx->dev, SENSOR_CHAN_ACCEL_XYZ, data->array);
    if (result < 0) {
        printk("%s: sensor_channel_get(XYZ) failed: %d\n", ctx->dev->name, result);
        return result;
    }

    return 0;
}
