/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/sys/time_units.h>
#include "boards/unique.h"
#include "global/gbf_sensor_database.h"

int main(void)
{
	uni_board_init();
	gbf_init_sensor();

	while (true) {
#if 0
		struct sensor_3axis sensor;
		memset(&sensor, 0, sizeof(sensor));

		get_accel_xyz(&sensor);
		gbf_set_sensor(SENSOR_ACCEL, &sensor);

		get_magnet_xyz(&sensor);
		gbf_set_sensor(SENSOR_MAGNET, &sensor);
#endif
		k_msleep(1000);
	}

	return 0;
}
