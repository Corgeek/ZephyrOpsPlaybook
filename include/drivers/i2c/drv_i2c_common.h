/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/kernel.h>

bool drv_init_i2c(void);

/* for 8bit size register address */
//  int i2c_reg_write_byte(const struct device *dev, uint16_t dev_addr, uint8_t reg_addr, uint8_t value);
int32_t i2c_reg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t value);
int32_t i2c_reg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t value);
int32_t i2c_reg_write_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint8_t *wbuf, size_t len);

//  int i2c_reg_read_byte(const struct device *dev, uint16_t dev_addr, uint8_t reg_addr, uint8_t *value)
int32_t i2c_reg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t *rbuf);
int32_t i2c_reg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *rbuf);
int32_t i2c_reg_read_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *rbuf, size_t len);

/* for 16bit size register address */
int32_t i2c_wreg_write_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t value);
int32_t i2c_wreg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t value);
int32_t i2c_wreg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t value);
int32_t i2c_wreg_write_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *wbuf, size_t len);

int32_t i2c_wreg_read_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *rbuf);
int32_t i2c_wreg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t *rbuf);
int32_t i2c_wreg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *rbuf);
int32_t i2c_wreg_read_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *rbuf, size_t len);
