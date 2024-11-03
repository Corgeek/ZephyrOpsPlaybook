#!/bin/bash

source scripts/west_env.bat

FLASH=FALSE
REBUILD=FALSE
while getopts fr OPT
do
	case $OPT in
		f) FLASH=TRUE;;
		r) REBUILD=TRUE;;
	esac
done

if [ "${REBUILD}" = "TRUE" ]; then
	rm -rf build
fi
west build -b ${BOARD_TYPE}

if [ ${?} = 0 ] && [ "${FLASH}" = "TRUE" ]; then
	west flash
fi
