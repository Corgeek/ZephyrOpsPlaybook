/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/i2c/drv_i2c_common.h"
#include "drivers/sensor/measure/drv_tof_sequence.h"
#include "drivers/sensor/measure/drv_tof_vl53l4cd.h"

#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c0))
#define GPIO0_PIN26                 GPIO_PORT_PIN(gpio0,  26)

void uni_board_init(void);
