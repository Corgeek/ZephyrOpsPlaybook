/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/**
 * @brief Initialize sample database
 */
void init_sample_database(void);

/**
 * @brief Set data to sample database
 */
void set_sample_database(const int32_t value);

/**
 * @brief Get data from sample database
 */
void get_sample_database(int32_t *value);
