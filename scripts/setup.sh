#!/bin/bash

BOARD_TYPE=nrf54l15dk/nrf54l15/cpuapp
BOARD_TYPE=bbc_microbit
BOARD_TYPE=bbc_microbit_v2

SCRIPT_PATH=`readlink -f ${0}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`

pushd ${SCRIPT_DIR} > /dev/null
python3 setup.py ${BOARD_TYPE}
popd > /dev/null
