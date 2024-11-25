# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ZephyrSkeleton)

include_directories(app
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/boards)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/global)

target_sources(app
PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/main.c
)

zephyr_compile_options(-Werror -Wno-address-of-packed-member)
