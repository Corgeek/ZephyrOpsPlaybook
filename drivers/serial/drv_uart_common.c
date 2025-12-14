/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include "boards/unique.h"
#include "drivers/serial/drv_uart_common.h"

const struct device *s_uart_dev;

bool drv_init_uart(struct uart_port_config *uart_dev)
{
    uart_dev->is_ready = device_is_ready(uart_dev->port);
    if (uart_dev->is_ready == false) {
        printk("uart is not ready[%s]\n", uart_dev->port->name);
        return false;
    }

    if (uart_configure(uart_dev->port, &uart_dev->cfg)) {
        printk("uart_configure() failed[%s]\n", uart_dev->port->name);
        uart_dev->is_ready = false;
        return false;
    }

    s_uart_dev = uart_dev->port;

    return true;
}

void drv_uart_send(const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        uart_poll_out(s_uart_dev, data[i]);
    }
}

size_t drv_uart_recv(uint8_t *data, size_t len)
{
    size_t cnt;
    for (cnt = 0; cnt < len; ++cnt) {
        if (uart_poll_in(s_uart_dev, &data[cnt]))
            break;
    }

    return cnt;
}
