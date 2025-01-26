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

#define SENSOR_ACCEL_PERIOD_MS      (100)

struct accel_ctx {
    const struct device *const dev;
    uint16_t period_ms;
    uint16_t state;
};

bool drv_init_accel(const struct accel_ctx *ctx);
bool drv_accel_setup(const struct accel_ctx *ctx);

int32_t drv_accel_start(const struct accel_ctx *ctx);
int32_t drv_accel_stop(const struct accel_ctx *ctx);
int32_t drv_accel_fetch(const struct accel_ctx *ctx, struct sensor_3d *value);

#ifdef  __cplusplus
}
#endif
