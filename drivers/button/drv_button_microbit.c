/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "drivers/button/drv_button_microbit.h"

static struct gpio_callback s_button_callback;
const struct gpio_dt_spec s_sw0_spec = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
const struct gpio_dt_spec s_sw1_spec = GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios);

static
void drv_button_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	printf(__func__);
}

bool drv_init_button(void)
{
	if (!gpio_is_ready_dt(&s_sw0_spec)) {
		printk("%s: device not ready.\n", s_sw0_spec.port->name);
		return false;
	}

	gpio_pin_configure_dt(&s_sw0_spec, GPIO_INPUT);
	gpio_pin_configure_dt(&s_sw1_spec, GPIO_INPUT);

	gpio_pin_interrupt_configure_dt(&s_sw0_spec, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_pin_interrupt_configure_dt(&s_sw1_spec, GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&s_button_callback, drv_button_callback, BIT(s_sw0_spec.pin) | BIT(s_sw1_spec.pin));

	gpio_add_callback(s_sw0_spec.port, &s_button_callback);

	return true;
}