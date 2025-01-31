/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef  __cplusplus
extern "C" {
#endif

// Left Side
#define GPIO0_PIN00                 GPIO_PORT_PIN(gpio0,  0)        // GP_0, SPI0_RX, I2C0_SDA, UART0_TX
#define GPIO0_PIN01                 GPIO_PORT_PIN(gpio0,  1)        // GP_1, SPI0_CSn, I2C0_SCL, UART0_RX
                                                                    // GND
#define GPIO0_PIN02                 GPIO_PORT_PIN(gpio0,  2)        // GP_2, SPI0_SCK, I2C1_SDA
#define GPIO0_PIN03                 GPIO_PORT_PIN(gpio0,  3)        // GP_3, SPI0_TX, I2C1_SCL
#define GPIO0_PIN04                 GPIO_PORT_PIN(gpio0,  4)        // GP_4, SPI0_RX, I2C0_SDA, UART1_TX
#define GPIO0_PIN05                 GPIO_PORT_PIN(gpio0,  5)        // GP_5, SPI0_CSn, I2C0_SCL, UART1_RX
                                                                    // GND
#define GPIO0_PIN06                 GPIO_PORT_PIN(gpio0,  6)        // GP_6, SPI0_SCK, I2C1_SDA
#define GPIO0_PIN07                 GPIO_PORT_PIN(gpio0,  7)        // GP_7, SPI0_TX, I2C1_SCL
#define GPIO0_PIN08                 GPIO_PORT_PIN(gpio0,  8)        // GP_8, SPI1_RX, I2C0_SDA, UART1_TX
#define GPIO0_PIN09                 GPIO_PORT_PIN(gpio0,  9)        // GP_9, SPI1_CSn, I2C0_SCL, UART1_RX
                                                                    // GND
#define GPIO0_PIN10                 GPIO_PORT_PIN(gpio0, 10)        // GP_10, SPI1_SCK, I2C1_SDA
#define GPIO0_PIN11                 GPIO_PORT_PIN(gpio0, 11)        // GP_11, SPI1_TX, I2C1_SCL
#define GPIO0_PIN12                 GPIO_PORT_PIN(gpio0, 12)        // GP_12, SPI1_RX, I2C0_SDA, UART0_TX
#define GPIO0_PIN13                 GPIO_PORT_PIN(gpio0, 13)        // GP_13, SPI1_CSn, I2C0_SCL, UART0_RX
                                                                    // GND
#define GPIO0_PIN14                 GPIO_PORT_PIN(gpio0, 14)        // GP_14, SPI1_SCK, I2C1_SDA
#define GPIO0_PIN15                 GPIO_PORT_PIN(gpio0, 15)        // GP_15, SPI1_TX, I2C1_SCL

// Right side
                                                                    // VBUS
                                                                    // VSYS
                                                                    // GND
                                                                    // 3V3_EN
                                                                    // 3V3(OUT)
                                                                    // ADC_VREF
#define GPIO0_PIN28                 GPIO_PORT_PIN(gpio0, 28)        // GP_28, ADC2
                                                                    // GND, AGND
#define GPIO0_PIN27                 GPIO_PORT_PIN(gpio0, 27)        // GP_27, ADC1, I2C1_SCL
#define GPIO0_PIN26                 GPIO_PORT_PIN(gpio0, 26)        // GP_26, ADC0, I2C1_SDA
#define GPIO0_PIN25                 GPIO_PORT_PIN(gpio0, 25)        // USER LED, RUN
#define GPIO0_PIN22                 GPIO_PORT_PIN(gpio0, 22)        // GP_22
                                                                    // GND
#define GPIO0_PIN21                 GPIO_PORT_PIN(gpio0, 21)        // GP_21, I2C0_SCL
#define GPIO0_PIN20                 GPIO_PORT_PIN(gpio0, 20)        // GP_20, I2C0_SDA
#define GPIO0_PIN19                 GPIO_PORT_PIN(gpio0, 19)        // GP_19, SPI0_TX, I2C1_SCL
#define GPIO0_PIN18                 GPIO_PORT_PIN(gpio0, 18)        // GP_18, SPI0_SCK, I2C1_SDA
                                                                    // GND
#define GPIO0_PIN17                 GPIO_PORT_PIN(gpio0, 17)        // GP_17, SPI0_CSn, I2C0_SCL, UART0_RX
#define GPIO0_PIN16                 GPIO_PORT_PIN(gpio0, 16)        // GP_16, SPI0_RX, I2C0_SDA, UART0_TX

// Aliases
#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c0))
#define USER_LED                    GPIO0_PIN25

#ifdef  __cplusplus
}
#endif
