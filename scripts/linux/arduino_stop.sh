#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat

adb ${ADB_DEVICE} shell pkill openocd
adb ${ADB_DEVICE} forward --remove tcp:3333

