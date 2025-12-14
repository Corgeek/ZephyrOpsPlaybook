/*
 * Copyright (c) 2025 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/serial/drv_uart_common.h"
#include "drivers/i2c/drv_i2c_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

// CN3
                                                                    // VIN
                                                                    // GND
                                                                    // T_NRST
                                                                    // 5V
#define GPIOA_PIN02                 GPIO_PORT_PIN(gpioa,  2)        // A7, ARD_A7, PA2, ADC1_IN3
#define GPIOA_PIN07                 GPIO_PORT_PIN(gpioa,  7)        // A6, ARD_A6, PA7, ADC2_IN4
#define GPIOA_PIN06                 GPIO_PORT_PIN(gpioa,  6)        // A5, ARD_A5, PA6/PA15, ADC2_IN3/I2C1_SCL
#define GPIOA_PIN05                 GPIO_PORT_PIN(gpioa,  5)        // A4, ARD_A4, PA5/PB7, ADC2_IN13/I2C1_SDA
#define GPIOA_PIN04                 GPIO_PORT_PIN(gpioa,  4)        // A3, ARD_A3, PA4, ADC2_IN17
#define GPIOA_PIN03                 GPIO_PORT_PIN(gpioa,  3)        // A2, ARD_A2, PA3, ADC1_IN4
#define GPIOA_PIN01                 GPIO_PORT_PIN(gpioa,  1)        // A1, ARD_A1, PA1, ADC2_IN2
#define GPIOA_PIN00                 GPIO_PORT_PIN(gpioa,  0)        // A0, ARD_A0, PA0, ADC2_IN1
                                                                    // AVDD
                                                                    // 3V3
#define GPIOB_PIN03                 GPIO_PORT_PIN(gpiob,  3)        // D13, ARD_D13, PB3, SPI1_CLK

// CN4
#define GPIOA_PIN09                 GPIO_PORT_PIN(gpioa,  9)        // D1, ARD_D1, PA9, USART1_TX
#define GPIOA_PIN10                 GPIO_PORT_PIN(gpioa, 10)        // D0, ARD_D0, PA10, USART1_RX
                                                                    // T_NRST, T_NRST, PG10_NRST, RESET
                                                                    // GND, -, -, 3V3 input/output
#define GPIOA_PIN12                 GPIO_PORT_PIN(gpioa,  2)        // D2, ARD_D2, PA12, -
#define GPIOB_PIN00                 GPIO_PORT_PIN(gpiob,  0)        // D3, ARD_D3, PB0, PWM: TIM3_CH3
#define GPIOB_PIN07                 GPIO_PORT_PIN(gpiob,  7)        // D4, ARD_D4, PB7, TIM4_CH2 / I2C1_SDA
#define GPIOA_PIN15                 GPIO_PORT_PIN(gpioa, 15)        // D5, ARD_D5, PA15, TIM2_CH1 / I2C1_SCL
#define GPIOB_PIN06                 GPIO_PORT_PIN(gpiob,  6)        // D6, ARD_D6, PB6, PWM: TIM1_CH1
#define GPIOF_PIN00                 GPIO_PORT_PIN(gpiof,  0)        // D7, ARD_D7, PF0, -
#define GPIOF_PIN01                 GPIO_PORT_PIN(gpiof,  1)        // D8, ARD_D8, PF1, -
#define GPIOA_PIN08                 GPIO_PORT_PIN(gpioa,  8)        // D9, ARD_D9, PA8, PWM: TIM4_CH1
#define GPIOA_PIN11                 GPIO_PORT_PIN(gpioa, 11)        // D10, ARD_D10, PA11, SPI1_CS / TIM1_CH4
#define GPIOB_PIN05                 GPIO_PORT_PIN(gpiob,  5)        // D11, ARD_D11, PB5, SPI1_MOSI / TIM3_CH2
#define GPIOB_PIN04                 GPIO_PORT_PIN(gpiob,  4)        // D12, ARD_D12, PB4, SPI1_MISO

// Aliases
#define HOST_UART                   DEVICE_DT_GET(DT_NODELABEL(usart1))
#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c1))
#define	USER_LED                    GPIOB_PIN03

#ifdef  __cplusplus
}
#endif
