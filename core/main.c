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

//  gpio_pin_configure(USER_LED.port, USER_LED.pin, GPIO_OUTPUT_ACTIVE);

    while (true) {
//      gpio_pin_toggle(USER_LED.port, USER_LED.pin);
        k_msleep(1000);
    }

    return 0;
}
