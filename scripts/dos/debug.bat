@echo off

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%..
set PROJ_PATH=%cd%

set SCRIPT_DIR=!SCRIPT_DIR:\=/!
set PROJ_PATH=!PROJ_PATH:\=/!

call scripts/west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

west debugserver

popd
