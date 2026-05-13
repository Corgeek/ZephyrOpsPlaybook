/*
 * Copyright (c) 2025 Takayuki Goto <goto.takayuki@space-entry.co.jp>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "boards/unique.h"

struct gpio_spec {
	struct gpio_port_pin gpio;
	uint32_t flags;
};

static const struct gpio_spec s_gpio_list[] = {
	{ USER_LED, GPIO_OUTPUT_ACTIVE },
};

void gpio_init_pin(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(s_gpio_list); ++i) {
        if (device_is_ready(s_gpio_list[i].gpio.port) == false)
			continue;

        gpio_pin_configure(s_gpio_list[i].gpio.port, s_gpio_list[i].gpio.pin, s_gpio_list[i].flags);
    }
}

void uni_board_init(void)
{
	gpio_init_pin();
}
