/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "drivers/button/drv_button_generic.h"

static const struct gpio_dt_spec s_nucleo_button = USER_BUTTON;
static struct gpio_callback s_button_cb_data;

void drv_button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

bool drv_init_button(void)
{
    if (gpio_is_ready_dt(&s_nucleo_button) == false) {
        printk("Error: button device %s is not ready\n",
            s_nucleo_button.port->name);
        return false;
    }

    int ret;
	ret = gpio_pin_configure_dt(&s_nucleo_button, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n", ret,
            s_nucleo_button.port->name, s_nucleo_button.pin);
		return false;
	}

	ret = gpio_pin_interrupt_configure_dt(&s_nucleo_button, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
        printk("Error %d: failed to configure interrupt on %s pin %d\n",
            ret, s_nucleo_button.port->name, s_nucleo_button.pin);
        return 0;
    }

	gpio_init_callback(&s_button_cb_data, drv_button_pressed, BIT(s_nucleo_button.pin));
	gpio_add_callback(s_nucleo_button.port, &s_button_cb_data);

    return true;
}
