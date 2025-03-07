/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include "boards/unique.h"

extern const lv_image_dsc_t g_img_osc_tokyo;

int main(void)
{
	lv_obj_t *img;

	img = lv_image_create(lv_screen_active());
	lv_image_set_src(img, &g_img_osc_tokyo);
	lv_obj_center(img);

	while (true) {
		k_msleep(MIN(lv_timer_handler(), INT32_MAX));
	}

	return 0;
}
