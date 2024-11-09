#!/bin/bash

ZEPHYR_ROOT=`readlink -f ..`
BOARD_TYPE=rpi_pico
BOARD_TYPE=nucleo_f401re
BOARD_TYPE=bbc_microbit_v2

cat > scripts/west_env.bat << EOF
ZEPHYR_ROOT=${ZEPHYR_ROOT}
BOARD_TYPE=${BOARD_TYPE}

if [ -z "\${ZEPHYR_ROOT}" ]; then
	echo "set \\\${ZEPHYR_ROOT} before exec this script"
	echo "e.g.\\\$ export ZEPHYR_ROOT=/opt/zephyr"
	exit 1
fi

if [ ! -e \${ZEPHYR_ROOT}/zephyr-env/zephyr/zephyr-env.sh ]; then
	echo \${ZEPHYR_ROOT}/zephyr/zephyr-env.sh
	echo "zephyr-env.sh is not found"
	exit 1
fi
source \${ZEPHYR_ROOT}/zephyr-env/zephyr/zephyr-env.sh

if [ -e \${ZEPHYR_ROOT}/.venv/bin/activate ]; then
	source \${ZEPHYR_ROOT}/.venv/bin/activate
fi
EOF

SDK_LIST=(`ls -r ${HOME} | grep zephyr-sdk-`)
echo "{ \"ZEPHYRSDK\": \"\${env:HOMEPATH}/${SDK_LIST[0]}\" }" > .vscode/settings.json

cat > .vscode/settings.json << EOF
{
  "ZEPHYRSDK": "\${env:HOMEPATH}/${SDK_LIST[0]}",
  "CROSS_GDB_PATH": "\${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb"
}
EOF

cp -f scripts/linux/build.sh scripts/build.bat
cp -f scripts/linux/debug.sh scripts/debug.bat
