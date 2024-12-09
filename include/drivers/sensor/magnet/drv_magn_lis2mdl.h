/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>
#include "global/gbf_sensor_database.h"

#define SENSOR_MAGNET_FREQ_HZ   (20)

const struct device *const magnet_device(void);

bool drv_init_magnet(void);
int get_magnet_xyz(struct sensor_3d *data);
