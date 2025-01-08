/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <assert.h>
#include "boards/unique.h"

#include "drivers/i2c/drv_i2c_common.h"
#include "drivers/sensor/measure/drv_tof_vl53l4cd.h"
#include "drivers/sensor/measure/vl53l4cd_api.h"

#define VL53L4CD_SENSOR_ID                      (0xEBAA)
#define VL53L4CD_DEFAULT_CONFIG_START_REG       (0x2D)
#define VL53L4CD_DEFAULT_CONFIG_END_REG         (0x87)

static const uint8_t s_vl53l4cd_default_config[] = {
  0x12, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C),
   else don't touch */
  0x00, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1
   (pull up at AVDD) */
  0x00, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1
  (pull up at AVDD) */
  0x11, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low
  (bits 3:0 must be 0x1), use SetInterruptPolarity() */
  0x02, /* 0x31 : bit 1 = interrupt depending on the polarity,
  use CheckForDataReady() */
  0x00, /* 0x32 : not user-modifiable */
  0x02, /* 0x33 : not user-modifiable */
  0x08, /* 0x34 : not user-modifiable */
  0x00, /* 0x35 : not user-modifiable */
  0x08, /* 0x36 : not user-modifiable */
  0x10, /* 0x37 : not user-modifiable */
  0x01, /* 0x38 : not user-modifiable */
  0x01, /* 0x39 : not user-modifiable */
  0x00, /* 0x3a : not user-modifiable */
  0x00, /* 0x3b : not user-modifiable */
  0x00, /* 0x3c : not user-modifiable */
  0x00, /* 0x3d : not user-modifiable */
  0xff, /* 0x3e : not user-modifiable */
  0x00, /* 0x3f : not user-modifiable */
  0x0F, /* 0x40 : not user-modifiable */
  0x00, /* 0x41 : not user-modifiable */
  0x00, /* 0x42 : not user-modifiable */
  0x00, /* 0x43 : not user-modifiable */
  0x00, /* 0x44 : not user-modifiable */
  0x00, /* 0x45 : not user-modifiable */
  0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high,
  2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
  0x0b, /* 0x47 : not user-modifiable */
  0x00, /* 0x48 : not user-modifiable */
  0x00, /* 0x49 : not user-modifiable */
  0x02, /* 0x4a : not user-modifiable */
  0x14, /* 0x4b : not user-modifiable */
  0x21, /* 0x4c : not user-modifiable */
  0x00, /* 0x4d : not user-modifiable */
  0x00, /* 0x4e : not user-modifiable */
  0x05, /* 0x4f : not user-modifiable */
  0x00, /* 0x50 : not user-modifiable */
  0x00, /* 0x51 : not user-modifiable */
  0x00, /* 0x52 : not user-modifiable */
  0x00, /* 0x53 : not user-modifiable */
  0xc8, /* 0x54 : not user-modifiable */
  0x00, /* 0x55 : not user-modifiable */
  0x00, /* 0x56 : not user-modifiable */
  0x38, /* 0x57 : not user-modifiable */
  0xff, /* 0x58 : not user-modifiable */
  0x01, /* 0x59 : not user-modifiable */
  0x00, /* 0x5a : not user-modifiable */
  0x08, /* 0x5b : not user-modifiable */
  0x00, /* 0x5c : not user-modifiable */
  0x00, /* 0x5d : not user-modifiable */
  0x01, /* 0x5e : not user-modifiable */
  0xcc, /* 0x5f : not user-modifiable */
  0x07, /* 0x60 : not user-modifiable */
  0x01, /* 0x61 : not user-modifiable */
  0xf1, /* 0x62 : not user-modifiable */
  0x05, /* 0x63 : not user-modifiable */
  0x00, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB),
   use SetSigmaThreshold(), default value 90 mm  */
  0xa0, /* 0x65 : Sigma threshold LSB */
  0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB),
   use SetSignalThreshold() */
  0x80, /* 0x67 : Min count Rate LSB */
  0x08, /* 0x68 : not user-modifiable */
  0x38, /* 0x69 : not user-modifiable */
  0x00, /* 0x6a : not user-modifiable */
  0x00, /* 0x6b : not user-modifiable */
  0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register,
   use SetIntermeasurementInMs() */
  0x00, /* 0x6d : Intermeasurement period */
  0x0f, /* 0x6e : Intermeasurement period */
  0x89, /* 0x6f : Intermeasurement period LSB */
  0x00, /* 0x70 : not user-modifiable */
  0x00, /* 0x71 : not user-modifiable */
  0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB),
   use SetD:tanceThreshold() */
  0x00, /* 0x73 : distance threshold high LSB */
  0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB),
   use SetD:tanceThreshold() */
  0x00, /* 0x75 : distance threshold low LSB */
  0x00, /* 0x76 : not user-modifiable */
  0x01, /* 0x77 : not user-modifiable */
  0x07, /* 0x78 : not user-modifiable */
  0x05, /* 0x79 : not user-modifiable */
  0x06, /* 0x7a : not user-modifiable */
  0x06, /* 0x7b : not user-modifiable */
  0x00, /* 0x7c : not user-modifiable */
  0x00, /* 0x7d : not user-modifiable */
  0x02, /* 0x7e : not user-modifiable */
  0xc7, /* 0x7f : not user-modifiable */
  0xff, /* 0x80 : not user-modifiable */
  0x9B, /* 0x81 : not user-modifiable */
  0x00, /* 0x82 : not user-modifiable */
  0x00, /* 0x83 : not user-modifiable */
  0x00, /* 0x84 : not user-modifiable */
  0x01, /* 0x85 : not user-modifiable */
  0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
  0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(),
   If you want an automatic start after VL53L4CD_init() call,
    put 0x40 in location 0x87 */
};

