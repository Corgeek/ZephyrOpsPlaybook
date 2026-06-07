/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include "drivers/gpio/drv_gpio_common.h"
#include "drivers/i2c/drv_i2c_common.h"
#include "drivers/serial/drv_uart_common.h"
#include "modules/com_uart_host.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define GPIOH_PIN10                 GPIO_PORT_PIN(gpioh, 10)        // LED 3 Red
#define GPIOH_PIN11                 GPIO_PORT_PIN(gpioh, 11)        // LED 3 Green

// aliases
#define USER_LED_RED                GPIOH_PIN10
#define USER_LED_GREEN              GPIOH_PIN11
#define USER_LED                    USER_LED_GREEN

#ifdef  __cplusplus
}
#endif
