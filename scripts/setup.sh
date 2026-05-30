#!/bin/bash

BOARD_TYPE=stm32h747i_disco/stm32h747xx/m7
BOARD_TYPE=nucleo_g431kb
BOARD_TYPE=nucleo_f030r8
BOARD_TYPE=nucleo_f401re
BOARD_TYPE=nucleo_l552ze_q
BOARD_TYPE=arduino_uno_q

SCRIPT_PATH=`readlink -f ${0}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`

pushd ${SCRIPT_DIR} > /dev/null
python3 setup.py ${BOARD_TYPE}
popd > /dev/null
