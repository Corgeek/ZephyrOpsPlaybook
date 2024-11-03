@echo off
copy /Y scripts\dos\*.bat scripts

setlocal enabledelayedexpansion

set i=0
for /f "delims=" %%A in ('dir /o-n /b %HOMEPATH%\zephyr-sdk-*') do (
    set sdklist[!i!]=%%A
    set /a i+=1
)

echo { "ZEPHYRSDK": "${env:HOMEPATH}/!sdklist[0]!" } > .vscode\settings.json
