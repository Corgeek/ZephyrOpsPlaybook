# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if (CONFIG_BT_BAS)
target_sources(app
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drv_ble_battery.c
)
endif()

if (CONFIG_BT_HRS)
target_sources(app
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drv_ble_heartrate.c
)
endif()
