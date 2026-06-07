@echo off

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%..
set PROJ_PATH=%cd%
popd
pushd %PROJ_PATH%

set SCRIPT_DIR=!SCRIPT_DIR:\=/!
set PROJ_PATH=!PROJ_PATH:\=/!

call scripts\west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

@echo on
adb %ADB_DEVICE% push build/zephyr/zephyr.bin /tmp
adb %ADB_DEVICE% push build/zephyr/zephyr.elf /tmp
adb %ADB_DEVICE% shell /opt/openocd/bin/arduino-flash.sh /tmp/zephyr.elf /tmp/zephyr.bin
@echo off

popd
