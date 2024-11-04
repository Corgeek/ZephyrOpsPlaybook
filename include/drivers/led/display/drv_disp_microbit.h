/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <stdint.h>
#include <zephyr/display/mb_display.h>

/**
 * @brief Initialize display-driver for microbit
 */
void drv_init_display(void);

/**
 * @brief display image data
 */
void drv_disp_image(uint32_t mode, int32_t duration, const struct mb_image *img, uint8_t img_count);

/**
 * @brief display text data
 */
void drv_disp_print(uint32_t mode, int32_t duration, const char *text);

/**
 * @brief stop display
 */
void drv_disp_stop(void);
