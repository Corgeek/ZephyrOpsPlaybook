/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/kernel.h>

bool drv_init_uart(void);
void drv_uart_send(const struct device *const dev, size_t len, const uint8_t *data);
