/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "vl53l4cd_api.h"

int32_t drv_tof_start_ranging(const struct device *const i2c_dev, uint16_t slv_addr);

int32_t drv_tof_start_system(const struct device *const i2c_dev, uint16_t slv_addr);
int32_t drv_tof_stop_ranging(const struct device *const i2c_dev, uint16_t slv_addr);
bool drv_tof_set_range_timing(const struct device *const i2c_dev, uint16_t slv_addr, uint32_t timing_budget_ms, uint32_t inter_measurement_ms);

int32_t drv_tof_clear_interrupt(const struct device *const i2c_dev, uint16_t slv_addr);
int32_t drv_tof_set_address(const struct device *const i2c_dev, uint16_t cur_addr, uint16_t new_addr);
uint16_t drv_tof_get_model_id(const struct device *const i2c_dev, uint16_t slv_addr);
bool drv_tof_wait_for_init(const struct device *const i2c_dev, uint16_t slv_addr);
uint8_t drv_tof_check_for_data_ready(const struct device *const i2c_dev, uint16_t slv_addr);

int32_t drv_tof_load_defconf(const struct device *const i2c_dev, uint16_t slv_addr);
int32_t drv_tof_dev_setting(const struct device *const i2c_dev, uint16_t slv_addr);
