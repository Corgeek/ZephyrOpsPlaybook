/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/serial/drv_uart_common.h"
#include "drivers/i2c/drv_i2c_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

// aliases
#define HOST_UART                   DEVICE_DT_GET(DT_NODELABEL(uart0))
#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c0))
#define USER_LED                    GPIO_DUMMY

#ifdef  __cplusplus
}
#endif
