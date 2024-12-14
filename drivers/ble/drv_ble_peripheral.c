/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include "drivers/ble/drv_ble_peripheral.h"
#include "drivers/ble/services/drv_ble_heartrate.h"

static const struct bt_data s_adv_param[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),
//              BT_UUID_16_ENCODE(BT_UUID_ESS_VAL),
//              BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL)),
};

static const struct bt_data s_scan_param[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

static
void ble_init_services(void)
{
    drv_hrs_register();
}

bool drv_init_bleperiph(void)
{
    int32_t ret = bt_enable(NULL);
    if (ret != 0) {
        printk("%s: bt_enable(NULL) is failed (%d)\n", __func__, ret);
        return false;
    }

    ble_init_services();
    drv_ble_conn_auth();

    ret = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1,
                s_adv_param, ARRAY_SIZE(s_adv_param), 
                s_scan_param, ARRAY_SIZE(s_scan_param));
    if (ret != 0) {
        printk("Advertising failed to start (%d)\n", ret);
        return false;
    }

    return true;
}
