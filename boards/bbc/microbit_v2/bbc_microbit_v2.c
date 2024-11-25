/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

#include "drivers/button/drv_button_microbit.h"
#include "drivers/led/display/drv_disp_microbit.h"

void board_init(void)
{
	drv_init_button();
	drv_init_display();
}
