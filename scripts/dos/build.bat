@echo off

call scripts\west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

set REBUILD=FALSE
set FLASH=FALSE
if "-r" == "%1" set REBUILD=TRUE
if "-r" == "%2" set REBUILD=TRUE
if "-f" == "%1" set FLASH=TRUE
if "-f" == "%2" set FLASH=TRUE

if "%REBUILD%" == "TRUE" (
  rmdir /S /Q build
)

@echo on
west build -b %BOARD_TYPE%
@echo off

if %ERRORLEVEL% neq 0 exit /b 1

if "%FLASH%" == "TRUE" (
@echo on
  west flash
)
