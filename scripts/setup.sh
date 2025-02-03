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
RUNNER_FLASH=`python3 opt_gen.py flash ${BOARD_TYPE}`
RUNNER_DEBUG=`python3 opt_gen.py debug ${BOARD_TYPE}`
popd > /dev/null

pushd ${SCRIPT_DIR}/.. > /dev/null
PROJ_PATH=`readlink -f .`
ZEPHYR_ROOT=`readlink -f ..`

cat > scripts/west_env.bat << EOF
ZEPHYR_ROOT=${ZEPHYR_ROOT}
BOARD_TYPE=${BOARD_TYPE}
RUNNER_FLASH="${RUNNER_FLASH}"
RUNNER_DEBUG="${RUNNER_DEBUG}"

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
  "ZEPHYRSDK": "${HOME}/${SDK_LIST[0]}",
  "PROJ_PATH": "${PROJ_PATH}",
  "CROSS_GDB_PATH": "\${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb"
}
EOF

mkdir -p ${ZEPHYR_ROOT}/.vscode
cp -f ${PROJ_PATH}/.vscode/*.json ${ZEPHYR_ROOT}/.vscode
cp -f scripts/linux/build.sh scripts/build.bat
cp -f scripts/linux/debug.sh scripts/debug.bat
cp -f scripts/linux/stop.sh scripts/stop.bat

popd > /dev/null
