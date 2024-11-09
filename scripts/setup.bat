@echo off

set ZEPHYR_ROOT=%HOMEPATH%\zephyrproject
set BOARD_TYPE=rpi_pico
set BOARD_TYPE=nucleo_f401re
set BOARD_TYPE=bbc_microbit

copy /Y scripts\dos\*.bat scripts

setlocal enabledelayedexpansion

(
echo set ZEPHYR_ROOT=%ZEPHYR_ROOT%
echo set BOARD_TYPE=%BOARD_TYPE%
echo call %%ZEPHYR_ROOT%%\zephyr\zephyr-env.cmd
echo call %%ZEPHYR_ROOT%%\.venv\Scripts\activate.bat
echo if %%ERRORLEVEL%% neq 0 ^(
echo     echo ^"Setup Environment variables failed^"
echo     exit /b 1
echo ^)
) > scripts/west_env.bat

set i=0
for /f "delims=" %%A in ('dir /o-n /b %HOMEPATH%\zephyr-sdk-*') do (
    set sdklist[!i!]=%%A
    set /a i+=1
)

(
echo {
echo   ^"ZEPHYRSDK^": ^"${env:HOMEPATH}/!sdklist[0]!^",
echo   ^"CROSS_GDB_PATH^": ^"${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb.exe^"
echo }
) > .vscode\settings.json
