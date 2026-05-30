@echo off

set BOARD_TYPE=stm32h747i_disco/stm32h747xx/m7
set BOARD_TYPE=nucleo_g431kb
set BOARD_TYPE=nucleo_f030r8
set BOARD_TYPE=nucleo_f401re
set BOARD_TYPE=nucleo_l552ze_q
set BOARD_TYPE=arduino_uno_q

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%

python setup.py %BOARD_TYPE%

popd
