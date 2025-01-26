/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "boards/unique.h"

#ifdef  __cplusplus
extern "C" {
#endif

enum SEQ_SENSOR_STATE {
    STS_SENSOR_INIT,
    STS_SENSOR_SETUP,
    STS_SENSOR_READY,
    STS_SENSOR_ACTIVE,

    STS_SENSOR_FATAL,

    STS_SENSOR_MAX
};

void seq_sensor_manager(void);

#ifdef  __cplusplus
}
#endif

