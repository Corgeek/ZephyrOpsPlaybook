/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "global/gbf_sample_database.h"

#define MUTEX_DEFINE()      K_MUTEX_DEFINE(s_sample_mutex)
#define MUTEX_LOCK()        k_mutex_lock(&s_sample_mutex, K_FOREVER)
#define MUTEX_UNLOCK()      k_mutex_unlock(&s_sample_mutex)

MUTEX_DEFINE();

static struct SampleData {
	int32_t value;
} s_sample_data;

void InitSampleDatabase(void)
{
	s_sample_data.value = 0;
}

void SetSampleDatabase(const int32_t value)
{
	MUTEX_LOCK();

	s_sample_data.value = value;

	MUTEX_UNLOCK();
}

void GetSampleDatabase(int32_t *value)
{
	if (value == NULL) {
		printk("%s: invalid arguments", __func__);
		return;
	}

	MUTEX_LOCK();

	*value = s_sample_data.value;

	MUTEX_UNLOCK();
}

