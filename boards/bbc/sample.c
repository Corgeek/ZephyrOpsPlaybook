/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/sys/time_units.h>
#include "global/gbf_sensor_database.h"
#include "drivers/led/display/drv_disp_microbit.h"
#include "drivers/sensor/accel/drv_accel_lis2dh.h"
#include "drivers/sensor/magnet/drv_magn_lis2mdl.h"
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"

int main(void)
{
	board_init();

	gbf_init_sensor();

	struct sensor_3d sensor;
	uint32_t curr_cycle = 0;
	uint32_t last_cycle = 0;

	while (true) {
		last_cycle = curr_cycle;
		curr_cycle = k_cycle_get_32();
		printk("cycle: %d\n", k_ticks_to_us_floor32(curr_cycle - last_cycle));

		memset(&sensor, 0, sizeof(sensor));

		get_accel_xyz(&sensor);
		gbf_set_sensor(SENSOR_ACCEL, &sensor);

		get_magnet_xyz(&sensor);
		gbf_set_sensor(SENSOR_MAGNET, &sensor);

		k_msleep(1000 / SENSOR_ACCEL_FREQ_HZ);
	}

	return 0;
}
