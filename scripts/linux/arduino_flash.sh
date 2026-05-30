#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat

adb ${ADB_DEVICE} push build/zephyr/zephyr.bin /tmp
adb ${ADB_DEVICE} shell /opt/openocd/bin/arduino-flash.sh /tmp/zephyr.bin

popd > /dev/null
