@echo off

set BOARD_TYPE=teensy40
set BOARD_TYPE=teensy41

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%

python setup.py %BOARD_TYPE%

popd
