/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>

enum SENSOR_DATA_TYPE {
    SENSOR_ACCEL,
    SENSOR_MAGNET,

    SENSOR_TYPE_MAX
};

struct sensor_3d {
    union {
        struct sensor_value array[3];
        struct sensor_value x;
        struct sensor_value y;
        struct sensor_value z;
    };
};

/**
 * @brief Initialize sensor database
 */
void gbf_init_sensor(void);

/**
 * @brief Set data to sensor database
 */
void gbf_set_sensor(enum SENSOR_DATA_TYPE type, struct sensor_3d *const data);

/**
 * @brief Get data from sensor database
 */
void gbf_get_sensor(enum SENSOR_DATA_TYPE type, struct sensor_3d *data);
