/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "drivers/led/display/drv_disp_microbit.h"
#include "drivers/sensor/accel/drv_accel_lis2dh.h"
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"

int main(void)
{
	board_init();

	drv_disp_print(MB_DISPLAY_MODE_SINGLE, 150, "Hello world");

	struct sensor_value accel[3];

	while (true) {
		memset(accel, 0, sizeof(accel));
		get_accel_xyz(&accel[0], &accel[1], &accel[2]);
#ifdef CONFIG_CBPRINTF_FP_SUPPORT
		printk("accel [m/s^2]:    (%12.6f, %12.6f, %12.6f)\n",
			sensor_value_to_double(&accel[0]), sensor_value_to_double(&accel[1]),
			sensor_value_to_double(&accel[2]));
#else // !CONFIG_CBPRINTF_FP_SUPPORT
		printk("accel [m/s^2]:    (%6d.%6d, %6d.%6d, %6d.%6d)\n", accel[0], accel[1], accel[2]);
#endif // CONFIG_CBPRINTF_FP_SUPPORT
		k_msleep(100);
	}

	return 0;
}
