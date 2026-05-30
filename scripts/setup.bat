@echo off

set BOARD_TYPE=rpi_pico
set BOARD_TYPE=rpi_pico2/rp2350a/m33

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%

python setup.py %BOARD_TYPE%

popd
