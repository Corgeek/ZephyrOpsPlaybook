@echo off

set SCRIPT_DIR=%~dp0
pushd %SCRIPT_DIR%..
set PROJ_PATH=%cd%
popd
pushd %PROJ_PATH%

call scripts\west_env.bat
if %ERRORLEVEL% neq 0 exit /b 1

rem set "SCA_OPT=-DZEPHYR_SCA_VARIANT=codechecker -DCODECHECKER_EXPORT=html -DCODECHECKER_PARSE_EXIT_STATUS=y"
set "SCA_OPT=-DZEPHYR_SCA_VARIANT=codechecker -DCODECHECKER_EXPORT=html"
set "SCA_DIR=%PROJ_PATH%\build\sca\codechecker"

if exist "%ZEPHYR_BASE%.codechecker.yml" (
  set "SCA_OPT=%SCA_OPT% -DCODECHECKER_CONFIG_FILE=%ZEPHYR_BASE:\=/%.codechecker.yml -DCODECHECKER_ANALYZE_OPTS=--no-missing-checker-error"
)

@echo on
if "/r" == "%1" (
  west build -p -b %BOARD_TYPE% -- %SCA_OPT%
) else (
  west build -b %BOARD_TYPE% -- %SCA_OPT%
)
@echo off

set RET=%ERRORLEVEL%

if exist "%SCA_DIR%\codechecker.plist" (
  rmdir "%SCA_DIR%\reports" 2>nul
  mklink /J "%SCA_DIR%\reports" "%SCA_DIR%\codechecker.plist" >nul
)

popd
rem exit /b %RET%