static
uint8_t drv_vl53l4cd_check_for_data_ready(const struct device *const i2c_dev, uint16_t slv_addr)
{
    uint8_t val = 0;
    uint8_t int_pol;

    i2c_wreg_read_byte(i2c_dev, slv_addr,
            VL53L4CD_GPIO_HV_MUX_CTRL, &val);
    val = (val & 0x10) >> 4;
    int_pol = val ? 0x00 : 0x01;

    i2c_wreg_read_byte(i2c_dev, slv_addr,
            VL53L4CD_GPIO_TIO_HV_STATUS, &val);

    return ((val & 0x01) == int_pol) ? 1 : 0;
}

static
int32_t drv_vl53l4cd_clear_interrupt(const struct device *const i2c_dev, uint16_t slv_addr)
{
    return i2c_wreg_write_byte(i2c_dev, slv_addr,
            VL53L4CD_SYSTEM_INTERRUPT_CLEAR, 0x01);
}

static
int32_t drv_vl53l4cd_start_ranging(const struct device *const i2c_dev, uint16_t slv_addr)
{
    int32_t result = 0;
    uint32_t value = 0;

    result |= i2c_wreg_read_dword(i2c_dev, slv_addr,
                VL53L4CD_INTERMEASUREMENT_MS, &value);

    // Sensor runs in continuous mode
    if (value == 0) {
        result |= i2c_wreg_write_byte(i2c_dev, slv_addr,
                VL53L4CD_SYSTEM_START, 0x21);
    }
    // Sensor runs in autonomous mode
    else {
        result |= i2c_wreg_write_byte(i2c_dev, slv_addr,
                VL53L4CD_SYSTEM_START, 0x40);
    }

    int32_t tmp_res = VL53L4CD_ERROR_TIMEOUT;
    for (int32_t i = 0; i < 1000; ++i) {
        if (drv_vl53l4cd_check_for_data_ready(i2c_dev, slv_addr) == 1) {
            tmp_res = 0;
            break;
        }

        k_msleep(1);
    }
    result |= tmp_res;
    result |= drv_vl53l4cd_clear_interrupt(i2c_dev, slv_addr);

    return result;
}

