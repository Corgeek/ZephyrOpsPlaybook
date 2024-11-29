/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <stdlib.h>
#include "global/gbf_sensor_database.h"
#include "drivers/led/display/drv_disp_microbit.h"
#include "drivers/sensor/accel/drv_accel_lis2dh.h"
#include "drivers/sensor/magnet/drv_magn_lis2mdl.h"

/**
 * @brief sub command: exec print display
 */
static
int exec_print_display(const struct shell *shell, size_t argc, char *argv[])
{
    int32_t duration = 250;

    if (argc == 3) {
        errno = 0;
        duration = strtol(argv[2], NULL, 10);
        if (errno == EINVAL) {
            printk("e.g.: exec print \"hello world\", 250\n");
            return EINVAL;
        }
    }
#if defined(CONFIG_BOARD_BBC_MICROBIT) || defined(CONFIG_BOARD_BBC_MICROBIT_V2)
  	drv_disp_print(MB_DISPLAY_MODE_SINGLE, duration, argv[1]);
#endif
    return 0;
}

/**
 * @brief sub command: exec acceleration sensor
 */
static
int exec_accel_sensor(const struct shell *shell, size_t argc, char *argv[])
{
    struct sensor_3axis accel;
    int ret;

    for (int i = 0; i < 3; ++i) {
        ret = get_accel_xyz(&accel);
        if (ret != 0) {
            return ret;
        }
        printk("accel [m/s^2]:    (%6d.%6d, %6d.%6d, %6d.%6d)\n",
            accel.x.val1, accel.x.val2, accel.y.val1, accel.y.val2, accel.z.val1, accel.z.val2);

        k_msleep(1000 / SENSOR_ACCEL_FREQ_HZ);
    }

    return 0;
}


/**
 * @brief sub command: exec magnetic sensor
 */
static
int exec_magnet_sensor(const struct shell *shell, size_t argc, char *argv[])
{
    struct sensor_3axis magnet;
    int ret;

    for (int i = 0; i < 3; ++i) {
        ret = get_magnet_xyz(&magnet);
        if (ret != 0) {
            return ret;
        }
        printk("magnet:    (%6d.%6d, %6d.%6d, %6d.%6d)\n",
            magnet.x.val1, magnet.x.val2, magnet.y.val1, magnet.y.val2, magnet.z.val1, magnet.z.val2);

        k_msleep(1000 / SENSOR_MAGNET_FREQ_HZ);
    }

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(s_exec_sub_array,
	SHELL_CMD_ARG(print,    NULL, "e.g.: exec print \"hello world\", 250", exec_print_display, 2, 1),
	SHELL_CMD_ARG(accel,    NULL, "e.g.: exec accel", exec_accel_sensor, 1, 0),
	SHELL_CMD_ARG(magnet,   NULL, "e.g.: exec accel", exec_magnet_sensor, 1, 0),
	SHELL_SUBCMD_SET_END
);

/**
 * @brief log command
 */
static
int hndl_exec_drivers(const struct shell *shell, size_t argc, char **argv)
{
	shell_error(shell, "%s:unknown parameter: %s", argv[0], argv[1]);
	return -EINVAL;
}

SHELL_CMD_ARG_REGISTER(exec, &s_exec_sub_array, "Driver executer", hndl_exec_drivers, 2, 1);
