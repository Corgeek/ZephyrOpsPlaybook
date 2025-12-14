# Copyright (c) 2025 Takayuki Goto <goto.takayuki@space-entry.co.jp>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

target_sources(app
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/nucleo_g431kb.c
)
