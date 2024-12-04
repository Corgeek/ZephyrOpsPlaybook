/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#if   defined(CONFIG_BOARD_BBC_MICROBIT)
#include "boards/bbc/microbit/bbc_microbit.h"
#elif defined(CONFIG_BOARD_BBC_MICROBIT_V2)
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"
#elif defined(CONFIG_BOARD_NUCLEO_F401RE)
#include "boards/st/nucleo_f401re.h"
#endif
