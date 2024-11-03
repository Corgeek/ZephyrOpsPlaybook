@echo off

set ZEPHYR_PATH=%HOMEPATH%\Projects\zephyr-env

set BOARD_TYPE=rpi_pico
set BOARD_TYPE=bbc_microbit

set REBUILD=FALSE
set FLASH=FALSE
if "/r" == "%1" set REBUILD=TRUE
if "/r" == "%2" set REBUILD=TRUE
if "/f" == "%1" set FLASH=TRUE
if "/f" == "%2" set FLASH=TRUE

call %ZEPHYR_PATH%\.venv\Scripts\activate.bat
call %ZEPHYR_PATH%\zephyr\zephyr-env.cmd

if "%REBUILD%" == "TRUE" (
  rmdir /S /Q build
)

@echo on
west build -b %BOARD_TYPE%
@echo off

if %ERRORLEVEL% neq 0 exit

if "%FLASH%" == "TRUE" (
@echo on
  west flash
)
