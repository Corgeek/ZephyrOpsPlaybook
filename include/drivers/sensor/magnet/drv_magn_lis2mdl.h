/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>
#include "global/gbf_sensor_database.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SENSOR_MAGNET_PERIOD_MS     (100)

struct magnet_ctx {
    const struct device *const dev;
    uint16_t period_ms;
    uint16_t state;
};

bool drv_init_magnet(const struct magnet_ctx *ctx);
bool drv_magnet_setup(const struct magnet_ctx *ctx);

int32_t drv_magnet_start(const struct magnet_ctx *ctx);
int32_t drv_magnet_stop(const struct magnet_ctx *ctx);
int32_t drv_magnet_fetch(const struct magnet_ctx *ctx, struct sensor_3d *data);

#ifdef  __cplusplus
}
#endif
