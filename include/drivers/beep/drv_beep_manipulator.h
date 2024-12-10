/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include <zephyr/drivers/pwm.h>

#define BEEP_MAX_PERIOD     PWM_USEC(3900)
#define BEEP_MIN_PERIOD     PWM_USEC(50)
#define BEEP_PERIOD_STEP    PWM_USEC(50)
#define BEEP_DURATION       K_MSEC(60)

void drv_beep_play(void);
void drv_beep_raise(void);
void drv_beep_lower(void);
bool drv_init_beep(void);

