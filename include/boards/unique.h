/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

struct gpio_port_pin {
    const struct device *const port;
    const gpio_pin_t pin;
};

#define GPIO_PORT_PIN(_port, _pin)          ((struct gpio_port_pin){ .port = DEVICE_DT_GET(DT_NODELABEL(_port)), .pin = (_pin) })

#if   defined(CONFIG_BOARD_BBC_MICROBIT)
#include "boards/bbc/microbit/bbc_microbit.h"
#elif defined(CONFIG_BOARD_BBC_MICROBIT_V2)
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"
#elif defined(CONFIG_BOARD_NUCLEO_F401RE)
#include "boards/st/nucleo_f401re.h"
#endif
