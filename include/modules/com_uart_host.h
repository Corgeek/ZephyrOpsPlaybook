/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "modules/cmd_uart_format.h"

bool com_host_init(const struct device *uart_port);
void com_host_close(void);
bool com_host_read(struct com_host_frame *frame);
bool com_host_write(void);
bool com_host_write_data(uint8_t cmd, const uint8_t array[COM_DATA_ARRAY_SIZE]);
