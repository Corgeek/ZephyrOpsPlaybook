/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief CRC-8/SMBUS (poly=0x07, init=0x00)
 */
uint8_t utl_crc8_get(const uint8_t *data, size_t len);

/**
 */
uint8_t utl_crc8_update(uint8_t crc, const uint8_t *data, size_t len);

#ifdef  __cplusplus
}
#endif
