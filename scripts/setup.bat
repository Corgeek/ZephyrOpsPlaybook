@echo off

set BOARD_TYPE=nrf54l15dk/nrf54l15/cpuapp
set BOARD_TYPE=bbc_microbit
set BOARD_TYPE=bbc_microbit_v2

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%

python setup.py %BOARD_TYPE%

popd
