#!/bin/bash

BOARD_TYPE=rpi_pico
BOARD_TYPE=rpi_pico2/rp2350a/m33
BOARD_TYPE=nucleo_f030r8
BOARD_TYPE=nucleo_f401re
BOARD_TYPE=nucleo_l552ze_q
BOARD_TYPE=bbc_microbit
BOARD_TYPE=bbc_microbit_v2

SCRIPT_PATH=`readlink -f ${0}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`

pushd ${SCRIPT_DIR} > /dev/null
python3 setup.py ${BOARD_TYPE}
popd > /dev/null
