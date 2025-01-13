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
    { .dev = I2C_100KHZ_BUS, .speed = I2C_SPEED_STANDARD, .is_ready = false },
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

/* for 8bit size register address */
int32_t i2c_reg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t value)
{
    uint8_t wbuf[3] = { reg_addr, value >> 8, value & 0xFF };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_reg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t value)
{
    uint8_t wbuf[5] = { reg_addr,
        (value >> 24) & 0xFF,
        (value >> 16) & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_reg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint16_t *rbuf)
{
    int32_t result = 0;

    result = i2c_write(i2c_dev, &reg_addr, sizeof(reg_addr), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    result = i2c_read(i2c_dev, (uint8_t*)rbuf, sizeof(*rbuf), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }

    return result;
}

int32_t i2c_reg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint8_t reg_addr, uint32_t *rbuf)
{
    int32_t result = 0;

    result = i2c_write(i2c_dev, &reg_addr, sizeof(reg_addr), slv_addr);
    if (result) {
        printk("i2c_write() of %s() is failed[%x]\n", __func__, reg_addr);
        return result;
    }

    result = i2c_read(i2c_dev, (uint8_t*)rbuf, sizeof(*rbuf), slv_addr);
    if (result) {
        printk("i2c_read() of %s() is failed[%x]\n", __func__, reg_addr);
    }

    return result;
}

/* for 16bit size register address */
int32_t i2c_wreg_write_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t value)
{
    uint8_t wbuf[3] = { reg_addr >> 8, reg_addr & 0xFF, value };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_wreg_write_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t value)
{
    uint8_t wbuf[4] = { reg_addr >> 8, reg_addr & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_wreg_write_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t value)
{
    uint8_t wbuf[6] = { reg_addr >> 8, reg_addr & 0xFF,
        (value >> 24) & 0xFF,
        (value >> 16) & 0xFF,
        (value >>  8) & 0xFF,
        (value      ) & 0xFF,
    };
    return i2c_write(i2c_dev, wbuf, sizeof(wbuf), slv_addr);
}

int32_t i2c_wreg_read_byte(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint8_t *rbuf)
{
    int32_t result = 0;
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
        *rbuf = tmp;
    }

    return result;
}

int32_t i2c_wreg_read_word(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint16_t *rbuf)
{
    int32_t result = 0;
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
        *rbuf = tmp[0] << 8 | tmp[1];
    }

    return result;
}

int32_t i2c_wreg_read_dword(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t reg_addr, uint32_t *rbuf)
{
    int32_t result = 0;
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
    *rbuf = tmp[0] << 24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];

    return result;
}
