#!/usr/bin/env python3

import sys
import platform
import json
from pathlib import Path
import re

from support import runner
if platform.system() == "Windows":
    from dos import os_dep
else:
    from linux import os_dep

BOARD_TYPE = ""

def setup_env() -> tuple[str, str, str]:
    scripts_dir = Path(__file__).resolve().parent
    proj_dir = scripts_dir.parent
    zephyr_root = proj_dir.parent

    runner_flash = runner.get_runner(cmd_type="flash", board_type=BOARD_TYPE)
    runner_debug = runner.get_runner(cmd_type="debug", board_type=BOARD_TYPE)

    west_env_path = scripts_dir / "west_env.bat"

    env_content = os_dep.gen_env_content(zephyr_root=zephyr_root,
                               BOARD_TYPE=BOARD_TYPE,
                               runner_flash=runner_flash,
                               runner_debug=runner_debug)

    west_env_path.write_text(env_content, encoding="utf-8")

    return zephyr_root, proj_dir, scripts_dir

def get_sdk_paths():
    found_sdks = {}
    sdk_pattern = re.compile(r"zephyr-sdk-(\d+\.\d+\.\d+)")

    for base_path in os_dep.sdk_base_paths:
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

    return sorted_sdks

def update_settings(proj_dir: str, selected_sdk: str):
    vscode_dir = Path(proj_dir) / ".vscode"
    settings_file = vscode_dir / "settings.json"

    if settings_file.exists():
        with settings_file.open("r", encoding="utf-8") as file:
            try:
                settings_json = json.load(file)
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
                settings_json = {}
    else:
        settings_json = {}

    insert_settings = {
        "ZEPHYRSDK": str(selected_sdk),
        "PROJ_PATH": str(proj_dir),
        "CROSS_GDB_PATH": str(os_dep.cross_gdb_path)
    }

    merged_settings = {**settings_json, **insert_settings}

    vscode_dir.mkdir(parents=True, exist_ok=True)
    with settings_file.open("w", encoding="utf-8") as file:
        json.dump(merged_settings, file, indent=2, ensure_ascii=False)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    BOARD_TYPE = sys.argv[1]

    print ("BOARD_TYPE:\r\n\t" + str(BOARD_TYPE) + "\r\n")
    zephyr_root, proj_dir, scripts_dir = setup_env()

    sorted_sdks = get_sdk_paths()
    selected_sdk = sorted_sdks[0][1]

    print("Installed SDK:")
    for sdk_path in sorted_sdks:
        print("\t" + str(sdk_path[0]) + " : " + str(sdk_path[1]))
    print("USE:\r\n\t" + str(selected_sdk))

    update_settings(proj_dir=proj_dir, selected_sdk=selected_sdk)
    os_dep.duplicate_scripts(zephyr_root=zephyr_root, proj_dir=proj_dir, scripts_dir=scripts_dir)
