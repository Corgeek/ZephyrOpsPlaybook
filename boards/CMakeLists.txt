# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if     (CONFIG_BOARD_BBC_MICROBIT)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/bbc/microbit)
elseif (CONFIG_BOARD_BBC_MICROBIT_V2)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/bbc/microbit_v2)
elseif (CONFIG_BOARD_NUCLEO_F030R8)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/st/nucleo_f030r8)
elseif (CONFIG_BOARD_NUCLEO_F401RE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/st/nucleo_f401re)
elseif (CONFIG_BOARD_NUCLEO_L552ZE_Q)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/st/nucleo_l552ze_q)
elseif (CONFIG_BOARD_STM32H747I_DISCO_STM32H747XX_M7)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/st/stm32h747i_disco)
elseif (CONFIG_BOARD_RPI_PICO)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/raspberrypi/rpi_pico)
elseif (CONFIG_BOARD_RPI_PICO2)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/raspberrypi/rpi_pico2)
else   ()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/generic)
endif  ()
