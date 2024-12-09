/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <assert.h>
#include "global/gbf_sensor_database.h"

#define MUTEX_DEFINE()      K_MUTEX_DEFINE(s_sensor_mutex)
#define MUTEX_LOCK()        k_mutex_lock(&s_sensor_mutex, K_FOREVER)
#define MUTEX_UNLOCK()      k_mutex_unlock(&s_sensor_mutex)

MUTEX_DEFINE();

static struct SampleData {
	struct sensor_3d accel;
	struct sensor_3d magnet;
} s_sensor_data;

void gbf_init_sensor(void)
{
	memset(&s_sensor_data, 0, sizeof(s_sensor_data));
}

void gbf_set_sensor(enum SENSOR_DATA_TYPE type, struct sensor_3d *const data)
{
	assert(data);

	MUTEX_LOCK();

	switch (type) {
		case SENSOR_ACCEL:	memcpy(&s_sensor_data.accel,  data, sizeof(s_sensor_data.accel));	break;
		case SENSOR_MAGNET:	memcpy(&s_sensor_data.magnet, data, sizeof(s_sensor_data.magnet));	break;
		default:	break;
	}

	MUTEX_UNLOCK();
}

void gbf_get_sensor(enum SENSOR_DATA_TYPE type, struct sensor_3d *data)
{
	assert(data);

	MUTEX_LOCK();

	switch (type) {
		case SENSOR_ACCEL:	memcpy(data, &s_sensor_data.accel,  sizeof(s_sensor_data.accel));	break;
		case SENSOR_MAGNET:	memcpy(data, &s_sensor_data.magnet, sizeof(s_sensor_data.magnet));	break;
		default:	break;
	}

	MUTEX_UNLOCK();
}
