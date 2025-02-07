#!/usr/bin/env python3

from pathlib import Path
import os
import shutil

cross_gdb_path = "${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb"

sdk_base_paths = [
    Path(os.environ.get("HOME")),
    Path(os.environ.get("HOME")) / ".local",
    Path(os.environ.get("HOME")) / ".local/opt",
    Path(os.environ.get("HOME")) / "bin",
    Path("/opt"),
    Path("/usr/local"),
]

def gen_env_content(zephyr_root: str, BOARD_TYPE: str, runner_flash: str, runner_debug: str, sdk_path: str):
    env_content = "\n".join([
        f"ZEPHYR_ROOT={zephyr_root}",
        f"BOARD_TYPE={BOARD_TYPE}",
        f'RUNNER_FLASH="{runner_flash}"',
        f'RUNNER_DEBUG="{runner_debug}"',
        f'export ZEPHYR_SDK_INSTALL_DIR="{sdk_path}"'
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

def duplicate_scripts(zephyr_root: str, proj_dir: str, scripts_dir: str) -> None:
    dst_vscode_dir = Path(zephyr_root) / ".vscode"
    dst_vscode_dir.mkdir(parents=True, exist_ok=True)

    src_vscode_dir = Path(proj_dir) / ".vscode"
    for file_name in src_vscode_dir.glob("*.json"):
        shutil.copy(file_name, dst_vscode_dir / file_name.name)

    for script in ["build", "debug", "stop"]:
        shutil.copy(scripts_dir / "linux" / f"{script}.sh", scripts_dir / f"{script}.bat")
