/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "drivers/led/display/drv_disp_microbit.h"

int main(void)
{
	drv_init_display();
	drv_disp_print(MB_DISPLAY_MODE_SINGLE, 1 * MSEC_PER_SEC, "Hello world");

	while (true) {
		k_msleep(1000);
	}

	return 0;
}
