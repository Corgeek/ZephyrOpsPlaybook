/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

/**
 * @brief sub command: Log enable
 */
static
int sub_log_enable(const struct shell *shell, size_t argc, char *argv[])
{
    printk("%s\n", __func__);
	return 0;
}

/**
 * @brief sub command: Log disable
 */
static
int sub_log_disable(const struct shell *shell, size_t argc, char *argv[])
{
    printk("%s\n", __func__);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(log_sub_array,
	SHELL_CMD_ARG(enable,	NULL, "", sub_log_enable, 1, 1),
	SHELL_CMD_ARG(disable,	NULL, "", sub_log_disable, 1, 1),
	SHELL_SUBCMD_SET_END
);

/**
 * @brief log command
 */
static
int hndl_log_operator(const struct shell *shell, size_t argc, char **argv)
{
	shell_error(shell, "%s:unknown parameter: %s", argv[0], argv[1]);
	return -EINVAL;
}

SHELL_CMD_ARG_REGISTER(log, &log_sub_array, "Log operator", hndl_log_operator, 2, 0);
