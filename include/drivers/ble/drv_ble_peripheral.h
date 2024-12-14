/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

enum {
    BLE_STATE_CONNECTED = (1 << 0),
    BLE_STATE_DISCONNECTED = (1 << 1),
};

bool drv_init_bleperiph(void);
void drv_ble_conn_auth(void);
