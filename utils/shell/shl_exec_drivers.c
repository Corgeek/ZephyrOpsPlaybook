/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <stdlib.h>
#include "global/gbf_sensor_database.h"
#include "boards/unique.h"

/**
 * @brief sub command: exec print display
 */
static
int exec_print_display(const struct shell *shell, size_t argc, char *argv[])
{
    int32_t duration = 250;

    if (argc == 3) {
        errno = 0;
        duration = strtol(argv[argc - 1], NULL, 10);
        if (errno == EINVAL) {
            printk("e.g.: exec print \"hello world\", 250\n");
            return EINVAL;
        }
    }
#if defined(CONFIG_MICROBIT_DISPLAY)
  	drv_disp_print(MB_DISPLAY_MODE_SINGLE, duration, argv[1]);
#endif
    return 0;
}

/**
 * @brief sub command: exec acceleration sensor
 */
static
int exec_beep_play(const struct shell *shell, size_t argc, char *argv[])
{
#if defined (CONFIG_BOARD_BBC_MICROBIT) || defined (CONFIG_BOARD_BBC_MICROBIT_V2)
    if (strcmp("play", argv[1]) == 0) {
        drv_beep_play();
    } else if (strcmp("raise", argv[1]) == 0) {
        drv_beep_raise();
    } else if (strcmp("lower", argv[1]) == 0) {
        drv_beep_lower();
    }
#endif
    return 0;
}

/**
 * @brief sub command: exec acceleration sensor
 */
static
int exec_accel_sensor(const struct shell *shell, size_t argc, char *argv[])
{
#ifdef CONFIG_LIS2DH
    int32_t count = 3;

    if (argc == 2) {
        errno = 0;
        count = strtol(argv[argc - 1], NULL, 10);
        if (errno == EINVAL) {
            printk("e.g.: exec accel 5\n");
            return EINVAL;
        }
    }

    struct sensor_3d accel;
    int ret;
    for (int i = 0; i < count; ++i) {
        ret = get_accel_xyz(&accel);
        if (ret != 0) {
            return ret;
        }
        printk("accel:    (%6d.%6d, %6d.%6d, %6d.%6d)\n",
            accel.x.val1, accel.x.val2, accel.y.val1, accel.y.val2, accel.z.val1, accel.z.val2);

        k_msleep(1000 / SENSOR_ACCEL_FREQ_HZ);
    }
#endif // CONFIG_LIS2DH
    return 0;
}

/**
 * @brief sub command: exec magnetic sensor
 */
static
int exec_magnet_sensor(const struct shell *shell, size_t argc, char *argv[])
{
#ifdef CONFIG_LIS2MDL
    int32_t count = 3;

    if (argc == 2) {
        errno = 0;
        count = strtol(argv[argc - 1], NULL, 10);
        if (errno == EINVAL) {
            printk("e.g.: exec magnet 5\n");
            return EINVAL;
        }
    }

    struct sensor_3d magnet;
    int ret;

    for (int i = 0; i < count; ++i) {
        ret = get_magnet_xyz(&magnet);
        if (ret != 0) {
            return ret;
        }
        printk("magnet:    (%6d.%6d, %6d.%6d, %6d.%6d)\n",
            magnet.x.val1, magnet.x.val2, magnet.y.val1, magnet.y.val2, magnet.z.val1, magnet.z.val2);

        k_msleep(1000 / SENSOR_MAGNET_FREQ_HZ);
    }
#endif // CONFIG_LIS2MDL
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(s_exec_sub_array,
	SHELL_CMD_ARG(print,    NULL, "exec print text [duration]", exec_print_display, 2, 1),
	SHELL_CMD_ARG(beep,     NULL, "exec beep play/stop/raise/lower", exec_beep_play, 2, 0),
	SHELL_CMD_ARG(accel,    NULL, "exec accel [loop_times]", exec_accel_sensor, 1, 1),
	SHELL_CMD_ARG(magnet,   NULL, "exec magnet [loop_times]", exec_magnet_sensor, 1, 1),
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
