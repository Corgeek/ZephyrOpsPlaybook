/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "boards/unique.h"

int main(void)
{
	uni_board_init();

	while (true) {
		k_msleep(1000);
	}

	return 0;
}
