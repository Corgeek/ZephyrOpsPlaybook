/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <assert.h>
#include "boards/unique.h"
#include "drivers/i2c/drv_i2c_common.h"

bool drv_init_i2c(struct i2c_bus_config *i2c_dev)
{
    int ret = 0;

    ret = device_is_ready(i2c_dev->bus);
    if (ret == 0) {
        printk("i2c is not ready[%s]\n", i2c_dev->bus->name);
        return i2c_dev->is_ready = false;
    }

    ret = i2c_configure(i2c_dev->bus, I2C_MODE_CONTROLLER | I2C_SPEED_SET(i2c_dev->speed));
    if (ret) {
        printk("i2c_configure() failed[%s]\n", i2c_dev->bus->name);
        return i2c_dev->is_ready = false;
    }

    return i2c_dev->is_ready = true;
}

/* for 8bit size register address */
int i2c_reg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t value)
{
    uint8_t wbuf[3] = { reg_addr, value >> 8, value & 0xFF };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int i2c_reg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t value)
{
    uint8_t wbuf[5] = { reg_addr,
        (value >> 24) & 0xFF,
        (value >> 16) & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int i2c_reg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t *value)
{
    int result = 0;

    result = i2c_write(i2c_dev, &reg_addr, sizeof(reg_addr), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    uint8_t tmp[2];
    result = i2c_read(i2c_dev, tmp, sizeof(tmp), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }
    *value = tmp[0] << 8 | tmp[1];

    return result;
}

int i2c_reg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *value)
{
    int result = 0;

    result = i2c_write(i2c_dev, &reg_addr, sizeof(reg_addr), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    uint8_t tmp[4];
    result = i2c_read(i2c_dev, tmp, sizeof(tmp), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }
    *value = tmp[0] << 24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];

    return result;
}

/* for 16bit size register address */
int i2c_wreg_write_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t value)
{
    uint8_t wbuf[3] = { reg_addr >> 8, reg_addr & 0xFF, value };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int i2c_wreg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t value)
{
    uint8_t wbuf[4] = { reg_addr >> 8, reg_addr & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int i2c_wreg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t value)
{
    uint8_t wbuf[6] = { reg_addr >> 8, reg_addr & 0xFF,
        (value >> 24) & 0xFF,
        (value >> 16) & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int i2c_wreg_read_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *value)
{
    int result = 0;
    uint8_t wbuf[2] = { reg_addr >> 8, reg_addr & 0xFF };

    result = i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    uint8_t tmp;
    result = i2c_read(i2c_dev, &tmp, sizeof(tmp), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    } else {
        *value = tmp;
    }

    return result;
}

int i2c_wreg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t *value)
{
    int result = 0;
    uint8_t wbuf[2] = { reg_addr >> 8, reg_addr & 0xFF };

    result = i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    uint8_t tmp[2];
    result = i2c_read(i2c_dev, tmp, sizeof(tmp), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    } else {
        *value = tmp[0] << 8 | tmp[1];
    }

    return result;
}

int i2c_wreg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *value)
{
    int result = 0;
    uint8_t wbuf[2] = { reg_addr >> 8, reg_addr & 0xFF };

    result = i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    uint8_t tmp[4];
    result = i2c_read(i2c_dev, tmp, sizeof(tmp), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }
    *value = tmp[0] << 24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];

    return result;
}
