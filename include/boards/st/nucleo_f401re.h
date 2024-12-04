/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/button/drv_button_nucleo.h"

struct gpio_config {
	uint32_t port_pin;
	uint32_t cfg;
};

void uni_board_init(void);
