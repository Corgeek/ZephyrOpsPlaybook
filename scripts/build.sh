#!/bin/bash

ZEPHYR_BASE=/opt/zephyr-env/zephyr
#BOARD_TYPE=rpi_pico
BOARD_TYPE=bbc_microbit

if [ -z "${ZEPHYR_BASE}" ]; then
	echo "set \${ZEPHYR_BASE} before exec this script"
	echo "e.g.\$ export ZEPHYR_BASE=/opt/zephyr"
	exit 1
fi

if [ ! -e ${ZEPHYR_BASE}/zephyr-env.sh ]; then
	echo ${ZEPHYR_BASE}/zephyr-env.sh
	echo "zephyr-env.sh is not found"
	exit 1
fi
source ${ZEPHYR_BASE}/zephyr-env.sh

if [ -e .venv/bin/activate ]; then
	source .venv/bin/activate
fi


rm -rf build
west build -b ${BOARD_TYPE}

if [ ${?} = 0 ] && [ ${#} -eq 1 ] && [ ${1} = "-f" ]; then
	west flash
fi

