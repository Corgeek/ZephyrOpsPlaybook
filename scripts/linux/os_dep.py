#!/usr/bin/env python3

from pathlib import Path
import os
import shutil

def get_cross_gdb_path(sdk_path: Path, use_gnu: bool) -> str:
    if use_gnu:
        return str(sdk_path / "gnu" / "arm-zephyr-eabi" / "bin" / "arm-zephyr-eabi-gdb")
    return str(sdk_path / "arm-zephyr-eabi" / "bin" / "arm-zephyr-eabi-gdb")

def get_codechecker_path(zephyr_root: Path) -> str:
    return str(Path(zephyr_root) / ".venv" / "bin" / "CodeChecker")

sdk_base_paths = [
    Path(os.environ.get("HOME")),
    Path(os.environ.get("HOME")) / ".local",
    Path(os.environ.get("HOME")) / ".local/opt",
    Path(os.environ.get("HOME")) / "bin",
    Path("/opt"),
    Path("/usr/local"),
    Path("/usr"),
]

def gen_env_content(zephyr_root: str, BOARD_TYPE: str, runner_flash: str, runner_debug: str, sdk_path: str, build_opt: str = "", adb_device: str = ""):
    env_content = "\n".join([
        f"ZEPHYR_ROOT={zephyr_root}",
        f"BOARD_TYPE={BOARD_TYPE}",
        f'RUNNER_FLASH="{runner_flash}"',
        f'RUNNER_DEBUG="{runner_debug}"',
        f'BUILD_OPT="{build_opt}"',
        f'ADB_DEVICE="{adb_device}"',
        f'export ZEPHYR_SDK_INSTALL_DIR="{sdk_path}"',
        "",
        "if [ ! -e ${ZEPHYR_ROOT}/zephyr/zephyr-env.sh ]; then",
        "    echo \"zephyr-env.sh is not found\"",
        "    exit 1",
        "fi",
        "source ${ZEPHYR_ROOT}/zephyr/zephyr-env.sh",
        "",
        "if [ -e ${ZEPHYR_ROOT}/.venv/bin/activate ]; then",
        "    source ${ZEPHYR_ROOT}/.venv/bin/activate",
        "fi",
    ])

    return env_content

def duplicate_scripts(zephyr_root: str, proj_dir: str, scripts_dir: str, board_type: str) -> None:
    dst_vscode_dir = Path(zephyr_root) / ".vscode"
    dst_vscode_dir.mkdir(parents=True, exist_ok=True)

    src_vscode_dir = Path(proj_dir) / ".vscode"
    for file_name in src_vscode_dir.glob("*.json"):
        shutil.copy(file_name, dst_vscode_dir / file_name.name)

    linux_dir = scripts_dir / "linux"
    prefix = board_type.replace("/", "_").split("_")[0]
    for cmd in ["build", "flash", "debug", "stop", "analyze"]:
        specific = linux_dir / f"{prefix}_{cmd}.sh"
        src = specific if specific.exists() else linux_dir / f"generic_{cmd}.sh"
        shutil.copy(src, scripts_dir / f"{cmd}.bat")
