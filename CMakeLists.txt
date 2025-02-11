# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

## Switch by Target 
if (BOARD STREQUAL "bbc_microbit")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/bbc/microbit/prj.conf)
elseif (BOARD STREQUAL "bbc_microbit_v2")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/bbc/microbit_v2/prj.conf)
elseif (BOARD STREQUAL "nucleo_f030r8")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/st/nucleo_f030r8/prj.conf)
elseif (BOARD STREQUAL "nucleo_f401re")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/st/nucleo_f401re/prj.conf)
elseif (BOARD STREQUAL "nucleo_l552ze_q")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/st/nucleo_l552ze_q/prj.conf)
elseif (BOARD STREQUAL "stm32h747i_disco")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/st/stm32h747i_disco/prj.conf)
elseif (BOARD STREQUAL "rpi_pico")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/raspberrypi/rpi_pico/prj.conf)
elseif (BOARD STREQUAL "rpi_pico2")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/raspberrypi/rpi_pico2/prj.conf)
else()
  set(CONF_FILE prj.conf)
endif()

## Main Process
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ZephyrPlaybook)

include_directories(app
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/boards)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/flow)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/global)

zephyr_compile_options(-Werror -Wno-address-of-packed-member)
