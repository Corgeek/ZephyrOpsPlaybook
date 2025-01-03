/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <assert.h>
#include "boards/unique.h"
#include "drivers/sensor/measure/drv_tof_sequence.h"
#include "drivers/sensor/measure/drv_tof_vl53l4cd.h"

#define VL53L4CD_SENSOR_ID       (0xEBAA)

static struct vl53l4cd_ctx s_tof_ctx[TOF_ID_MAX] = {
    [TOF_ID_1ST] = {
        .i2c   = I2C_100KHZ_BUS,
        .xshut = TOF_XSHUT,
        .gpio  = { NULL, 0 },
        .addr  = TOF_1ST_ADDR
    },
};

void drv_tof_power(int32_t tof_id, bool on_off)
{
    gpio_pin_set(s_tof_ctx[tof_id].xshut.port, s_tof_ctx[tof_id].xshut.pin, on_off ? 1 : 0);
    k_msleep(10);
}

// Setup sequence
void drv_tof_reset(int32_t tof_id)
{
    if (drv_tof_wait_for_init(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr) == false) {
        printk("drv_tof_wait_for_init() is timeouted\n");
        return;
    }

    // Load default configuration
    drv_tof_load_defconf(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);

    // Start VHV
    drv_tof_start_system(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);

    for (int32_t i = 0; i < 1000; ++i) {
        if (drv_tof_check_for_data_ready(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr) == 1)
            break;

        k_msleep(1);
    }

    drv_tof_clear_interrupt(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);
    drv_tof_stop_ranging(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);
    drv_tof_dev_setting(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);

    if (drv_tof_set_range_timing(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr, 50, 0) == false)
        printk("drv_tof_set_range_timing() is failed\n");
}

bool drv_init_tof(int32_t tof_id)
{
    int result = 0;

    // Setup port-pin
    if (device_is_ready(s_tof_ctx[tof_id].xshut.port) == false) {
        printk("%s is not ready\n", s_tof_ctx[tof_id].xshut.port->name);
        return false;
    }

    if (s_tof_ctx[tof_id].gpio.port != NULL) {
        if (device_is_ready(s_tof_ctx[tof_id].gpio.port) == false) {
            printk("%s is not ready\n", s_tof_ctx[tof_id].gpio.port->name);
            return false;
        }
    }

    result = gpio_pin_configure(s_tof_ctx[tof_id].xshut.port, s_tof_ctx[tof_id].xshut.pin, GPIO_OUTPUT);
    if (result) {
        printk("%s configure failed\n", s_tof_ctx[tof_id].gpio.port->name);
        return false;
    }

    // Start initial sequence
    drv_tof_power(tof_id, false);
    drv_tof_power(tof_id, true);

    // Change slave address
    if (drv_tof_set_address(s_tof_ctx[tof_id].i2c, VL53L4CD_DEF_ADDR, s_tof_ctx[tof_id].addr)) {
        printk("VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS is failed[%x]\n", s_tof_ctx[tof_id].addr);
        return false;
    }

    // Get Sensor ID
    uint32_t val = 0;
    val = drv_tof_get_model_id(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);
    if (val != VL53L4CD_SENSOR_ID) {
        return false;
    }

    // InitSensor
    drv_tof_reset(tof_id);

    // Program the highest possible TimingBudget, without enabling the
    // low power mode. This should give the best accuracy
    drv_tof_set_range_timing(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr, 200, 0);

    k_msleep(1000);

    // Start Measurements
    drv_tof_start_ranging(s_tof_ctx[tof_id].i2c, s_tof_ctx[tof_id].addr);

    return true;
}
