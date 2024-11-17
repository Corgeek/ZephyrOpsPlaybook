@echo off

setlocal enabledelayedexpansion

set BOARD_TYPE=rpi_pico
set BOARD_TYPE=nucleo_f401re
set BOARD_TYPE=bbc_microbit_v2

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%..
set PROJ_PATH=%cd%
pushd ..
set ZEPHYR_ROOT=%cd%
popd

set "ZEPHYR_ROOT=!ZEPHYR_ROOT:\=/!"
set "SCRIPT_DIR=!SCRIPT_DIR:\=/!"
set "PROJ_PATH=!PROJ_PATH:\=/!"

(
echo set ZEPHYR_ROOT=%ZEPHYR_ROOT%
echo set BOARD_TYPE=%BOARD_TYPE%
echo call %%ZEPHYR_ROOT%%/zephyr/zephyr-env.cmd
echo call %%ZEPHYR_ROOT%%/.venv/Scripts/activate.bat
echo if %%ERRORLEVEL%% neq 0 ^(
echo     echo ^"Setup Environment variables failed^"
echo     exit /b 1
echo ^)
) > scripts\west_env.bat

set i=0
for /f "delims=" %%A in ('dir /o-n /b %HOMEPATH%\zephyr-sdk-*') do (
    set sdklist[!i!]=%%A
    set /a i+=1
)

(
echo {
echo   ^"ZEPHYRSDK^": ^"${env:HOMEPATH}/!sdklist[0]!^",
echo   ^"PROJ_PATH^": ^"%PROJ_PATH%^",
echo   ^"CROSS_GDB_PATH^": ^"${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb.exe^"
echo }
) > .vscode\settings.json

md ..\.vscode > NUL 2>&1
copy /Y .vscode\*.json ..\.vscode
copy /Y scripts\dos\*.bat scripts

popd
