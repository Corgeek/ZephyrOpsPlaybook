/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/drivers/sensor.h>

struct sensor_3d {
    union {
        struct sensor_value array[3];
        struct sensor_value x, y, z;
    };
};

/**
 * @brief Initialize sensor database
 */
void gbf_init_sensor(void);

/**
 * @brief Set data to sensor database
 */
void gbf_set_accel(struct sensor_3d *const data);
void gbf_set_magnet(struct sensor_3d *const data);
void gbf_set_measure(uint16_t data);

/**
 * @brief Get data from sensor database
 */
void gbf_get_accel(struct sensor_3d *data);
void gbf_get_magnet(struct sensor_3d *data);
void gbf_get_measure(uint16_t *data);
