/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

struct gpio_port_pin {
    const struct device *port;
    gpio_pin_t pin;
};

#define GPIO_PORT_PIN(_port, _pin)  ((struct gpio_port_pin){ .port = DEVICE_DT_GET(DT_NODELABEL(_port)), .pin = (_pin) })
#define GPIO_DUMMY                  ((struct gpio_port_pin){ .port = NULL, .pin = 0 })

int  drv_init_gpio(const struct gpio_port_pin *pp, gpio_flags_t flags, int init);
bool gpio_is_valid(const struct gpio_port_pin *pp);
