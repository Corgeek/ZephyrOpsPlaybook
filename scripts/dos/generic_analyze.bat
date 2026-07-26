@echo off

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%..
set PROJ_PATH=%cd%
popd
pushd %PROJ_PATH%

call scripts\west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

set "SCA_OPT=-DZEPHYR_SCA_VARIANT=codechecker -DCODECHECKER_EXPORT=html"
set "SCA_DIR=%PROJ_PATH%\build\sca\codechecker"

@echo on
if "/r" == "%1" (
  west build -p -b %BOARD_TYPE% -- %SCA_OPT%
) else (
  west build -b %BOARD_TYPE% -- %SCA_OPT%
)
@echo off

if %ERRORLEVEL% neq 0 (
  popd
  exit /b 1
)

if exist "%SCA_DIR%\codechecker.plist" (
  rmdir "%SCA_DIR%\reports" 2>nul
  mklink /J "%SCA_DIR%\reports" "%SCA_DIR%\codechecker.plist" >nul
)

popd
