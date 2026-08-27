import platform
import subprocess
from pathlib import Path

root = Path(__file__).parent.parent

system = platform.system()

if system == "Windows":
    python = root / "venv" / "Scripts" / "python.exe"

elif system == "Linux":
    if "microsoft" in platform.release().lower():
        python = root / ".vscode" / "env" / "bin" / "python"
    else:
        python = root / ".vscode" / ".venv" / "bin" / "python"

else:
    raise RuntimeError(f"Unsupported OS: {system}")

if not python.exists():
    raise FileNotFoundError(
        f"Python environment not found: {python}"
    )

subprocess.run([
    str(python),
    str(root / ".vscode" / "runner.py")
])