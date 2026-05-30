#!/bin/bash

BOARD_TYPE=teensy40
BOARD_TYPE=teensy41

SCRIPT_PATH=`readlink -f ${0}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`

pushd ${SCRIPT_DIR} > /dev/null
python3 setup.py ${BOARD_TYPE}
popd > /dev/null
