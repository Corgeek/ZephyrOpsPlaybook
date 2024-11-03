@echo off

call scripts\west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

west debugserver
