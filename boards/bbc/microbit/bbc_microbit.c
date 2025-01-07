/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "boards/unique.h"

struct gpio_spec {
	struct gpio_port_pin gpio;
	uint32_t flags;
};

static const struct gpio_spec s_gpio_list[] = {
    { GPIO_RING_0, GPIO_OUTPUT },
    { GPIO_RING_1, GPIO_OUTPUT },
    { GPIO_RING_2, GPIO_OUTPUT },
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
#if defined(CONFIG_GPIO)
	gpio_init_pin();
#endif // CONFIG_GPIO
#if defined(CONFIG_I2C)
	drv_init_i2c();
#endif // CONFIG_I2C

#if defined(CONFIG_BEEP)
	drv_init_beep();
#endif // CONFIG_BEEP
#if defined(CONFIG_BUTTON)
	drv_init_button();
#endif // CONFIG_BUTTON
#if defined(CONFIG_DISPLAY_WRAPPER)
	drv_init_display();
#endif // CONFIG_DISPLAY_WRAPPER
#if defined(CONFIG_ACCEL_LIS2DH)
	drv_init_accel();
#endif // CONFIG_ACCEL_LIS2DH
#if defined(CONFIG_MAGNET_LIS2MDL)
	drv_init_magnet();
#endif // CONFIG_MAGNET_LIS2MDL
#if defined(CONFIG_TOF_VL53L4CD)
	drv_init_tof(TOF_ID_1ST);
#endif // CONFIG_TOF_VL53L4CD
}
