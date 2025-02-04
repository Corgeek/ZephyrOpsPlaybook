@echo off

set BOARD_TYPE=rpi_pico
set BOARD_TYPE=rpi_pico2/rp2350a/m33
set BOARD_TYPE=nucleo_f030r8
set BOARD_TYPE=nucleo_f401re
set BOARD_TYPE=nucleo_l552ze_q
set BOARD_TYPE=bbc_microbit
set BOARD_TYPE=bbc_microbit_v2

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%

python setup.py %BOARD_TYPE%

popd
