#!/bin/bash

source scripts/west_env.bat

FLASH=FALSE
REBUILD=FALSE
while getopts "-:" OPT; do
	case $OPT in
		-)
			case "${OPTARG}" in
				rebuild)	REBUILD=TRUE;;
				flash)		FLASH=TRUE;;
			esac
	esac
done

if [ "${REBUILD}" = "TRUE" ]; then
	rm -rf build
fi
west build -b ${BOARD_TYPE}

if [ ${?} = 0 ] && [ "${FLASH}" = "TRUE" ]; then
	west flash
fi
