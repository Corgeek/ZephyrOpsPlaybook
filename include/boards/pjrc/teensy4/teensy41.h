/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/gpio/drv_gpio_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define GPIO_PIN00                  GPIO_PORT_PIN(gpio1,  3)    // AD_B0_03,    GPIO1_3 / UART6_RX / CAN2_RX
#define GPIO_PIN01                  GPIO_PORT_PIN(gpio1,  2)    // AD_B0_02,    GPIO1_2 / UART6_TX / CAN2_TX
#define GPIO_PIN02                  GPIO_PORT_PIN(gpio4,  4)    // EMC_04,      GPIO4_4
#define GPIO_PIN03                  GPIO_PORT_PIN(gpio4,  5)    // EMC_05,      GPIO4_5
#define GPIO_PIN04                  GPIO_PORT_PIN(gpio4,  6)    // EMC_06,      GPIO4_6
#define GPIO_PIN05                  GPIO_PORT_PIN(gpio4,  8)    // EMC_08,      GPIO4_8
#define GPIO_PIN06                  GPIO_PORT_PIN(gpio2, 10)    // B0_10,       GPIO2_10
#define GPIO_PIN07                  GPIO_PORT_PIN(gpio2, 17)    // B1_01,       GPIO2_17 / UART4_RX
#define GPIO_PIN08                  GPIO_PORT_PIN(gpio2, 16)    // B1_00,       GPIO2_16 / UART4_TX
#define GPIO_PIN09                  GPIO_PORT_PIN(gpio2, 11)    // B0_11,       GPIO2_11

#define GPIO_PIN10                  GPIO_PORT_PIN(gpio2,  0)    // B0_00,       GPIO2_0
#define GPIO_PIN11                  GPIO_PORT_PIN(gpio2,  2)    // B0_02,       GPIO2_2
#define GPIO_PIN12                  GPIO_PORT_PIN(gpio2,  1)    // B0_01,       GPIO2_1
#define GPIO_PIN13                  GPIO_PORT_PIN(gpio2,  3)    // B0_03,       GPIO2_3 / LED
#define GPIO_PIN14                  GPIO_PORT_PIN(gpio1, 18)    // AD_B1_02,    GPIO1_18 / UART2_TX
#define GPIO_PIN15                  GPIO_PORT_PIN(gpio1, 19)    // AD_B1_03,    GPIO1_19 / UART2_RX
#define GPIO_PIN16                  GPIO_PORT_PIN(gpio1, 23)    // AD_B1_07,    GPIO1_23 / UART3_RX / I2C3_SCL
#define GPIO_PIN17                  GPIO_PORT_PIN(gpio1, 22)    // AD_B1_06,    GPIO1_22 / UART3_TX / I2C3_SDA
#define GPIO_PIN18                  GPIO_PORT_PIN(gpio1, 17)    // AD_B1_01,    GPIO1_17 / I2C1_SDA
#define GPIO_PIN19                  GPIO_PORT_PIN(gpio1, 16)    // AD_B1_00,    GPIO1_16 / I2C1_SCL

#define GPIO_PIN20                  GPIO_PORT_PIN(gpio1, 26)    // AD_B1_10,    GPIO1_26 / UART8_TX
#define GPIO_PIN21                  GPIO_PORT_PIN(gpio1, 27)    // AD_B1_11,    GPIO1_27 / UART8_RX
#define GPIO_PIN22                  GPIO_PORT_PIN(gpio1, 24)    // AD_B1_08,    GPIO1_24 / CAN1_TX
#define GPIO_PIN23                  GPIO_PORT_PIN(gpio1, 25)    // AD_B1_09,    GPIO1_25 / CAN1_RX
#define GPIO_PIN24                  GPIO_PORT_PIN(gpio1, 12)    // AD_B0_12,    GPIO1_12 / UART1_TX / I2C4_SCL
#define GPIO_PIN25                  GPIO_PORT_PIN(gpio1, 13)    // AD_B0_13,    GPIO1_13 / UART1_RX / I2C4_SDA
#define GPIO_PIN26                  GPIO_PORT_PIN(gpio1, 30)    // AD_B1_14,    GPIO1_30 / SPI3_MOSI
#define GPIO_PIN27                  GPIO_PORT_PIN(gpio1, 31)    // AD_B1_15,    GPIO1_31 / SPI3_SCK
#define GPIO_PIN28                  GPIO_PORT_PIN(gpio3, 18)    // EMC_32,      GPIO3_18 / UART7_RX
#define GPIO_PIN29                  GPIO_PORT_PIN(gpio4, 31)    // EMC_31,      GPIO4_31 / UART7_TX

#define GPIO_PIN30                  GPIO_PORT_PIN(gpio3, 23)    // EMC_37,      GPIO3_23 / CAN3_RX
#define GPIO_PIN31                  GPIO_PORT_PIN(gpio3, 22)    // EMC_36,      GPIO3_22 / CAN3_TX
#define GPIO_PIN32                  GPIO_PORT_PIN(gpio2, 12)    // B0_12,       GPIO2_12
#define GPIO_PIN33                  GPIO_PORT_PIN(gpio4,  7)    // EMC_07,      GPIO4_7
#define GPIO_PIN34                  GPIO_PORT_PIN(gpio2, 29)    // B1_13,       GPIO2_29 / UART5_RX
#define GPIO_PIN35                  GPIO_PORT_PIN(gpio2, 28)    // B1_12,       GPIO2_28 / UART5_TX
#define GPIO_PIN36                  GPIO_PORT_PIN(gpio2, 18)    // B1_02,       GPIO2_18
#define GPIO_PIN37                  GPIO_PORT_PIN(gpio2, 19)    // B1_03,       GPIO2_19
#define GPIO_PIN38                  GPIO_PORT_PIN(gpio1, 28)    // AD_B1_12,    GPIO1_28 / SPI3_CS
#define GPIO_PIN39                  GPIO_PORT_PIN(gpio1, 29)    // AD_B1_13,    GPIO1_29 / SPI3_MISO

#define GPIO_PIN40                  GPIO_PORT_PIN(gpio1, 20)    // AD_B1_04,    GPIO1_20
#define GPIO_PIN41                  GPIO_PORT_PIN(gpio1, 21)    // AD_B1_05,    GPIO1_21 / UART3_RX

// aliases
#define HOST_UART                   DEVICE_DT_GET(DT_NODELABEL(lpuart6))
#define USER_LED                    GPIO_PIN13

#ifdef  __cplusplus
}
#endif
