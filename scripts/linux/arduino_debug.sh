#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat

adb ${ADB_DEVICE} forward tcp:3333 tcp:3333
adb ${ADB_DEVICE} shell /opt/openocd/bin/arduino-debug.sh

popd > /dev/null
