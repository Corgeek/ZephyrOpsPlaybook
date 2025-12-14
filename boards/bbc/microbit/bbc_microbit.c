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
    { GPIO_RING_0, GPIO_OUTPUT },
    { GPIO_RING_1, GPIO_OUTPUT },
    { GPIO_RING_2, GPIO_OUTPUT },
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
	{ I2C_100KHZ_BUS, 	I2C_SPEED_STANDARD },
};
#endif // CONFIG_I2C

static
void gpio_init_pin(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(s_gpio_list); ++i) {
        if (device_is_ready(s_gpio_list[i].gpio.port) == false)
			continue;

        gpio_pin_configure(s_gpio_list[i].gpio.port, s_gpio_list[i].gpio.pin, s_gpio_list[i].flags);
    }
}

#if defined(CONFIG_SERIAL)
static
void uart_init_port(void)
{
	for (size_t i = 0; i < ARRAY_SIZE(s_uart_ports); ++i) {
		if (drv_init_uart(&s_uart_ports[i])) {
		}
	}
}
#endif // CONFIG_SERIAL

#if defined(CONFIG_I2C)
static
void i2c_init_bus(void)
{
	for (size_t i = 0; i < ARRAY_SIZE(s_i2c_buses); ++i) {
		if (drv_init_i2c(&s_i2c_buses[i])) {
		}
	}
}
#endif // CONFIG_I2C

void uni_board_init(void)
{
#if defined(CONFIG_GPIO)
	gpio_init_pin();
#endif // CONFIG_GPIO
#if defined(CONFIG_I2C)
	i2c_init_bus();
#endif // CONFIG_I2C
#if defined(CONFIG_SERIAL)
	uart_init_port();
#endif

#if defined(CONFIG_BEEP)
	drv_init_beep();
#endif // CONFIG_BEEP
#if defined(CONFIG_BUTTON)
	drv_init_button();
#endif // CONFIG_BUTTON
#if defined(CONFIG_DISPLAY_WRAPPER)
	drv_init_display();
#endif // CONFIG_DISPLAY_WRAPPER
}
