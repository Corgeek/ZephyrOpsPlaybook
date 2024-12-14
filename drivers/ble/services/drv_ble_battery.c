/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/services/bas.h>
#include "drivers/ble/services/drv_ble_battery.h"

static uint8_t s_battery_level = 60;        // dummy value

void drv_bas_level_notify(void)
{
    bt_bas_set_battery_level(s_battery_level);
}
