/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/button/drv_button_nucleo.h"

// CN7 odd
#define GPIOC_PIN10                 GPIO_PORT_PIN(gpioc, 10)        // PC_10, SPI3 SCLK
#define GPIOC_PIN12                 GPIO_PORT_PIN(gpioc, 12)        // PC_12, SPI3_MOSI
                                                                    // VDD
                                                                    // BOOT0
                                                                    // -
                                                                    // -
#define GPIOA_PIN13                 GPIO_PORT_PIN(gpioa, 13)        // PA_13
#define GPIOA_PIN14                 GPIO_PORT_PIN(gpioa, 14)        // PA_14
#define GPIOA_PIN15                 GPIO_PORT_PIN(gpioa, 15)        // PA_15, PWM2/1, SPI1_SSEL
                                                                    // GND
#define GPIOB_PIN07                 GPIO_PORT_PIN(gpiob,  7)        // PB_7, UART1_RX, PWM4/2, I2C1_SDA
#define GPIOC_PIN13                 GPIO_PORT_PIN(gpioc, 13)        // PC_13, BUTTON1
#define GPIOC_PIN14                 GPIO_PORT_PIN(gpioc, 14)        // PC_14
#define GPIOC_PIN15                 GPIO_PORT_PIN(gpioc, 15)        // PC_15
#define GPIOH_PIN00                 GPIO_PORT_PIN(gpioh,  0)        // PH_0
#define GPIOH_PIN01                 GPIO_PORT_PIN(gpioh,  1)        // PH_1
                                                                    // VBAT
#define GPIOC_PIN02                 GPIO_PORT_PIN(gpioc,  2)        // PC_2, SPI2_MISO, ADC1/12
#define GPIOC_PIN03                 GPIO_PORT_PIN(gpioc,  3)        // PC_3, SPI2_MOSI, ADC1/13

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
#define GPIOA_PIN00                 GPIO_PORT_PIN(gpioa,  0)        // PA_0, A0, ADC1/0, PWM2/1, UART2_CTS
#define GPIOA_PIN01                 GPIO_PORT_PIN(gpioa,  1)        // PA_1, A1, ADC1/1, PWM2/2, UART2_RTS
#define GPIOA_PIN04                 GPIO_PORT_PIN(gpioa,  4)        // PA_4, A2, ADC1/4, SPI1_SSEL
#define GPIOB_PIN00                 GPIO_PORT_PIN(gpiob,  0)        // PB_0, A3, ADC1/8, PWM1/2N
#define GPIOC_PIN01                 GPIO_PORT_PIN(gpioc,  1)        // PC_1, A4, ADC1/11
#define GPIOC_PIN00                 GPIO_PORT_PIN(gpioc,  0)        // PC_0, A6, ADC1/10

// CN10 odd
#define GPIOC_PIN09                 GPIO_PORT_PIN(gpioc,  9)        // PC_9, PWM3/4, I2C3_SDA
#define GPIOB_PIN08                 GPIO_PORT_PIN(gpiob,  8)        // PB_8, D15, PWM4/3, I2C1_SCL
#define GPIOB_PIN09                 GPIO_PORT_PIN(gpiob,  9)        // PB_9, D14, SPI2_SSEL, PWM4/4, I2C1_SDA
                                                                    // AVDD
                                                                    // GND
#define GPIOA_PIN05                 GPIO_PORT_PIN(gpioa,  5)        // PA_5, D13, SPI1_SCLK, LED1, PWM2/1, ADC1/5
#define GPIOA_PIN06                 GPIO_PORT_PIN(gpioa,  6)        // PA_6, D12, SPI1_MISO, PWM3/1, ADC1/6
#define GPIOA_PIN07                 GPIO_PORT_PIN(gpioa,  7)        // PA_7, D11, SPI1_MOSI, PWM1/1N, ADC1/7
#define GPIOB_PIN06                 GPIO_PORT_PIN(gpiob,  6)        // PB_6, D10, I2C1_SCL, PWM4/1, UART1_TX
#define GPIOC_PIN07                 GPIO_PORT_PIN(gpioc,  7)        // PC_7, D9, PWM3/2, UART6_RX
#define GPIOA_PIN09                 GPIO_PORT_PIN(gpioa,  9)        // PA_9, D8, USB_VBUS, PWM1/2, UART1_TX
#define GPIOA_PIN08                 GPIO_PORT_PIN(gpioa,  8)        // PA_8, D7, USB_SOF, PWM1/1, I2C3_SCL
#define GPIOB_PIN10                 GPIO_PORT_PIN(gpiob, 10)        // PB_10, D6, SPI2_SCLK, PWM2/3, I2C2_SCL
#define GPIOB_PIN04                 GPIO_PORT_PIN(gpiob,  4)        // PB_4, D5, SPI1_MISO, PWM3/1, I2C3_SDA
#define GPIOB_PIN05                 GPIO_PORT_PIN(gpiob,  5)        // PB_5, D4, SPI1_MOSI, PWM3/2,
#define GPIOB_PIN03                 GPIO_PORT_PIN(gpiob,  3)        // PB_3, D3, SPI1_SCLK, PWM2/2, I2C2_SDA
#define GPIOA_PIN10                 GPIO_PORT_PIN(gpioa, 10)        // PA_10, D2, USB_ID, PWM1/3, UART1_RX
#define GPIOA_PIN02                 GPIO_PORT_PIN(gpioa,  2)        // PA_2, D1, UART2_TX
#define GPIOA_PIN03                 GPIO_PORT_PIN(gpioa,  3)        // PA_3, D0, UART2_RX

// CN10 even
#define GPIOC_PIN08                 GPIO_PORT_PIN(gpioc,  8)        // PC_8, PWM3/3
#define GPIOC_PIN06                 GPIO_PORT_PIN(gpioc,  6)        // PC_6, UART6_TX, PWM3/1
#define GPIOC_PIN05                 GPIO_PORT_PIN(gpioc,  5)        // PC_5, ADC1/15
                                                                    // U5V
                                                                    // -
#define GPIOA_PIN12                 GPIO_PORT_PIN(gpioa, 12)        // PA_12, UART6_RX, UART1_RTS, USB_DP
#define GPIOA_PIN11                 GPIO_PORT_PIN(gpioa, 11)        // PA_11, UART6_TX, PWM1/4, USB_DM, UART1_CTS
#define GPIOB_PIN12                 GPIO_PORT_PIN(gpiob, 12)        // PB_12, SPI2_SSEL
                                                                    // -
                                                                    // GND
#define GPIOB_PIN02                 GPIO_PORT_PIN(gpiob,  2)        // PB_2
#define GPIOB_PIN01                 GPIO_PORT_PIN(gpiob,  1)        // PB_1, ADC1/9, PWM1/3N
#define GPIOB_PIN15                 GPIO_PORT_PIN(gpiob, 15)        // PB_15, PWM1/3N, SPI2_MOSI
#define GPIOB_PIN14                 GPIO_PORT_PIN(gpiob, 14)        // PB_14, PWM1/2N, SPI2_MISO
#define GPIOB_PIN13                 GPIO_PORT_PIN(gpiob, 13)        // PB_13, PWM1/1N, SPI2_SCLK
                                                                    // AGND
#define GPIOC_PIN04                 GPIO_PORT_PIN(gpioc,  4)        // PC_4, ADC1/14
                                                                    // -
                                                                    // -

#define	GREEN_LED					GPIOA_PIN05
#define USER_BUTTON                 GPIOC_PIN13

void uni_board_init(void);
