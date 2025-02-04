#!/usr/bin/env python3

import os
import sys
import json

def get_runner(cmd_type :str, board_type :str) -> str:
    script_dir = os.path.dirname(os.path.abspath(__file__))
    runner_json = os.path.join(script_dir, "runner.json")

    try:
        with open(runner_json, "r") as file:
            runner_data = json.load(file)
    except FileNotFoundError:
        print(f"Error: File '{runner_json}' not found.", file=sys.stderr)
        return ""
    except json.JSONDecodeError:
        print(f"Error: Failed to parse JSON file '{runner_json}'.", file=sys.stderr)
        return ""

    return runner_data.get(cmd_type).get(board_type, "")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(1)

    print (get_runner(cmd_type=sys.argv[1], board_type=sys.argv[2]))

