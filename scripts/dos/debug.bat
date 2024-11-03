@echo off

set ZEPHYR_ROOT=%HOMEPATH%\Projects\zephyr-env

call %ZEPHYR_ROOT%\.venv\Scripts\activate.bat
call %ZEPHYR_ROOT%\zephyr\zephyr-env.cmd

if %ERRORLEVEL% neq 0 exit

west debugserver
