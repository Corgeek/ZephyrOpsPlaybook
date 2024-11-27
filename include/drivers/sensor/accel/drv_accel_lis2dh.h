/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>

#define SENSOR_ACCEL_FREQ_HZ   (20)

bool drv_init_accel(void);
int get_accel_xyz(struct sensor_value *ax, struct sensor_value *ay, struct sensor_value *az);
