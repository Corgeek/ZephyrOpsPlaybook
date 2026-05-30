#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat

if [ "/r" = "${1}" ]; then
	west build -p -b ${BOARD_TYPE}
else
	west build -b ${BOARD_TYPE}
fi

popd > /dev/null
