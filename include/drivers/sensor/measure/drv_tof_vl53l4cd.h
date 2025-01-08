/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>

#define VL53L4CD_DEF_ADDR       (0x29)
#define TOF_TIMING_BUDGET_MS    (100)

struct vl53l4cd_ctx {
    const struct device *const i2c;
    const struct gpio_port_pin xshut;
    const struct gpio_port_pin interrupt;
    uint16_t addr;
    uint16_t state;
    uint32_t timing_budget_ms;
    uint32_t inter_measurement_ms;
};

bool drv_init_tof(const struct vl53l4cd_ctx *ctx);
bool drv_tof_setup(const struct vl53l4cd_ctx *ctx);

int32_t drv_tof_start(const struct vl53l4cd_ctx *ctx);
int32_t drv_tof_stop(const struct vl53l4cd_ctx *ctx);
int32_t drv_tof_fetch(const struct vl53l4cd_ctx *ctx, struct sensor_value *data);
