/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/i2c/drv_i2c_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

// CN7 odd
#define GPIOC_PIN10                 GPIO_PORT_PIN(gpioc, 10)        // PC_10
#define GPIOC_PIN12                 GPIO_PORT_PIN(gpioc, 12)        // PC_12
                                                                    // VDD
                                                                    // BOOT0
#define GPIOF_PIN06                 GPIO_PORT_PIN(gpiof,  6)        // PF_6
#define GPIOF_PIN07                 GPIO_PORT_PIN(gpiof,  7)        // PF_7
#define GPIOA_PIN13                 GPIO_PORT_PIN(gpioa, 13)        // PA_13
#define GPIOA_PIN14                 GPIO_PORT_PIN(gpioa, 14)        // PA_14
#define GPIOA_PIN15                 GPIO_PORT_PIN(gpioa, 15)        // PA_15
                                                                    // GND
#define GPIOB_PIN07                 GPIO_PORT_PIN(gpiob,  7)        // PB_7
#define GPIOC_PIN13                 GPIO_PORT_PIN(gpioc, 13)        // PC_13
#define GPIOC_PIN14                 GPIO_PORT_PIN(gpioc, 14)        // PC_14
#define GPIOC_PIN15                 GPIO_PORT_PIN(gpioc, 15)        // PC_15
#define GPIOF_PIN00                 GPIO_PORT_PIN(gpiof,  0)        // PF_0
#define GPIOF_PIN01                 GPIO_PORT_PIN(gpiof,  1)        // PF_1
                                                                    // VBAT
#define GPIOC_PIN02                 GPIO_PORT_PIN(gpioc,  2)        // PC_2
#define GPIOC_PIN03                 GPIO_PORT_PIN(gpioc,  3)        // PC_3

// CN7 even
#define GPIOC_PIN11                 GPIO_PORT_PIN(gpioc, 11)        // PC_11
#define GPIOD_PIN02                 GPIO_PORT_PIN(gpiod,  2)        // PD_2
                                                                    // E5V
                                                                    // GND
                                                                    // -
                                                                    // IOREF
                                                                    // RESET
                                                                    // +3.3V
                                                                    // +5V
                                                                    // GND
                                                                    // GND
                                                                    // VIN
                                                                    // -
#define GPIOA_PIN00                 GPIO_PORT_PIN(gpioa,  0)        // PA_0, A0, ADC_IN0
#define GPIOA_PIN01                 GPIO_PORT_PIN(gpioa,  1)        // PA_1, A1, ADC_IN1
#define GPIOA_PIN04                 GPIO_PORT_PIN(gpioa,  4)        // PA_4, A2, ADC_IN4
#define GPIOB_PIN00                 GPIO_PORT_PIN(gpiob,  0)        // PB_0, A3, ADC_IN8
#define GPIOC_PIN01                 GPIO_PORT_PIN(gpioc,  1)        // PC_1, A4, ADC_IN11
#define GPIOC_PIN00                 GPIO_PORT_PIN(gpioc,  0)        // PC_0, A5, ADC_IN10

// CN10 odd
#define GPIOC_PIN09                 GPIO_PORT_PIN(gpioc,  9)        // PC_9
#define GPIOB_PIN08                 GPIO_PORT_PIN(gpiob,  8)        // PB_8, D15, I2C1_SCL
#define GPIOB_PIN09                 GPIO_PORT_PIN(gpiob,  9)        // PB_9, D14, I2C1_SDA
                                                                    // AVDD
                                                                    // GND
#define GPIOA_PIN05                 GPIO_PORT_PIN(gpioa,  5)        // PA_5, D13, SPI1_SCLK, LED1
#define GPIOA_PIN06                 GPIO_PORT_PIN(gpioa,  6)        // PA_6, D12, SPI1_MISO
#define GPIOA_PIN07                 GPIO_PORT_PIN(gpioa,  7)        // PA_7, D11, TIM17_CH1, SPI1_MOSI
#define GPIOB_PIN06                 GPIO_PORT_PIN(gpiob,  6)        // PB_6, D10, TIM16_CH1N, SPI1_CS
#define GPIOC_PIN07                 GPIO_PORT_PIN(gpioc,  7)        // PC_7, D9, TIM3_CH2
#define GPIOA_PIN09                 GPIO_PORT_PIN(gpioa,  9)        // PA_9, D8
#define GPIOA_PIN08                 GPIO_PORT_PIN(gpioa,  8)        // PA_8, D7
#define GPIOB_PIN10                 GPIO_PORT_PIN(gpiob, 10)        // PB_10, D6, TIM3_CH2
#define GPIOB_PIN04                 GPIO_PORT_PIN(gpiob,  4)        // PB_4, D5, TIM3_CH1
#define GPIOB_PIN05                 GPIO_PORT_PIN(gpiob,  5)        // PB_5, D4
#define GPIOB_PIN03                 GPIO_PORT_PIN(gpiob,  3)        // PB_3, D3, TIM2_CH2
#define GPIOA_PIN10                 GPIO_PORT_PIN(gpioa, 10)        // PA_10, D2
#define GPIOA_PIN02                 GPIO_PORT_PIN(gpioa,  2)        // PA_2, D1, UART2_TX
#define GPIOA_PIN03                 GPIO_PORT_PIN(gpioa,  3)        // PA_3, D0, UART2_RX

// CN10 even
#define GPIOC_PIN08                 GPIO_PORT_PIN(gpioc,  8)        // PC_8
#define GPIOC_PIN06                 GPIO_PORT_PIN(gpioc,  6)        // PC_6
#define GPIOC_PIN05                 GPIO_PORT_PIN(gpioc,  5)        // PC_5
                                                                    // U5V
                                                                    // -
#define GPIOA_PIN12                 GPIO_PORT_PIN(gpioa, 12)        // PA_12
#define GPIOA_PIN11                 GPIO_PORT_PIN(gpioa, 11)        // PA_11
#define GPIOB_PIN12                 GPIO_PORT_PIN(gpiob, 12)        // PB_12
#define GPIOB_PIN11                 GPIO_PORT_PIN(gpiob, 11)        // PB_11
                                                                    // GND
#define GPIOB_PIN02                 GPIO_PORT_PIN(gpiob,  2)        // PB_2
#define GPIOB_PIN01                 GPIO_PORT_PIN(gpiob,  1)        // PB_1
#define GPIOB_PIN15                 GPIO_PORT_PIN(gpiob, 15)        // PB_15
#define GPIOB_PIN14                 GPIO_PORT_PIN(gpiob, 14)        // PB_14
#define GPIOB_PIN13                 GPIO_PORT_PIN(gpiob, 13)        // PB_13
                                                                    // AGND
#define GPIOC_PIN04                 GPIO_PORT_PIN(gpioc,  4)        // PC_4
#define GPIOF_PIN05                 GPIO_PORT_PIN(gpiof,  5)        // PF_5
#define GPIOF_PIN04                 GPIO_PORT_PIN(gpiof,  4)        // PF_4

#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c1))
#define UART_115200_BUS             DEVICE_DT_GET(DT_NODELABEL(usart1))
#define USER_BUTTON                 GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios)
#define	GREEN_LED                   GPIOA_PIN05
#define TOF_XSHUT                   GPIOA_PIN00

#ifdef  __cplusplus
}
#endif
