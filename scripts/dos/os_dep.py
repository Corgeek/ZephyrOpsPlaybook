#!/usr/bin/env python3

from pathlib import Path
import os
import shutil

cross_gdb_path = "${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb.exe"

sdk_base_paths = [
    Path(os.environ.get("HOMEPATH")),
    Path(os.environ.get("PROGRAMFILES"))
]

def gen_env_content(zephyr_root: str, BOARD_TYPE: str, runner_flash: str, runner_debug: str):
    env_content = "\n".join([
        f"set ZEPHYR_ROOT={zephyr_root}",
        f"set BOARD_TYPE={BOARD_TYPE}",
        f"set RUNNER_FLASH={runner_flash}",
        f"set RUNNER_DEBUG={runner_debug}",
        "",
        "call %ZEPHYR_ROOT%\\zephyr\\zephyr-env.cmd",
        "call %ZEPHYR_ROOT%\\.venv\\Scripts\\activate.bat",
        "",
        "if %ERRORLEVEL% neq 0 (",
        "    echo \"Setup Environment variables failed\"",
        "    exit /b 1",
        ")",
    ])

    return env_content

def duplicate_scripts(zephyr_root: str, proj_dir: str, scripts_dir: str) -> None:
    dst_vscode_dir = Path(zephyr_root) / ".vscode"
    dst_vscode_dir.mkdir(parents=True, exist_ok=True)

    src_vscode_dir = Path(proj_dir) / ".vscode"
    for file_name in src_vscode_dir.glob("*.json"):
        shutil.copy(file_name, dst_vscode_dir / file_name.name)

    for script in ["build", "debug", "stop"]:
        shutil.copy(scripts_dir / "dos" / f"{script}.bat", scripts_dir / f"{script}.bat")
