# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

## Switch by Target 
if (BOARD STREQUAL "bbc_microbit")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/bbc/microbit/prj.conf)
elseif (BOARD STREQUAL "bbc_microbit_v2")
  set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/bbc/microbit_v2/prj.conf)
else()
  set(CONF_FILE prj.conf)
endif()

## Main Process
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ZephyrSkeleton)

include_directories(app
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/boards)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/global)

zephyr_compile_options(-Werror -Wno-address-of-packed-member)
