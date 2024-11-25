# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if      (CONFIG_BOARD_BBC_MICROBIT)
target_sources(app
PRIVATE
    bbc/microbit/bbc_microbit.c
)
elseif  (CONFIG_BOARD_BBC_MICROBIT_V2)
target_sources(app
PRIVATE
    bbc/microbit_v2/bbc_microbit_v2.c
)
endif()
