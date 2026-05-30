#!/usr/bin/env python3

import sys
import subprocess

def find_device(model: str) -> str:
    try:
        result = subprocess.run(
            ["adb", "devices"],
            capture_output=True, text=True, check=True,
        )
    except (FileNotFoundError, subprocess.CalledProcessError) as e:
        print(f"adb devices failed: {e}")
        return ""

    for line in result.stdout.splitlines()[1:]:
        parts = line.split()
        if len(parts) < 2 or parts[1] != "device":
            continue

        serial = parts[0]
        try:
            dt_model = subprocess.run(
                ["adb", "-s", serial, "shell", "cat", "/proc/device-tree/model"],
                capture_output=True, text=True, check=True,
            ).stdout
        except subprocess.CalledProcessError:
            continue

        dt_model = dt_model.replace("\x00", "").strip()
        if model in dt_model:
            print(f"adb device found:\r\n\t{serial} ({dt_model})")
            return serial

    print(f"No adb device matching '{model}' was found.")
    return ""

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    print(find_device(model=sys.argv[1]))
