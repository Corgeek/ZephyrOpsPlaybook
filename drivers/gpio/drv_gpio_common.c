/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "drivers/gpio/drv_gpio_common.h"

int drv_init_gpio(const struct gpio_port_pin *pp, gpio_flags_t flags, int init)
{
    int ret;

    if (!gpio_is_valid(pp)) {
        return 0;
    }

    ret = gpio_pin_configure(pp->port, pp->pin, flags);
    if (ret < 0) {
        return ret;
    }

    return GPIO_OUTPUT & flags ? gpio_pin_set_raw(pp->port, pp->pin, init) : ret;
}

bool gpio_is_valid(const struct gpio_port_pin *pp)
{
    return pp->port != NULL;
}
