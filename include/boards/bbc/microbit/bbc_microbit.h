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

// Around 0 Ring
#define GPIO0_PIN04                 GPIO_PORT_PIN(gpio0,  4)        // P0.04
#define GPIO0_PIN03                 GPIO_PORT_PIN(gpio0,  3)        // P0.03
#define GPIO0_PIN05                 GPIO_PORT_PIN(gpio0,  5)        // P0.05
#define GPIO0_PIN17                 GPIO_PORT_PIN(gpio0, 17)        // P0.17
#define GPIO0_PIN12                 GPIO_PORT_PIN(gpio0, 12)        // P0.12
#define GPIO0_PIN11                 GPIO_PORT_PIN(gpio0, 11)        // P0.11

// Around 1 Ring
#define GPIO0_PIN02                 GPIO_PORT_PIN(gpio0,  2)        // P0.02
#define GPIO0_PIN18                 GPIO_PORT_PIN(gpio0, 18)        // P0.18
#define GPIO0_PIN10                 GPIO_PORT_PIN(gpio0, 10)        // P0.10
#define GPIO0_PIN06                 GPIO_PORT_PIN(gpio0,  6)        // P0.06
#define GPIO0_PIN26                 GPIO_PORT_PIN(gpio0, 26)        // P0.26
#define GPIO0_PIN20                 GPIO_PORT_PIN(gpio0, 20)        // P0.20

// Around 2 Ring
#define GPIO0_PIN01                 GPIO_PORT_PIN(gpio0,  1)        // P0.01
#define GPIO0_PIN23                 GPIO_PORT_PIN(gpio0, 23)        // P0.23
#define GPIO0_PIN22                 GPIO_PORT_PIN(gpio0, 22)        // P0.22
#define GPIO0_PIN21                 GPIO_PORT_PIN(gpio0, 21)        // P0.21
#define GPIO0_PIN16                 GPIO_PORT_PIN(gpio0, 16)        // P0.16

// Around 3.3V Ring
#define GPIO0_PIN00                 GPIO_PORT_PIN(gpio0,  0)        // P0.00
#define GPIO0_PIN30                 GPIO_PORT_PIN(gpio0, 30)        // P0.30

// Aliases
#define	BUTTON_A                    GPIO0_PIN17
#define	BUTTON_B                    GPIO0_PIN26
#define GPIO_RING_0                 GPIO0_PIN03
#define GPIO_RING_1                 GPIO0_PIN02
#define GPIO_RING_2                 GPIO0_PIN01

void uni_board_init(void);
