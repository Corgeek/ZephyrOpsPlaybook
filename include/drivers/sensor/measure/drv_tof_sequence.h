/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "boards/unique.h"
#include "drivers/i2c/drv_i2c_common.h"

#define VL53L4CD_DEF_ADDR       (0x29)
#define TOF_1ST_ADDR            (0x54)

enum TOF_DEV_ID {
    TOF_ID_1ST,

    TOF_ID_MAX
};

struct vl53l4cd_ctx {
    const struct device *const i2c;
    const struct gpio_port_pin xshut;
    const struct gpio_port_pin gpio;
    uint16_t addr;
    uint16_t seq;
};

bool drv_init_tof(int32_t tof_id);
