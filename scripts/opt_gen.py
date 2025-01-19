import os
import sys
import json

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    runner_json = os.path.join(script_dir, "support", "runner.json")

    if len(sys.argv) != 3:
        sys.exit(1)

    cmd_type = sys.argv[1]
    board_type = sys.argv[2]

    try:
        with open(runner_json, "r") as file:
            runner_data = json.load(file)
    except FileNotFoundError:
        print(f"Error: File '{runner_json}' not found.", file=sys.stderr)
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"Error: Failed to parse JSON file '{runner_json}'.", file=sys.stderr)
        sys.exit(1)

    print(runner_data.get(cmd_type).get(board_type, ""))

if __name__ == "__main__":
    main()
