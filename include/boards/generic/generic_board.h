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

// aliases
#define USER_LED                    GPIO_DUMMY

#ifdef  __cplusplus
}
#endif
