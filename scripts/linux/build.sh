#!/bin/bash

source scripts/west_env.bat

FLASH=FALSE
REBUILD=FALSE
if [ "/r" = "${1}" ] || [ "/r" = "${2}" ]; then
	REBUILD=TRUE
fi
if [ "/f" = "${1}" ] || [ "/f" = "${2}" ]; then
	FLASH=TRUE
fi

if [ "${REBUILD}" = "TRUE" ]; then
	rm -rf build
fi
west build -b ${BOARD_TYPE}

if [ ${?} = 0 ] && [ "${FLASH}" = "TRUE" ]; then
	west flash
fi
