/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "boards/unique.h"
#include "flow/seq_sensor_manager.h"
#include "global/gbf_sensor_database.h"

int main(void)
{
	uni_board_init();

	while (true) {
		seq_sensor_manager();
		k_msleep(100);
	}

	return 0;
}
