#!/bin/bash

SCRIPT_PATH=`readlink -f ${0}`
pushd `dirname ${SCRIPT_PATH}`/.. > /dev/null
PROJ_PATH=`readlink -f .`

source scripts/west_env.bat
west debugserver ${RUNNER_DEBUG}

popd > /dev/null
