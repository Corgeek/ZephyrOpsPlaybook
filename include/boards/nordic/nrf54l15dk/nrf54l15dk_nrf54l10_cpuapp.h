/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include <zephyr/drivers/gpio.h>
#include "drivers/gpio/drv_gpio_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define GPIO1_PIN10                 GPIO_PORT_PIN(gpio1, 10)
#define GPIO1_PIN14                 GPIO_PORT_PIN(gpio1, 14)
#define GPIO2_PIN07                 GPIO_PORT_PIN(gpio2,  7)
#define GPIO2_PIN09                 GPIO_PORT_PIN(gpio2,  9)

// aliases
#define USER_LED                    GPIO1_PIN10
#define USER_LED0                   GPIO2_PIN09
#define USER_LED1                   GPIO1_PIN10
#define USER_LED2                   GPIO2_PIN07
#define USER_LED3                   GPIO1_PIN14

#ifdef  __cplusplus
}
#endif
