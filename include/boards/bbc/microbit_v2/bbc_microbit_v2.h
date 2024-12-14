/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/beep/drv_beep_manipulator.h"
#include "drivers/button/drv_button_microbit.h"
#include "drivers/display/drv_disp_microbit.h"
#include "drivers/sensor/accel/drv_accel_lis2dh.h"
#include "drivers/sensor/magnet/drv_magn_lis2mdl.h"
#include "drivers/ble/drv_ble_peripheral.h"

// Around 0 Ring
#define GPIO0_PIN31                 GPIO_PORT_PIN(gpio0, 31)        // P0.31, AIN7
#define GPIO0_PIN02                 GPIO_PORT_PIN(gpio0,  2)        // P0.02, AIN0
#define GPIO0_PIN28                 GPIO_PORT_PIN(gpio0, 28)        // P0.28, AIN4
#define GPIO0_PIN14                 GPIO_PORT_PIN(gpio0, 14)        // P0.14
#define GPIO1_PIN05                 GPIO_PORT_PIN(gpio1,  5)        // P1.05
#define GPIO0_PIN11                 GPIO_PORT_PIN(gpio0, 11)        // P0.11, TRACEDATA2

// Around 1 Ring
#define GPIO0_PIN03                 GPIO_PORT_PIN(gpio0,  3)        // P0.03, AIN1
#define GPIO0_PIN10                 GPIO_PORT_PIN(gpio0, 10)        // P0.10, NFC2
#define GPIO0_PIN09                 GPIO_PORT_PIN(gpio0,  9)        // P0.09, NFC1
#define GPIO0_PIN30                 GPIO_PORT_PIN(gpio0, 30)        // P0.30, AIN6
#define GPIO0_PIN23                 GPIO_PORT_PIN(gpio0, 23)        // P0.23
#define GPIO0_PIN12                 GPIO_PORT_PIN(gpio0, 12)        // P0.12, TRACEDATA1

// Around 2 Ring
#define GPIO0_PIN04                 GPIO_PORT_PIN(gpio0,  4)        // P0.04, AIN2
#define GPIO0_PIN17                 GPIO_PORT_PIN(gpio0, 17)        // P0.17
#define GPIO0_PIN01                 GPIO_PORT_PIN(gpio0,  1)        // P0.01, XL2
#define GPIO0_PIN13                 GPIO_PORT_PIN(gpio0, 13)        // P0.13
#define GPIO1_PIN02                 GPIO_PORT_PIN(gpio1,  2)        // P1.02

// Around 3.3V Ring
#define GPIO0_PIN26                 GPIO_PORT_PIN(gpio0, 26)        // P0.26
#define GPIO1_PIN00                 GPIO_PORT_PIN(gpio1,  0)        // P1.00, TRACEDATA0

// Aliases
#define	BUTTON_A                    GPIO0_PIN14
#define	BUTTON_B                    GPIO0_PIN23
#define GPIO_RING_0                 GPIO0_PIN02
#define GPIO_RING_1                 GPIO0_PIN03
#define GPIO_RING_2                 GPIO0_PIN04

void uni_board_init(void);
