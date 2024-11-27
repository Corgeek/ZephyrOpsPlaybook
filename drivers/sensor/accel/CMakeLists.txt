# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if (CONFIG_LIS2DH)
target_sources(app
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drv_accel_lis2dh.c
)
endif()

