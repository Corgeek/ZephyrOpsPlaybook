/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct gpio_port_pin {
    const struct device *const port;
    const gpio_pin_t pin;
};

void uni_board_init(void);

#define GPIO_PORT_PIN(_port, _pin)          ((struct gpio_port_pin){ .port = DEVICE_DT_GET(DT_NODELABEL(_port)), .pin = (_pin) })
#define GPIO_DUMMY                          ((struct gpio_port_pin){ .port = NULL, .pin = 0 })

#if   defined(CONFIG_BOARD_BBC_MICROBIT)
#include "boards/bbc/microbit/bbc_microbit.h"
#elif defined(CONFIG_BOARD_BBC_MICROBIT_V2)
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"
#elif defined(CONFIG_BOARD_NUCLEO_F030R8)
#include "boards/st/nucleo_f030r8/nucleo_f030r8.h"
#elif defined(CONFIG_BOARD_NUCLEO_F401RE)
#include "boards/st/nucleo_f401re/nucleo_f401re.h"
#elif defined(CONFIG_BOARD_NUCLEO_L552ZE_Q)
#include "boards/st/nucleo_l552ze_q/nucleo_l552ze_q.h"
#elif defined(CONFIG_BOARD_STM32H747I_DISCO_STM32H747XX_M7)
#include "boards/st/stm32h747i_disco/stm32h747i_disco_m7.h"
#elif defined(CONFIG_BOARD_RPI_PICO)
#include "boards/raspberrypi/rpi_pico/rpi_pico.h"
#elif defined(CONFIG_BOARD_RPI_PICO2)
#include "boards/raspberrypi/rpi_pico2/rpi_pico2.h"
#else
#include "boards/generic/generic_board.h"
#endif

#ifdef  __cplusplus
}
#endif
