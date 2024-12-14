/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/services/hrs.h>
#include "drivers/ble/services/drv_ble_heartrate.h"

static sys_slist_t s_hrs_cblist = SYS_SLIST_STATIC_INIT(&s_hrs_cblist);
static bool s_hrs_enabled = false;

static void drv_hrs_changed(bool enabled)
{
	s_hrs_enabled = enabled;

	printk("HRS notification status changed: %s\n",
	       enabled ? "enabled" : "disabled");
}

static struct bt_hrs_cb s_cb_heartrate = {
	.ntf_changed = drv_hrs_changed,
};

void drv_hrs_register(void)
{
    sys_slist_append(&s_hrs_cblist, &s_cb_heartrate._node);
}
