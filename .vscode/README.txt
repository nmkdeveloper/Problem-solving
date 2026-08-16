# PyQt6 VS Code Runner

This is a VS Code task runner for C++ / Pascal / Python with a PyQt6 GUI.

## Platform support

- Windows
- Linux (Ubuntu, Debian, Fedora, Arch and other common POSIX distributions)

Linux-specific behavior includes:

- native Linux executable names (no `.exe`)
- `g++` / `fpc` without Windows-only linker flags
- dedicated process groups using Qt `QProcess.setChildProcessModifier(os.setsid)`
- process-group termination with `killpg(SIGKILL)`
- Linux peak RSS tracking through `/proc/<pid>/status` (`VmHWM`)
- Windows-only `pywin32` remains optional and is installed only on Windows

## Install

Create the virtual environment expected by `tasks.json`:

```bash
python3 -m venv .vscode/venv
.vscode/venv/bin/python -m pip install -r .vscode/requirements.txt
```

On Linux, install the native compilers you need through your distribution:

- C++: `g++`
- Pascal: `fpc`
- Python: `python3`

## Run

Use the supplied `tasks.json`. It passes the active VS Code file through `TARGET_FILE=${file}`.