static
int32_t drv_vl53l4cd_start_system(const struct device *const i2c_dev, uint16_t slv_addr)
{
    return i2c_wreg_write_byte(i2c_dev, slv_addr,
                VL53L4CD_SYSTEM_START, 0x40);
}

static
int32_t drv_vl53l4cd_stop_ranging(const struct device *const i2c_dev, uint16_t slv_addr)
{
    return i2c_wreg_write_byte(i2c_dev, slv_addr,
                VL53L4CD_SYSTEM_START, 0x00);
}

static
bool drv_vl53l4cd_set_range_timing(const struct device *const i2c_dev, uint16_t slv_addr, uint32_t timing_budget_ms, uint32_t inter_measurement_ms)
{
    int32_t result = 0;
    uint16_t osc_freq = 0;
    uint32_t macro_period_us = 0, timing_budget_us = 0;
    float inter_measurement_factor = (float)1.055;

    result |= i2c_wreg_read_word(i2c_dev, slv_addr,
                0x0006, &osc_freq);
    if (osc_freq != 0) {
        timing_budget_us = timing_budget_ms * (uint32_t)1000;
        macro_period_us = (uint32_t)((uint32_t)2304 * ((uint32_t)0x40000000 / (uint32_t)osc_freq)) >> 6;
    }

    // Timing budget check validity
    if (timing_budget_ms < (uint32_t)10 || timing_budget_ms > (uint32_t)200 || result) {
        return false;
    }

    // Sensor runs in continuous mode
    if (inter_measurement_ms == 0) {
        result |= i2c_wreg_write_dword(i2c_dev, slv_addr,
            VL53L4CD_INTERMEASUREMENT_MS, 0);
        timing_budget_us -= 2500;
    }
    // Sensor runs in autonomous low power mode
    else if (inter_measurement_ms > timing_budget_ms) {
        uint16_t clock_pll = 0;
        result |= i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_RESULT_OSC_CALIBRATE_VAL, &clock_pll);
        clock_pll = clock_pll & (uint16_t)0x3FF;

        inter_measurement_factor = inter_measurement_factor
                                * (float)inter_measurement_ms
                                * (float)clock_pll;

        result |= i2c_wreg_write_multi(i2c_dev, slv_addr,
            VL53L4CD_INTERMEASUREMENT_MS, (uint8_t*)&inter_measurement_factor, sizeof(inter_measurement_factor));

        timing_budget_us -= (uint32_t)4300;
        timing_budget_us /= (uint32_t)2;
    }
    //  Invalid case
    else {
        return false;
    }

    uint32_t tmp;
    uint32_t ls_byte;

    timing_budget_us = timing_budget_us << 12;

    tmp = macro_period_us * 16;
    ls_byte = ((timing_budget_us + ((tmp >> 6) >> 1)) / (tmp >> 6)) - 1;

    uint16_t ms_byte = 0;
    while ((ls_byte & 0xFFFFFF00U) > 0U) {
        ls_byte = ls_byte >> 1;
        ms_byte++;
    }
    ms_byte = (uint16_t)(ms_byte << 8) + (uint16_t)(ls_byte & (uint32_t)0xFF);
    result |= i2c_wreg_write_word(i2c_dev, slv_addr,
            VL53L4CD_RANGE_CONFIG_A, ms_byte);

    tmp = macro_period_us * 12;
    ls_byte = ((timing_budget_us + ((tmp >> 6) >> 1)) / (tmp >> 6)) - 1;

    ms_byte = 0;
    while ((ls_byte & 0xFFFFFF00U) > 0U) {
        ls_byte = ls_byte >> 1;
        ms_byte++;
    }
    ms_byte = (uint16_t)(ms_byte << 8) + (uint16_t)(ls_byte & (uint32_t)0xFF);
    result |= i2c_wreg_write_word(i2c_dev, slv_addr,
            VL53L4CD_RANGE_CONFIG_B, ms_byte);

    return true;
}

