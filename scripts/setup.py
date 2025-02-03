#!/usr/bin/env python3

import os
import shutil
import json
from pathlib import Path
import re

from support import runner

BOARD_TYPE = "rpi_pico"
BOARD_TYPE = "rpi_pico2/rp2350a/m33"
BOARD_TYPE = "nucleo_f030r8"
BOARD_TYPE = "nucleo_f401re"
BOARD_TYPE = "nucleo_l552ze_q"
BOARD_TYPE = "bbc_microbit"
BOARD_TYPE = "bbc_microbit_v2"

def setup_env() -> tuple[str, str, str]:
    scripts_dir = Path(__file__).resolve().parent
    proj_dir = scripts_dir.parent
    zephyr_root = proj_dir.parent

    runner_flash = runner.get_runner(cmd_type="flash", board_type=BOARD_TYPE)
    runner_debug = runner.get_runner(cmd_type="debug", board_type=BOARD_TYPE)

    west_env_path = scripts_dir / "west_env.bat"

    env_content = "\n".join([
        f"ZEPHYR_ROOT={zephyr_root}",
        f"BOARD_TYPE={BOARD_TYPE}",
        f'RUNNER_FLASH="{runner_flash}"',
        f'RUNNER_DEBUG="{runner_debug}"',
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

    west_env_path.write_text(env_content, encoding="utf-8")

    return zephyr_root, proj_dir, scripts_dir

def update_settings(proj_dir: str) -> None:
    sdk_base_paths = [
        Path(os.environ["HOME"]),
        Path(os.environ["HOME"]) / ".local",
        Path(os.environ["HOME"]) / ".local/opt",
        Path(os.environ["HOME"]) / "bin",
        Path("/opt"),
        Path("/usr/local"),
    ]

    found_sdks = {}
    sdk_pattern = re.compile(r"zephyr-sdk-(\d+\.\d+\.\d+)")

    for base_path in sdk_base_paths:
        if base_path.exists():
            for item in base_path.iterdir():
                if sdk_pattern.match(item.name):
                    if item.name not in found_sdks:
                        found_sdks[item.name] = item

    sorted_sdks = sorted(
        found_sdks.items(), 
        key=lambda x: list(map(int, x[0].replace("zephyr-sdk-", "").split('.'))), 
        reverse=True
    )

    if not sorted_sdks:
        raise FileNotFoundError("No Zephyr SDK found in specified directories.")

    print("Installed SDK:")
    for sdk_path in sorted_sdks:
        print("\t" + str(sdk_path[0]) + " : " + str(sdk_path[1]))
    print("USE:\r\n\t" + str(sorted_sdks[0][1]))

    selected_sdk = sorted_sdks[0][1]

    vscode_dir = Path(proj_dir) / ".vscode"
    settings_file = vscode_dir / "settings.json"

    if settings_file.exists():
        with settings_file.open("r", encoding="utf-8") as file:
            try:
                settings_json = json.load(file)
            except json.JSONDecodeError:
                settings_json = {}
    else:
        settings_json = {}

    insert_settings = {
        "ZEPHYRSDK": str(selected_sdk),
        "PROJ_PATH": str(proj_dir),
        "CROSS_GDB_PATH": "${config:ZEPHYRSDK}/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb",
    }

    merged_settings = {**settings_json, **insert_settings}

    vscode_dir.mkdir(parents=True, exist_ok=True)
    with settings_file.open("w", encoding="utf-8") as file:
        json.dump(merged_settings, file, indent=2, ensure_ascii=False)

def duplicate_to_root(zephyr_root: str, proj_dir: str, scripts_dir: str) -> None:
    dst_vscode_dir = Path(zephyr_root) / ".vscode"
    dst_vscode_dir.mkdir(parents=True, exist_ok=True)

    src_vscode_dir = Path(proj_dir) / ".vscode"
    for file_name in src_vscode_dir.glob("*.json"):
        shutil.copy(file_name, dst_vscode_dir / file_name.name)

    for script in ["build", "debug", "stop"]:
        shutil.copy(scripts_dir / "linux" / f"{script}.sh", scripts_dir / f"{script}.bat")

if __name__ == "__main__":
    print ("BOARD_TYPE:\r\n\t" + str(BOARD_TYPE) + "\r\n")
    zephyr_root, proj_dir, scripts_dir = setup_env()
    update_settings(proj_dir=proj_dir)
    duplicate_to_root(zephyr_root=zephyr_root, proj_dir=proj_dir, scripts_dir=scripts_dir)
