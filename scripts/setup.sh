#!/bin/bash

BOARD_TYPE=rpi_pico
BOARD_TYPE=rpi_pico2/rp2350a/m33

SCRIPT_PATH=`readlink -f ${0}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`

pushd ${SCRIPT_DIR} > /dev/null
python3 setup.py ${BOARD_TYPE}
popd > /dev/null