static
int32_t drv_vl53l4cd_set_address(const struct device *const i2c_dev, uint16_t cur_addr, uint16_t new_addr)
{
    if (cur_addr == new_addr)
        return 0;

    return i2c_wreg_write_byte(i2c_dev, cur_addr,
            VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS, new_addr);
}

static
int32_t drv_vl53l4cd_get_model_id(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t *model_id)
{
    return i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_IDENTIFICATION_MODEL_ID, model_id);
}

static
bool drv_vl53l4cd_wait_for_init(const struct device *const i2c_dev, uint16_t slv_addr)
{
    uint8_t firm = 0;

    for (int32_t i = 0; i < 1000; ++i) {
        i2c_wreg_read_byte(i2c_dev, slv_addr,
            VL53L4CD_FIRMWARE_SYSTEM_STATUS, &firm);

        // 0x3 means booted
        if (firm == 0x3)
            return true;

        k_msleep(1);
    }

    return false;
}

static
int32_t drv_vl53l4cd_load_defconf(const struct device *const i2c_dev, uint16_t slv_addr)
{
    int32_t result = 0;

    // Load default configuration
    for (uint8_t i = 0; i < ARRAY_SIZE(s_vl53l4cd_default_config); ++i) {
        result |= i2c_wreg_write_byte(i2c_dev, slv_addr,
                VL53L4CD_DEFAULT_CONFIG_START_REG + i, s_vl53l4cd_default_config[i]);
    }

    return result;
}

static
int32_t drv_vl53l4cd_dev_setting(const struct device *const i2c_dev, uint16_t slv_addr)
{
    int32_t result = 0;

    result |= i2c_wreg_write_byte(i2c_dev, slv_addr, VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND, 0x09);
    result |= i2c_wreg_write_byte(i2c_dev, slv_addr, 0x000B, 0x00);
    result |= i2c_wreg_write_word(i2c_dev, slv_addr, 0x0024, 0x500);

    return result;
}

static
int32_t drv_vl53l4cd_get_signal_rate(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t *value)
{
    return i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_RESULT_SIGNAL_RATE, value);
}
/*
static
int32_t drv_vl53l4cd_get_ambient_rate(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t *value)
{
    return i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_RESULT_AMBIENT_RATE, value);
}

static
int32_t drv_vl53l4cd_get_sigma(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t *value)
{
    return i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_RESULT_SIGMA, value);
}
*/
static
int32_t drv_vl53l4cd_get_distance(const struct device *const i2c_dev, uint16_t slv_addr, uint16_t *value)
{
    return i2c_wreg_read_word(i2c_dev, slv_addr,
            VL53L4CD_RESULT_DISTANCE, value);
}

static
void drv_vl53l4cd_power(const struct gpio_port_pin *xshut, bool on_off)
{
    gpio_pin_set(xshut->port, xshut->pin, on_off ? 1 : 0);
    k_msleep(10);
}

bool drv_init_tof(const struct vl53l4cd_ctx *ctx)
{
    // Setup port-pin
    if (device_is_ready(ctx->xshut.port) == false) {
        printk("%s is not ready\n", ctx->xshut.port->name);
        return false;
    }

    if (ctx->interrupt.port != NULL) {
        if (device_is_ready(ctx->interrupt.port) == false) {
            printk("%s is not ready\n", ctx->interrupt.port->name);
            return false;
        }
    }

    int32_t result;
    result = gpio_pin_configure(ctx->xshut.port, ctx->xshut.pin, GPIO_OUTPUT);
    if (result) {
        printk("%s configure failed\n", ctx->interrupt.port->name);
        return false;
    }

    // Start initial sequence
    drv_vl53l4cd_power(&ctx->xshut, false);
    drv_vl53l4cd_power(&ctx->xshut, true);

    // Change slave address
    if (drv_vl53l4cd_set_address(ctx->i2c, VL53L4CD_DEF_ADDR, ctx->addr)) {
        printk("VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS is failed[%x]\n", ctx->addr);
        return false;
    }

    // Get Sensor ID
    uint16_t val = 0;
    drv_vl53l4cd_get_model_id(ctx->i2c, ctx->addr, &val);
    if (val != VL53L4CD_SENSOR_ID) {
        printk("Sensor ID[%d] is mismatched\n", val);
        return false;
    }

    return true;
}

