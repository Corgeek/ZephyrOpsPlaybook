/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>

struct uart_port_config {
    const struct device *const port;
    struct uart_config cfg;
    bool is_ready;
};

#ifdef  __cplusplus
extern "C" {
#endif

bool drv_init_uart(struct uart_port_config *uart_dev);
void drv_uart_send(const uint8_t *data, size_t len);
size_t drv_uart_recv(uint8_t *data, size_t len);

#ifdef  __cplusplus
}
#endif
