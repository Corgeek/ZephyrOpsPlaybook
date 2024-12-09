/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
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
    { GPIO_RING_0, GPIO_INPUT },
    { GPIO_RING_1, GPIO_INPUT },
    { GPIO_RING_2, GPIO_INPUT },
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

	drv_init_button();
	drv_init_display();
	drv_init_accel();
	drv_init_magnet();
}
