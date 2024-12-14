/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include "drivers/ble/drv_ble_peripheral.h"

static ATOMIC_DEFINE(s_pairing_state, 2U);

static
void drv_ble_connected(struct bt_conn *conn, uint8_t cause)
{
	if (cause) {
		printk("Connection failed, [0x%02x] %s\n", cause, bt_hci_err_to_str(cause));
	} else {
		printk("Connected\n");
		atomic_set_bit(s_pairing_state, BLE_STATE_CONNECTED);
	}
}

static
void drv_ble_disconnected(struct bt_conn *conn, uint8_t cause)
{
	printk("Disconnected, reason 0x%02x %s\n", cause, bt_hci_err_to_str(cause));
	atomic_set_bit(s_pairing_state, BLE_STATE_DISCONNECTED);
}

static
void drv_ble_auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

BT_CONN_CB_DEFINE(s_ble_conn_cb) = {
	.connected = drv_ble_connected,
	.disconnected = drv_ble_disconnected,
};

static struct bt_conn_auth_cb s_ble_auth_cb = {
	.cancel = drv_ble_auth_cancel,
};

void drv_ble_conn_auth(void)
{
    bt_conn_auth_cb_register(&s_ble_auth_cb);
}
