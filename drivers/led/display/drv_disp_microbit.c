/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include "drivers/led/display/drv_disp_microbit.h"

/**
 * @brief singleton of display instance
 */
static
struct mb_display *get_disp_instance(void)
{
    static struct mb_display *s_disp_microbit;

    if (s_disp_microbit == NULL)
        s_disp_microbit = mb_display_get();

    return s_disp_microbit;
}

bool drv_init_display(void)
{
    get_disp_instance();

    return true;
}

void drv_disp_image(uint32_t mode, int32_t duration, const struct mb_image *img, uint8_t img_count)
{
    mb_display_image(get_disp_instance(), mode, duration, img, img_count);
}

void drv_disp_print(uint32_t mode, int32_t duration, const char *text)
{
    mb_display_print(get_disp_instance(), mode, duration, "%s", text);
}

void drv_disp_stop(void)
{
    mb_display_stop(get_disp_instance());
}
