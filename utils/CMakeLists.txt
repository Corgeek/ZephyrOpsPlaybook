# Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

if   (CONFIG_SHELL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/shell)
endif()