bool drv_tof_setup(const struct vl53l4cd_ctx *ctx)
{
    if (drv_vl53l4cd_wait_for_init(ctx->i2c, ctx->addr) == false) {
        printk("drv_vl53l4cd_wait_for_init() is timeouted\n");
        return false;
    }

    int32_t result = 0;
    do {
        // Load default configuration
        result |= drv_vl53l4cd_load_defconf(ctx->i2c, ctx->addr);
        if (result) {
            printk("drv_vl53l4cd_load_defconf() failed[%d]\n", result);
            break;
        }

        // Start
        result |= drv_vl53l4cd_start_system(ctx->i2c, ctx->addr);
        if (result) {
            printk("drv_vl53l4cd_start_system() failed[%d]\n", result);
            break;
        }

        bool is_ready = false;
        for (int32_t i = 0; i < 1000; ++i) {
            is_ready = drv_vl53l4cd_check_for_data_ready(ctx->i2c, ctx->addr);
            if (is_ready)
                break;

            k_msleep(1);
        }
        if (is_ready == false) {
            printk("drv_vl53l4cd_check_for_data_ready() not ready\n");
            break;
        }

        result |= drv_vl53l4cd_clear_interrupt(ctx->i2c, ctx->addr);
        if (result) {
            printk("drv_vl53l4cd_clear_interrupt() failed[%d]\n", result);
            break;
        }

        result |= drv_vl53l4cd_stop_ranging(ctx->i2c, ctx->addr);
        if (result) {
            printk("drv_vl53l4cd_stop_ranging() failed[%d]\n", result);
            break;
        }

        result |= drv_vl53l4cd_dev_setting(ctx->i2c, ctx->addr);
        if (result) {
            printk("drv_vl53l4cd_dev_setting() failed[%d]\n", result);
            break;
        }

        // Program the highest possible TimingBudget, without enabling the
        // low power mode. This should give the best accuracy
        if (drv_vl53l4cd_set_range_timing(ctx->i2c, ctx->addr, ctx->timing_budget_ms, ctx->inter_measurement_ms) == false) {
            printk("drv_vl53l4cd_set_range_timing() failed\n");
            break;
        }

    } while (0);

    return result ? false : true;
}

int32_t drv_tof_start(const struct vl53l4cd_ctx *ctx)
{
    return drv_vl53l4cd_start_ranging(ctx->i2c, ctx->addr);
}

int32_t drv_tof_stop(const struct vl53l4cd_ctx *ctx)
{
    return drv_vl53l4cd_stop_ranging(ctx->i2c, ctx->addr);
}

int32_t drv_tof_fetch(const struct vl53l4cd_ctx *ctx, struct sensor_value *data)
{
    if (drv_vl53l4cd_check_for_data_ready(ctx->i2c, ctx->addr) == 0) {
        printk("data is not ready");
        return -1;
    }

    int32_t result;
    uint16_t dist_mm;
    uint16_t sig_rate;

    // (Mandatory) Clear HW interrupt to restart measurements
    result = drv_vl53l4cd_clear_interrupt(ctx->i2c, ctx->addr);
    result |= drv_vl53l4cd_get_distance(ctx->i2c, ctx->addr, &dist_mm);
    result |= drv_vl53l4cd_get_signal_rate(ctx->i2c, ctx->addr, &sig_rate);

    data->val1 = dist_mm;
    data->val2 = sig_rate;

    return result;
}
