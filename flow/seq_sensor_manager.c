/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include "boards/unique.h"
#include "global/gbf_sensor_database.h"
#include "flow/seq_sensor_manager.h"
#include "drivers/sensor/accel/drv_accel_lis2dh.h"
#include "drivers/sensor/measure/drv_tof_vl53l4cd.h"

enum TOF_DEV_ID {
    TOF_ID_1ST,

    TOF_ID_MAX
};

#if defined(CONFIG_ACCEL_SENSOR)
static struct accel_ctx s_accel_ctx = {
    .state = STS_SENSOR_INIT,
    .dev = DEVICE_DT_GET(DT_NODELABEL(lsm303agr_accel)),
    .period_ms = SENSOR_ACCEL_PERIOD_MS,
};
#endif // CONFIG_ACCEL_SENSOR

#if defined(CONFIG_MAGNET_SENSOR)
static struct magnet_ctx s_magnet_ctx = {
    .state = STS_SENSOR_INIT,
    .dev = DEVICE_DT_GET(DT_ALIAS(magn0)),
    .period_ms = SENSOR_MAGNET_PERIOD_MS,
};
#endif // CONFIG_MAGNET_SENSOR

#if defined(CONFIG_MEASURE_SENSOR)
static struct vl53l4cd_ctx s_tof_ctx[TOF_ID_MAX] = {
    [TOF_ID_1ST] = {
        .state = STS_SENSOR_INIT,
        .i2c = I2C_100KHZ_BUS,
        .xshut = TOF_XSHUT,
        .interrupt = GPIO_DUMMY,
        .addr = VL53L4CD_DEF_ADDR,
        .timing_budget_ms = TOF_TIMING_BUDGET_MS,
        .inter_measurement_ms = 0,
    },
};
#endif // CONFIG_MEASURE_SENSOR

static
void seq_sensor_accel(void)
{
#if defined(CONFIG_ACCEL_SENSOR)
    struct sensor_3d value;

    switch (s_accel_ctx.state) {
    case STS_SENSOR_INIT:
        if (drv_init_accel(&s_accel_ctx))
            s_accel_ctx.state = STS_SENSOR_SETUP;
        break;

    case STS_SENSOR_SETUP:
        if (drv_accel_setup(&s_accel_ctx))
            s_accel_ctx.state = STS_SENSOR_READY;
        break;

    case STS_SENSOR_READY:
        if (drv_accel_start(&s_accel_ctx) == 0)
            s_accel_ctx.state = STS_SENSOR_ACTIVE;
        break;

    case STS_SENSOR_ACTIVE:
        drv_accel_fetch(&s_accel_ctx, &value);
        gbf_set_accel(&value);
        break;

    case STS_SENSOR_FATAL:
    default:
        break;
    }
#endif // CONFIG_ACCEL_SENSOR
}

static
void seq_sensor_magnet(void)
{
#if defined(CONFIG_MAGNET_SENSOR)
    struct sensor_3d value;

    switch (s_magnet_ctx.state) {
    case STS_SENSOR_INIT:
        if (drv_init_magnet(&s_magnet_ctx))
            s_magnet_ctx.state = STS_SENSOR_SETUP;
        break;

    case STS_SENSOR_SETUP:
        if (drv_magnet_setup(&s_magnet_ctx))
            s_magnet_ctx.state = STS_SENSOR_READY;
        break;

    case STS_SENSOR_READY:
        if (drv_magnet_start(&s_magnet_ctx) == 0)
            s_magnet_ctx.state = STS_SENSOR_ACTIVE;
        break;

    case STS_SENSOR_ACTIVE:
        drv_magnet_fetch(&s_magnet_ctx, &value);
        gbf_set_magnet(&value);
        break;

    case STS_SENSOR_FATAL:
    default:
        break;
    }
#endif // CONFIG_MAGNET_SENSOR
}

static
void seq_sensor_measure(void)
{
#if defined(CONFIG_MEASURE_SENSOR)
    for (int32_t i = 0; i < TOF_ID_MAX; ++i) {
        struct sensor_value value;

        switch (s_tof_ctx[i].state) {
        case STS_SENSOR_INIT:
            if (drv_init_tof(&s_tof_ctx[i]))
                s_tof_ctx[i].state = STS_SENSOR_SETUP;
            break;

        case STS_SENSOR_SETUP:
            if (drv_tof_setup(&s_tof_ctx[i]))
                s_tof_ctx[i].state = STS_SENSOR_READY;
            break;

        case STS_SENSOR_READY:
            if (drv_tof_start(&s_tof_ctx[i]) == 0)
                s_tof_ctx[i].state = STS_SENSOR_ACTIVE;
            break;

        case STS_SENSOR_ACTIVE:
            drv_tof_fetch(&s_tof_ctx[i], &value);
            gbf_set_measure((uint16_t)(value.val1));
            break;

        case STS_SENSOR_FATAL:
        default:
            break;
        }
    }
#endif // CONFIG_MEASURE_SENSOR
}

void seq_sensor_manager(void)
{
    seq_sensor_accel();
    seq_sensor_magnet();
    seq_sensor_measure();
}
