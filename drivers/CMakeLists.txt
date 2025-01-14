# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if (CONFIG_BEEP)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/beep)
endif()

if (CONFIG_BT_PERIPHERAL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ble)
endif()

if (CONFIG_BUTTON)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/button)
endif()

if (CONFIG_I2C)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/i2c)
endif()

if (CONFIG_PWM)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/led)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/display)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/sensor)

if (CONFIG_SERIAL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/serial)
endif()
