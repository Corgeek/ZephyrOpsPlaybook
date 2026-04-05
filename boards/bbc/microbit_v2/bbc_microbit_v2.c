/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "boards/unique.h"

struct gpio_spec {
    struct gpio_port_pin gpio;
    uint32_t flags;
};

static const struct gpio_spec s_gpio_list[] = {
};

#if defined(CONFIG_SERIAL)
struct uart_port_config s_uart_ports[] = {
    {
        .port = HOST_UART,
        .cfg = {
            .baudrate = 115200,
            .parity = UART_CFG_PARITY_NONE,
            .stop_bits = UART_CFG_STOP_BITS_1,
            .data_bits = UART_CFG_DATA_BITS_8,
            .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
        },
        .is_ready = false,
    }
};
#endif // CONFIG_SERIAL

#if defined(CONFIG_I2C)
struct i2c_bus_config s_i2c_buses[] = {
    {
        .bus = I2C_100KHZ_BUS,
        .speed = I2C_SPEED_STANDARD,
        .is_ready = false
    },
};
#endif // CONFIG_I2C

void uni_board_init(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(s_gpio_list); ++i) {
        if (device_is_ready(s_gpio_list[i].gpio.port) == false)
            continue;

        gpio_pin_configure(s_gpio_list[i].gpio.port, s_gpio_list[i].gpio.pin, s_gpio_list[i].flags);
    }

#if defined(CONFIG_I2C)
    if (drv_init_i2c(&s_i2c_buses[0])) {
        s_i2c_buses[0].is_ready = true;
    }
#endif // CONFIG_I2C
#if defined(CONFIG_SERIAL)
    if (drv_init_uart(&s_uart_ports[0])) {
        if (com_host_init(s_uart_ports[0].port)) {
            s_uart_ports[0].is_ready = true;
        }
    }
#endif
}
