/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

struct gpio_config {
	uint32_t port_pin;
	uint32_t cfg;
};

void board_init(void);
