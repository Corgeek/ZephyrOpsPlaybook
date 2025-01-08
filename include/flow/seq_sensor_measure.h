/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "boards/unique.h"

enum SEQ_SENSOR_STATE {
    SEQ_SENSOR_INIT,
    SEQ_SENSOR_SETUP,
    SEQ_SENSOR_READY,
    SEQ_SENSOR_ACTIVE,

    SEQ_SENSOR_FATAL,

    SEQ_SENSOR_MAX
};

void seq_sensor_manager(void);
