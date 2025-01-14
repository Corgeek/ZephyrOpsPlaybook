/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include "boards/unique.h"
#include "drivers/serial/drv_uart_common.h"

struct uart_bus_config {
    const struct device *const bus;
    struct uart_config cfg;
    bool is_ready;
};

static struct uart_bus_config s_uart_dev[] = {
#ifdef UART_115200_BUS
    {
        .bus = UART_115200_BUS,
        .cfg = {
            .baudrate = 115200,
            .parity = UART_CFG_PARITY_NONE,
            .stop_bits = UART_CFG_STOP_BITS_1,
            .data_bits = UART_CFG_DATA_BITS_8,
            .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
        },
        .is_ready = false,
    }
#endif // UART_115200_BUS
};

bool drv_init_uart(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(s_uart_dev); ++i) {
        s_uart_dev[i].is_ready = device_is_ready(s_uart_dev[i].bus);
        if (s_uart_dev[i].is_ready == false) {
            printk("uart is not ready[%s]\n", s_uart_dev[i].bus->name);
            continue;
        }

        if (uart_configure(s_uart_dev[i].bus, &s_uart_dev[i].cfg)) {
            printk("uart_configure() failed[%s]\n", s_uart_dev[i].bus->name);
            s_uart_dev[i].is_ready = false;
            continue;
        }
    }

    bool result = true;
    for (size_t i = 0; i < ARRAY_SIZE(s_uart_dev); ++i) {
        result |= s_uart_dev[i].is_ready;
    }

    return result;
}

void drv_uart_send(const struct device *const dev, size_t len, const uint8_t *data)
{
    for (size_t i = 0; i < len; ++i) {
        uart_poll_out(dev, data[i]);
    }
}
