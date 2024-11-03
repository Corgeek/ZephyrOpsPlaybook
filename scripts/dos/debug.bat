@echo off

set ZEPHYR_ENV=%HOMEPATH%\Projects\zephyr-env

call %ZEPHYR_ENV%\.venv\Scripts\activate.bat
call %ZEPHYR_ENV%\zephyr\zephyr-env.cmd

if %ERRORLEVEL% neq 0 exit

west debugserver
