# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if     (CONFIG_BOARD_BBC_MICROBIT)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/bbc/microbit)
elseif (CONFIG_BOARD_BBC_MICROBIT_V2)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/bbc/microbit_v2)
elseif (CONFIG_BOARD_NUCLEO_F401RE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/st)
else   ()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/generic)
endif  ()
