/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include "drivers/beep/drv_beep_manipulator.h"

struct beep_context {
    struct k_work work;
    k_timeout_t duration;
    uint32_t max_period;
    uint32_t min_period;
    uint32_t period;
    bool is_active;
};

static struct beep_context s_beep_context;
static const struct pwm_dt_spec s_beep_spec = PWM_DT_SPEC_GET(DT_PATH(zephyr_user));

static
void drv_beep_callback(struct k_work *)
{
    pwm_set_dt(&s_beep_spec, s_beep_context.period, s_beep_context.period / 2U);
    k_sleep(s_beep_context.duration);

    pwm_set_pulse_dt(&s_beep_spec, 0);
    k_sleep(s_beep_context.duration);

    s_beep_context.is_active = false;
}

void drv_beep_play(void)
{
    s_beep_context.is_active = true;
    k_work_submit(&s_beep_context.work);
}

void drv_beep_raise(void)
{
    s_beep_context.period -= BEEP_PERIOD_STEP;
    if (s_beep_context.period < s_beep_context.min_period)
        s_beep_context.period = s_beep_context.min_period;
}

void drv_beep_lower(void)
{
    s_beep_context.period += BEEP_PERIOD_STEP;
    if (s_beep_context.max_period < s_beep_context.period)
        s_beep_context.period = s_beep_context.max_period;
}

bool drv_init_beep(void)
{
    if (pwm_is_ready_dt(&s_beep_spec) == false) {
        printk("%s is not ready\n", s_beep_spec.dev->name);
        return false;
    }

    s_beep_context.duration = BEEP_DURATION;
    s_beep_context.max_period = BEEP_MAX_PERIOD;
    s_beep_context.min_period = BEEP_MIN_PERIOD;
    s_beep_context.period = s_beep_spec.period;
    s_beep_context.is_active = false;

    k_work_init(&s_beep_context.work, drv_beep_callback);
    k_work_submit(&s_beep_context.work);

	return true;
}
