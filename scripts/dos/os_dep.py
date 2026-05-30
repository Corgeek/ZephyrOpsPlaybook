#!/usr/bin/env python3

from pathlib import Path
import os
import shutil

def get_cross_gdb_path(sdk_path: Path, use_gnu: bool) -> str:
    if use_gnu:
        return str(sdk_path / "gnu" / "arm-zephyr-eabi" / "bin" / "arm-zephyr-eabi-gdb.exe")
    return str(sdk_path / "arm-zephyr-eabi" / "bin" / "arm-zephyr-eabi-gdb.exe")

sdk_base_paths = [
    Path(os.environ.get("HOMEPATH")),
    Path(os.environ.get("PROGRAMFILES")),
    Path(os.environ.get("SYSTEMDRIVE", "C:") + "\\")
]

def gen_env_content(zephyr_root: str, BOARD_TYPE: str, runner_flash: str, runner_debug: str, sdk_path: str, build_opt: str = "", adb_device: str = ""):
    env_content = "\n".join([
        f"set \"ZEPHYR_ROOT={zephyr_root}\"",
        f"set \"BOARD_TYPE={BOARD_TYPE}\"",
        f"set \"RUNNER_FLASH={runner_flash}\"",
        f"set \"RUNNER_DEBUG={runner_debug}\"",
        f"set \"BUILD_OPT={build_opt}\"",
        f"set \"ADB_DEVICE={adb_device}\"",
        f"set \"ZEPHYR_SDK_INSTALL_DIR={sdk_path}\"",
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

def duplicate_scripts(zephyr_root: str, proj_dir: str, scripts_dir: str, board_type: str) -> None:
    dst_vscode_dir = Path(zephyr_root) / ".vscode"
    dst_vscode_dir.mkdir(parents=True, exist_ok=True)

    src_vscode_dir = Path(proj_dir) / ".vscode"
    for file_name in src_vscode_dir.glob("*.json"):
        shutil.copy(file_name, dst_vscode_dir / file_name.name)

    dos_dir = scripts_dir / "dos"
    prefix = board_type.replace("/", "_").split("_")[0]
    for cmd in ["build", "flash", "debug", "stop"]:
        specific = dos_dir / f"{prefix}_{cmd}.bat"
        src = specific if specific.exists() else dos_dir / f"generic_{cmd}.bat"
        shutil.copy(src, scripts_dir / f"{cmd}.bat")
