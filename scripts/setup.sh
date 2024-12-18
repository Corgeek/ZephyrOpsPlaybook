#!/bin/bash

BOARD_TYPE=rpi_pico
BOARD_TYPE=nucleo_f401re
BOARD_TYPE=bbc_microbit
BOARD_TYPE=bbc_microbit_v2

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`
ZEPHYR_ROOT=`readlink -f ..`

cat > scripts/west_env.bat << EOF
ZEPHYR_ROOT=${ZEPHYR_ROOT}
BOARD_TYPE=${BOARD_TYPE}

if [ ! -e \${ZEPHYR_ROOT}/zephyr/zephyr-env.sh ]; then
	echo "zephyr-env.sh is not found"
	exit 1
fi
source \${ZEPHYR_ROOT}/zephyr/zephyr-env.sh

if [ -e \${ZEPHYR_ROOT}/.venv/bin/activate ]; then
	source \${ZEPHYR_ROOT}/.venv/bin/activate
fi
EOF

SDK_LIST=(`ls -r ${HOME} | grep zephyr-sdk-`)
cat > .vscode/settings.json << EOF
{
  "ZEPHYRSDK": "\${env:HOMEPATH}/${SDK_LIST[0]}",
  "PROJ_PATH": "${PROJ_PATH}",
  "CROSS_GDB_PATH": "\${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb"
}
EOF

mkdir -p ${ZEPHYR_ROOT}/.vscode
cp -f ${PROJ_PATH}/.vscode/*.json ${ZEPHYR_ROOT}/.vscode
cp -f scripts/linux/build.sh scripts/build.bat
cp -f scripts/linux/debug.sh scripts/debug.bat

popd > /dev/null
