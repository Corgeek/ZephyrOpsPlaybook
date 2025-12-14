/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

struct i2c_bus_config {
    const struct device *const bus;
    uint8_t speed;
    bool is_ready;
};

#ifdef  __cplusplus
extern "C" {
#endif

bool drv_init_i2c(struct i2c_bus_config *i2c_dev);

/* for 8bit size register address */
//  int i2c_reg_write_byte(const struct device *dev, uint16_t dev_addr, uint8_t reg_addr, uint8_t value);
int i2c_reg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t value);
int i2c_reg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t value);

//  int i2c_reg_read_byte(const struct device *dev, uint16_t dev_addr, uint8_t reg_addr, uint8_t *value)
int i2c_reg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t *value);
int i2c_reg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *value);

/* for 16bit size register address */
int i2c_wreg_write_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t value);
int i2c_wreg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t value);
int i2c_wreg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t value);

int i2c_wreg_read_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *value);
int i2c_wreg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t *value);
int i2c_wreg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *value);

#ifdef  __cplusplus
}
#endif
