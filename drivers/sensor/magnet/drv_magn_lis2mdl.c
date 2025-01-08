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

bool drv_init_magnet(const struct magnet_ctx *ctx)
{
    if (device_is_ready(ctx->dev) == false) {
        printk("%s: sensor device is not ready.\n", ctx->dev->name);
        return false;
    }

    return true;
}

bool drv_magnet_setup(const struct magnet_ctx *ctx)
{
    return true;
}

int32_t drv_magnet_start(const struct magnet_ctx *ctx)
{
    return 0;
}

int32_t drv_magnet_stop(const struct magnet_ctx *ctx)
{
    return 0;
}

int32_t drv_magnet_fetch(const struct magnet_ctx *ctx, struct sensor_3d *data)
{
    assert(data);
    int result;

    result = sensor_sample_fetch(ctx->dev);
    if (result < 0) {
		printk("%s: sensor_sample_fetch() failed: %d\n", ctx->dev->name, result);
		return result;
	}

    result = sensor_channel_get(ctx->dev, SENSOR_CHAN_MAGN_XYZ, data->array);
    if (result < 0) {
        printk("%s: sensor_channel_get(XYZ) failed: %d\n", ctx->dev->name, result);
        return result;
    }

    return 0;
}
