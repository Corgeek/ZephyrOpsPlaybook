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

struct i2c_config {
    const struct device *const dev;
    uint8_t speed;
    bool is_ready;
};

static struct i2c_config s_i2c_dev[] = {
#ifdef I2C_100KHZ_BUS
    [I2C_ID_SNSR] = { .dev = I2C_100KHZ_BUS, .speed = I2C_SPEED_STANDARD, .is_ready = false },
#endif // I2C_100KHZ_BUS
};

bool drv_init_i2c(void)
{
    int ret = 0;

    for (int i = 0; i < ARRAY_SIZE(s_i2c_dev); ++i) {
        s_i2c_dev[i].is_ready = device_is_ready(s_i2c_dev[i].dev);
        if (s_i2c_dev[i].is_ready == false) {
            printk("i2c is not ready[%s]\n", s_i2c_dev[i].dev->name);
            continue;
        }

        ret = i2c_configure(s_i2c_dev[i].dev, I2C_MODE_CONTROLLER | I2C_SPEED_SET(s_i2c_dev[i].speed));
        if (ret) {
            printk("i2c_configure() failed[%s]\n", s_i2c_dev[i].dev->name);
            continue;
        }
    }

    return true;
}

int32_t i2c_reg_write_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint8_t *wbuf, size_t len)
{
    uint8_t buf[1 + len];

    buf[0] = reg_addr;
    memcpy(&buf[1], wbuf, len);
    return i2c_write(i2c_dev, buf, sizeof(buf), slv_addr);
}

int32_t i2c_wreg_write_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t value)
{
    uint8_t wbuf[3] = { reg_addr >> 8, reg_addr & 0xFF, value };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_wreg_write_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *wbuf, size_t len)
{
    uint8_t buf[2 + len];

    buf[0] = reg_addr >> 8;
    buf[1] = reg_addr & 0xFF;
    memcpy(&buf[2], wbuf, len);
    return i2c_write(i2c_dev, buf, sizeof(buf), slv_addr);
}

int32_t i2c_reg_read_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *rbuf, size_t len)
{
    assert(len == 1 || len == 2 || len == 4);

    uint8_t data[4] = { 0 };
    int result;

    result = i2c_write(i2c_dev, &reg_addr, 1, slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    result = i2c_read(i2c_dev, data, len, slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x, %d]\n", __func__, reg_addr, len);
        return result;
    }

    if      (len == 1)  *rbuf = data[0];
    else if (len == 2)  *rbuf = data[0] <<  8 | data[1];
    else if (len == 4)  *rbuf = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

    return result;
}

int32_t i2c_wreg_read_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *rbuf)
{
    int32_t result = 0;
    uint8_t wbuf[] = { reg_addr >> 8, reg_addr & 0xFF };

    result = i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    result = i2c_read(i2c_dev, rbuf, sizeof(uint8_t), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }

    return result;
}

int32_t i2c_wreg_read_multi(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *rbuf, size_t len)
{
    assert(len == 1 || len == 2 || len == 4);

    uint8_t wbuf[] = { reg_addr >> 8, reg_addr & 0xFF };
    uint8_t data[4] = { 0 };
    int result;

    result = i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    result = i2c_read(i2c_dev, data, len, slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x, %d]\n", __func__, reg_addr, len);
        return result;
    }

    if      (len == 1)  *rbuf = data[0];
    else if (len == 2)  *rbuf = data[0] <<  8 | data[1];
    else if (len == 4)  *rbuf = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

    return result;
}
