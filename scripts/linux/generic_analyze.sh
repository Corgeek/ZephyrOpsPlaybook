#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat

SCA_OPT="-DZEPHYR_SCA_VARIANT=codechecker -DCODECHECKER_EXPORT=html"
SCA_DIR=build/sca/codechecker

if [ "/r" = "${1}" ]; then
	west build -p -b ${BOARD_TYPE} -- ${SCA_OPT}
else
	west build -b ${BOARD_TYPE} -- ${SCA_OPT}
fi
RET=$?

if [ 0 -eq ${RET} ] && [ -d ${SCA_DIR}/codechecker.plist ]; then
	ln -sfn codechecker.plist ${SCA_DIR}/reports
fi

popd > /dev/null
exit ${RET}
