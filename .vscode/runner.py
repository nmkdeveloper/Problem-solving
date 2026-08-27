import ctypes
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time
from pathlib import Path

# ---------------------------------------------------------------------------
# PyQt6: import everything explicitly and NEVER hide the real exception.
# ---------------------------------------------------------------------------
try:
    from PyQt6.QtCore import (
        QEasingCurve,
        QProcess,
        QProcessEnvironment,
        QPropertyAnimation,
        QTimer,
        Qt,
    )
    from PyQt6.QtGui import QColor, QFont, QFontDatabase, QTextCursor, QIcon, QCursor
    from PyQt6.QtWidgets import (
        QApplication,
        QFrame,
        QGraphicsOpacityEffect,
        QGridLayout,
        QHBoxLayout,
        QLabel,
        QMainWindow,
        QPlainTextEdit,
        QPushButton,
        QSizePolicy,
        QTextEdit,
        QVBoxLayout,
        QWidget,
    )
except Exception as exc:
    print("=" * 72)
    print("[!] PyQt6 initialization/import failed.")
    print("=" * 72)
    print(f"Exception type : {type(exc).__name__}")
    print(f"Exception      : {exc}")
    print(f"Python         : {sys.executable}")
    print(f"Python version : {sys.version}")
    print()
    print("The real exception above is intentionally preserved.")
    print("=" * 72)
    raise


try:
    import psutil
    HAS_PSUTIL = True
except ImportError:
    psutil = None
    HAS_PSUTIL = False

try:
    import win32api
    import win32con
    HAS_PYWIN32 = True
except ImportError:
    win32api = None
    win32con = None
    HAS_PYWIN32 = False


SUPPORTED = {".cpp", ".cxx", ".cc", ".pas", ".pp", ".py", ".pyw"}


def prepare_stdin_payload(text: str) -> bytes:
    if not text.endswith("\n"):
        text += "\n"
    return text.encode("utf-8")


def format_terminal_separator(width: int = 68) -> str:
    return "-" * width


def format_stdin_echo(text: str) -> str:
    lines = text.splitlines()
    if not lines:
        return "> \n"
    return "".join(f"> {line}\n" for line in lines)


def print_color(text, color_code):
    colors = {
        "red": "\033[91m",
        "green": "\033[92m",
        "yellow": "\033[93m",
        "cyan": "\033[96m",
        "gray": "\033[90m",
        "magenta": "\033[95m",
        "bold_white": "\033[1;97m",
        "reset": "\033[0m",
    }
    print(f"{colors.get(color_code, '')}{text}{colors['reset']}")


def get_windows_error_message(code: int) -> str:
    if os.name != "nt":
        return ""

    unsigned_code = code & 0xFFFFFFFF
    msg = ""

    if HAS_PYWIN32:
        try:
            msg = win32api.FormatMessage(unsigned_code).strip()
        except Exception:
            pass
        if not msg:
            try:
                h_ntdll = win32api.GetModuleHandle("ntdll.dll")
                flags = (
                    win32con.FORMAT_MESSAGE_FROM_HMODULE
                    | win32con.FORMAT_MESSAGE_IGNORE_INSERTS
                )
                msg = win32api.FormatMessage(
                    flags, h_ntdll, unsigned_code, 0, None
                ).strip()
            except Exception:
                pass

    if not msg:
        flags = 0x00000800 | 0x00000200
        buffer = ctypes.create_unicode_buffer(2048)
        h_ntdll = ctypes.windll.kernel32.GetModuleHandleW("ntdll.dll")
        if h_ntdll:
            result = ctypes.windll.kernel32.FormatMessageW(
                flags,
                h_ntdll,
                ctypes.c_ulong(unsigned_code),
                0,
                buffer,
                2048,
                None,
            )
            if result > 0:
                msg = buffer.value.strip()

    if msg:
        msg = msg.replace("{EXCEPTION}", "")
        msg = msg.replace("0x%p", "unmapped address")
        msg = msg.replace("%p", "unmapped address")
        msg = msg.replace("%s", "read/written")
        msg = msg.replace("\r", "").replace("\n", " - ")
        msg = re.sub(r"\s+", " ", msg).strip()

    return msg


# Compiler-specific Pascal stack limit. Kept separate from realtime Peak Memory.
PASCAL_STACK_BYTES = 32 * 1024 * 1024  # 32 MiB
LINUX_PROCESS_GROUP_LAUNCHER = "setsid"
LINUX_MEMORY_WRAPPER = Path(__file__).resolve().parent / "memory_wrapper.py"

def get_max_stack_bytes(percentage=0.90):
    default_bytes = 1024 * 1024 * 1024
    if HAS_PSUTIL:
        try:
            return int(psutil.virtual_memory().available * percentage)
        except Exception:
            pass
    return default_bytes


def read_linux_memory_stats(path) -> int:
    """Read peak RSS recorded by the Linux memory wrapper."""
    if not path:
        return 0
    try:
        value = int(Path(path).read_text(encoding="ascii").strip())
        return max(0, value)
    except (OSError, ValueError):
        return 0


def build_cpp_command(source: Path, exe: Path, max_stack_bytes: int):
    cmd = [
        "g++", "-O3", "-g",
        "-Wall", "-Wextra", "-Wpedantic",
        "-Warray-bounds=2",
        "-D_GLIBCXX_DEBUG",
        "-D_GLIBCXX_DEBUG_PEDANTIC",
        "-D_FORTIFY_SOURCE=2",
    ]
    if os.name == "nt":
        cmd.append(f"-Wl,--stack,{max_stack_bytes}")
    cmd.extend([str(source), "-o", str(exe)])
    return cmd


def build_pascal_command(source: Path, exe: Path):
    cmd = [
        "fpc", "-O-", "-Cr", "-Ci", "-Co", "-Ct", "-CR",
        "-Sa", "-Se", "-vwnh",
    ]
    if os.name == "nt":
        cmd.append(f"-Cs{PASCAL_STACK_BYTES}")
    cmd.extend([f"-o{exe}", str(source)])
    return cmd


def build_process_launch_command(command):
    """Fallback launcher for Linux builds when Qt child modifiers are unavailable."""
    command = list(command)
    if os.name == "posix" and shutil.which(LINUX_PROCESS_GROUP_LAUNCHER):
        return [LINUX_PROCESS_GROUP_LAUNCHER, *command]
    return command


def configure_linux_process_group(process) -> bool:
    """Create a dedicated Linux process group before exec when Qt supports it."""
    if os.name != "posix":
        return False
    modifier = getattr(process, "setChildProcessModifier", None)
    if modifier is None:
        return False
    try:
        modifier(os.setsid)
        return True
    except Exception:
        return False


def read_linux_peak_memory(pid: int) -> int:
    """Read Linux VmHWM, the kernel's peak resident-set watermark."""
    if os.name != "posix" or not pid:
        return 0
    try:
        with open(f"/proc/{int(pid)}/status", "r", encoding="utf-8") as stream:
            for line in stream:
                if line.startswith("VmHWM:"):
                    parts = line.split()
                    if len(parts) >= 2:
                        value = int(parts[1])
                        unit = parts[2].lower() if len(parts) >= 3 else "kb"
                        if unit == "kb":
                            return value * 1024
                        if unit == "mb":
                            return value * 1024 * 1024
                        return value
    except (OSError, ValueError):
        pass
    return 0


def build_python_command(source: Path):
    env = os.environ.copy()
    env["PYTHONDEVMODE"] = "1"
    env["PYTHONWARNINGS"] = "error"
    return [
        [sys.executable, "-W", "error", "-X", "dev", str(source)],
        env,
    ]



# ---------------------------------------------------------------------------
# Peak memory tracking
# Windows keeps a process handle open so PeakWorkingSetSize is still
# available even when a very short-lived program exits between timer ticks.
# ---------------------------------------------------------------------------
_PROCESS_QUERY_INFORMATION = 0x0400
_PROCESS_VM_READ = 0x0010

if os.name == "nt":
    class _PROCESS_MEMORY_COUNTERS(ctypes.Structure):
        _fields_ = [
            ("cb", ctypes.c_ulong),
            ("PageFaultCount", ctypes.c_ulong),
            ("PeakWorkingSetSize", ctypes.c_size_t),
            ("WorkingSetSize", ctypes.c_size_t),
            ("QuotaPeakPagedPoolUsage", ctypes.c_size_t),
            ("QuotaPagedPoolUsage", ctypes.c_size_t),
            ("QuotaPeakNonPagedPoolUsage", ctypes.c_size_t),
            ("QuotaNonPagedPoolUsage", ctypes.c_size_t),
            ("PagefileUsage", ctypes.c_size_t),
            ("PeakPagefileUsage", ctypes.c_size_t),
        ]

    _kernel32 = ctypes.windll.kernel32
    _psapi = ctypes.WinDLL("psapi.dll")

    _kernel32.OpenProcess.argtypes = [
        ctypes.c_ulong, ctypes.c_int, ctypes.c_ulong
    ]
    _kernel32.OpenProcess.restype = ctypes.c_void_p
    _kernel32.CloseHandle.argtypes = [ctypes.c_void_p]
    _kernel32.CloseHandle.restype = ctypes.c_int
    _psapi.GetProcessMemoryInfo.argtypes = [
        ctypes.c_void_p,
        ctypes.POINTER(_PROCESS_MEMORY_COUNTERS),
        ctypes.c_ulong,
    ]
    _psapi.GetProcessMemoryInfo.restype = ctypes.c_int


def open_memory_handle(pid: int):
    if os.name != "nt" or not pid:
        return None
    try:
        return _kernel32.OpenProcess(
            _PROCESS_QUERY_INFORMATION | _PROCESS_VM_READ,
            False,
            int(pid),
        )
    except Exception:
        return None


def read_peak_memory(handle):
    if not handle:
        return 0
    try:
        counters = _PROCESS_MEMORY_COUNTERS()
        counters.cb = ctypes.sizeof(counters)
        if _psapi.GetProcessMemoryInfo(
            handle, ctypes.byref(counters), ctypes.sizeof(counters)
        ):
            return int(counters.PeakWorkingSetSize)
    except Exception:
        pass
    return 0


def close_memory_handle(handle):
    if handle and os.name == "nt":
        try:
            _kernel32.CloseHandle(handle)
        except Exception:
            pass


def sample_process_memory(pid: int, current_peak: int = 0) -> int:
    best = current_peak
    if os.name == "nt":
        handle = open_memory_handle(pid)
        if handle:
            best = max(best, read_peak_memory(handle))
            close_memory_handle(handle)
            return best
    if os.name == "posix":
        best = max(best, read_linux_peak_memory(pid))

    if HAS_PSUTIL:
        try:
            best = max(best, psutil.Process(pid).memory_info().rss)
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass
    return best


def kill_process_tree(pid: int):
    if not pid:
        return

    if os.name == "nt":
        try:
            subprocess.run(
                ["taskkill", "/PID", str(pid), "/T", "/F"],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                check=False,
                creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0),
            )
            return
        except OSError:
            pass

    if os.name == "posix":
        try:
            os.killpg(int(pid), signal.SIGKILL)
            return
        except (OSError, ProcessLookupError):
            pass

    if not HAS_PSUTIL:
        return

    try:
        parent = psutil.Process(pid)
    except (psutil.NoSuchProcess, psutil.AccessDenied):
        return

    try:
        children = parent.children(recursive=True)
    except (psutil.NoSuchProcess, psutil.AccessDenied):
        children = []

    targets = list(reversed(children)) + [parent]
    for proc in targets:
        try:
            proc.kill()
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            pass

    try:
        psutil.wait_procs(targets, timeout=1.0)
    except Exception:
        pass


STATUS_COLORS = {
    "idle": "#667085",
    "building": "#B54708",
    "running": "#175CD3",
    "success": "#027A48",
    "failed": "#B42318",
    "stopped": "#667085",
}


APP_STYLE = r"""
QWidget {
    color: #101828;
    font-family: "VNF-Comic Sans", "Segoe UI";
    font-size: 10pt;
}
QMainWindow {
    background: #F7F8FC;
}
QFrame#HeaderCard,
QFrame#ConsoleCard,
QFrame#InputCard,
QFrame#MetricCard {
    background: #FFFFFF;
    border: 1px solid #EAECF0;
    border-radius: 16px;
}
QLabel#AppTitle {
    color: #101828;
    font-size: 16pt;
    font-weight: 700;
}
QLabel#FileName {
    color: #667085;
    font-size: 9pt;
}
QLabel#SectionTitle {
    color: #344054;
    font-size: 9pt;
    font-weight: 700;
}
QLabel#StatusBadge {
    padding: 6px 12px;
    border-radius: 10px;
    font-size: 9pt;
    font-weight: 700;
}
QLabel#MetricLabel {
    color: #667085;
    font-size: 8pt;
    font-weight: 600;
}
QLabel#MetricValue {
    color: #101828;
    font-size: 12pt;
    font-weight: 700;
}
QTextEdit#Console {
    background: #172033;
    color: #E4E7EC;
    border: 1px solid #26334A;
    border-radius: 12px;
    padding: 12px;
    selection-background-color: #344054;
    selection-color: #F8FAFC;
    font-family: "JetBrains Mono", Consolas, "Cascadia Mono", monospace;
    font-size: 9.5pt;
}
QPlainTextEdit#Input {
    background: #FFFFFF;
    color: #101828;
    border: 1px solid #D0D5DD;
    border-radius: 14px;
    padding: 10px 12px;
    selection-background-color: #D1E9FF;
    selection-color: #101828;
    font-family: "JetBrains Mono", Consolas, "Cascadia Mono", monospace;
    font-size: 9.5pt;
}
QPlainTextEdit#Input:focus {
    border: 2px solid #84CAFF;
    background: #FFFFFF;
}
QPushButton {
    min-height: 38px;
    padding: 0 16px;
    border-radius: 10px;
    border: 1px solid #D0D5DD;
    background: #FFFFFF;
    color: #344054;
    font-weight: 700;
}
QPushButton:hover {
    background: #F9FAFB;
    border-color: #98A2B3;
}
QPushButton:pressed {
    background: #F2F4F7;
}
QPushButton#SendButton {
    background: #175CD3;
    border-color: #175CD3;
    color: #FFFFFF;
    min-width: 82px;
}
QPushButton#SendButton:hover {
    background: #1849A9;
}
QPushButton#StopButton {
    background: #FFF1F3;
    border-color: #FECDD6;
    color: #C01048;
    min-width: 82px;
}
QPushButton#StopButton:hover {
    background: #FFE4E8;
}
QPushButton#CloseButton {
    background: #101828;
    border-color: #101828;
    color: #FFFFFF;
    min-width: 82px;
}
QPushButton#CloseButton:hover {
    background: #1D2939;
}
QScrollBar:vertical {
    width: 10px;
    background: transparent;
}
QScrollBar::handle:vertical {
    background: #475467;
    border-radius: 5px;
    min-height: 30px;
}
QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical {
    height: 0;
}
"""


class RunnerWindow(QMainWindow):
    def __init__(self, target_path, app_icon=None):
        super().__init__()
        self.target_path = target_path
        self.directory = target_path.parent
        self.extension = target_path.suffix.lower()
        exe_suffix = ".exe" if os.name == "nt" else ""
        self.exe_path = self.directory / f"{target_path.stem}{exe_suffix}"

        self.compile_process = None
        self.process = None
        self.closing = False
        self.stop_requested = False
        self.run_started_at = None
        self.peak_memory_bytes = 0
        self.memory_handle = None
        self.memory_stats_path = None

        self.live_metrics_timer = QTimer(self)
        self.live_metrics_timer.setInterval(50)
        self.live_metrics_timer.timeout.connect(self.update_live_metrics)

        self.monitor_timer = QTimer(self)
        self.monitor_timer.setInterval(25)
        self.monitor_timer.timeout.connect(self.update_memory)

        self.setWindowTitle(f"Build & Run — {target_path.name}")
        if app_icon is not None and not app_icon.isNull():
            self.setWindowIcon(app_icon)
        # Start at 50% of the current monitor's available screen size.
        # Prefer the monitor where the cursor currently is, which is useful
        # on multi-monitor Linux/Windows setups.
        screen = QApplication.screenAt(QCursor.pos()) or QApplication.primaryScreen()
        if screen is not None:
            available = screen.availableGeometry()
            width = max(1, available.width() // 2)
            height = max(1, available.height() // 2)
            self.resize(width, height)
            self.move(
                available.x() + (available.width() - width) // 2,
                available.y() + (available.height() - height) // 2,
            )
        else:
            self.resize(980, 780)

        self._animations = []
        self._build_ui()
        self._start_pipeline()

    def _build_ui(self):
        root = QWidget()
        self.setCentralWidget(root)

        layout = QVBoxLayout(root)
        layout.setContentsMargins(18, 18, 18, 18)
        layout.setSpacing(12)

        header = QFrame()
        header.setObjectName("HeaderCard")
        header_layout = QHBoxLayout(header)
        header_layout.setContentsMargins(18, 14, 18, 14)

        dot = QLabel("●")
        dot.setStyleSheet("color:#175CD3; font-size:18px;")
        header_layout.addWidget(dot)

        heading = QVBoxLayout()
        heading.setSpacing(1)

        title = QLabel("Build & Run")
        title.setObjectName("AppTitle")
        filename = QLabel(self.target_path.name)
        filename.setObjectName("FileName")

        heading.addWidget(title)
        heading.addWidget(filename)
        header_layout.addLayout(heading)
        header_layout.addStretch(1)

        self.status = QLabel("Starting")
        self.status.setObjectName("StatusBadge")
        self.status.setAlignment(Qt.AlignmentFlag.AlignCenter)
        header_layout.addWidget(self.status)

        layout.addWidget(header)

        console_card = QFrame()
        console_card.setObjectName("ConsoleCard")
        console_layout = QVBoxLayout(console_card)
        console_layout.setContentsMargins(14, 12, 14, 14)
        console_layout.setSpacing(8)

        output_title = QLabel("OUTPUT")
        output_title.setObjectName("SectionTitle")
        console_layout.addWidget(output_title)

        self.console = QTextEdit()
        self.console.setObjectName("Console")
        self.console.setReadOnly(True)
        self.console.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)
        self.console.setFont(QFont("JetBrains Mono", 10))
        console_layout.addWidget(self.console, 1)
        layout.addWidget(console_card, 1)

        self.input_card = QFrame()
        self.input_card.setObjectName("InputCard")
        input_layout = QVBoxLayout(self.input_card)
        input_layout.setContentsMargins(14, 12, 14, 14)
        input_layout.setSpacing(8)

        input_title = QLabel("STANDARD INPUT")
        input_title.setObjectName("SectionTitle")
        input_layout.addWidget(input_title)

        input_row = QHBoxLayout()
        input_row.setSpacing(8)

        self.stdin = QPlainTextEdit()
        self.stdin.setObjectName("Input")
        self.stdin.setPlaceholderText("Type input here…   Ctrl+Enter to send")
        self.stdin.setFixedHeight(64)
        self.stdin.setFont(QFont("JetBrains Mono", 10))
        self.stdin.installEventFilter(self)

        self.send_button = QPushButton("Send")
        self.send_button.setObjectName("SendButton")
        self.send_button.clicked.connect(self.send_stdin)
        self.send_button.setEnabled(False)

        input_row.addWidget(self.stdin, 1)
        input_row.addWidget(self.send_button)
        input_layout.addLayout(input_row)

        layout.addWidget(self.input_card)
        self.input_card.setVisible(False)

        metrics = QGridLayout()
        metrics.setHorizontalSpacing(10)

        self.return_card, self.return_value = self._make_metric(
            "RETURN CODE", "—"
        )
        self.time_card, self.time_value = self._make_metric(
            "EXECUTION TIME", "—"
        )
        self.memory_card, self.memory_value = self._make_metric(
            "PEAK MEMORY", "—"
        )

        metrics.addWidget(self.return_card, 0, 0)
        metrics.addWidget(self.time_card, 0, 1)
        metrics.addWidget(self.memory_card, 0, 2)

        for col in range(3):
            metrics.setColumnStretch(col, 1)

        layout.addLayout(metrics)

        actions = QHBoxLayout()
        actions.addStretch(1)

        self.stop_button = QPushButton("Stop")
        self.stop_button.setObjectName("StopButton")
        self.stop_button.setVisible(False)
        self.stop_button.setEnabled(False)
        self.stop_button.clicked.connect(self.stop_process)

        self.close_button = QPushButton("Close")
        self.close_button.setObjectName("CloseButton")
        self.close_button.clicked.connect(self.close)

        actions.addWidget(self.stop_button)
        actions.addWidget(self.close_button)
        layout.addLayout(actions)

        self.set_status("idle", "Starting")

    @staticmethod
    def _make_metric(label_text, value_text):
        card = QFrame()
        card.setObjectName("MetricCard")
        card_layout = QVBoxLayout(card)
        card_layout.setContentsMargins(14, 10, 14, 10)
        card_layout.setSpacing(2)

        label = QLabel(label_text)
        label.setObjectName("MetricLabel")
        value = QLabel(value_text)
        value.setObjectName("MetricValue")

        card_layout.addWidget(label)
        card_layout.addWidget(value)
        return card, value

    def set_status(self, state, text):
        base = STATUS_COLORS.get(state, STATUS_COLORS["idle"])
        self.status.setText(text)
        self.status.setStyleSheet(
            f"background:{base}15; color:{base}; "
            f"border:1px solid {base}30; "
            "padding:6px 12px; border-radius:10px; font-weight:700;"
        )

    def _animate_visibility(self, widget, visible: bool, duration=180):
        effect = widget.graphicsEffect()
        if not isinstance(effect, QGraphicsOpacityEffect):
            effect = QGraphicsOpacityEffect(widget)
            widget.setGraphicsEffect(effect)

        if visible:
            widget.setVisible(True)
            effect.setOpacity(0.0)
            animation = QPropertyAnimation(effect, b"opacity", self)
            animation.setDuration(duration)
            animation.setStartValue(0.0)
            animation.setEndValue(1.0)
        else:
            animation = QPropertyAnimation(effect, b"opacity", self)
            animation.setDuration(duration)
            animation.setStartValue(effect.opacity())
            animation.setEndValue(0.0)
            animation.finished.connect(lambda: widget.setVisible(False))

        animation.setEasingCurve(QEasingCurve.Type.OutCubic)
        animation.finished.connect(lambda: self._discard_animation(animation))
        self._animations.append(animation)
        animation.start()

    def _discard_animation(self, animation):
        if animation in self._animations:
            self._animations.remove(animation)
        animation.deleteLater()

    def _set_running_controls(self, running: bool):
        self.send_button.setEnabled(running)
        self._animate_visibility(self.input_card, running)
        self._animate_visibility(self.stop_button, running)
        self.stop_button.setEnabled(running)

    def eventFilter(self, obj, event):
        if obj is self.stdin and event.type() == event.Type.KeyPress:
            if (
                event.key() == Qt.Key.Key_Return
                and event.modifiers() & Qt.KeyboardModifier.ControlModifier
            ):
                self.send_stdin()
                return True
        return super().eventFilter(obj, event)

    def append_output(self, text, kind="normal"):
        if not text:
            return

        colors = {
            "normal": "#D0D5DD",
            "stdout": "#F2F4F7",
            "stderr": "#FDA29B",
            "command": "#84CAFF",
            "success": "#6CE9A6",
            "warning": "#FEC84B",
            "error": "#F97066",
            "info": "#98A2B3",
            "stdin": "#A6F4C5",
        }

        cursor = self.console.textCursor()
        cursor.movePosition(QTextCursor.MoveOperation.End)

        fmt = cursor.charFormat()
        fmt.setForeground(QColor(colors.get(kind, colors["normal"])))
        cursor.setCharFormat(fmt)
        cursor.insertText(text)

        self.console.setTextCursor(cursor)
        self.console.ensureCursorVisible()

    def _start_pipeline(self):
        if not self.target_path.is_file():
            self.append_output(
                f"[!] File not found: {self.target_path}\n", "error"
            )
            self.set_status("failed", "File not found")
            return

        self.append_output(f"Target: {self.target_path}\n", "info")
        self.append_output("\n[1/3] Cleaning workspace...\n", "info")

        if self.exe_path.exists():
            try:
                self.exe_path.unlink()
            except OSError as exc:
                self.append_output(
                    f"[!] Could not remove old executable: {exc}\n", "error"
                )
                self.set_status("failed", "Cleanup failed")
                return

        if self.extension in {".cpp", ".cxx", ".cc"}:
            self._compile_cpp()
        elif self.extension in {".pas", ".pp"}:
            self._compile_pascal()
        elif self.extension in {".py", ".pyw"}:
            self._check_python()
        else:
            self.append_output("[!] Unsupported file type.\n", "error")
            self.set_status("failed", "Unsupported")

    def _start_compile_process(self, cmd, label):
        self.compile_process = QProcess(self)
        self.compile_process.setWorkingDirectory(str(self.directory))
        use_qt_process_group = configure_linux_process_group(self.compile_process)
        launch_cmd = cmd if use_qt_process_group or os.name != "posix" else build_process_launch_command(cmd)
        self.compile_process.setProgram(launch_cmd[0])
        self.compile_process.setArguments(launch_cmd[1:])
        self.compile_process.readyReadStandardOutput.connect(self._compile_stdout)
        self.compile_process.readyReadStandardError.connect(self._compile_stderr)
        self.compile_process.finished.connect(self._compile_finished)

        self.set_status("building", "Compiling")
        self.append_output(f"[2/3] {label}\n", "command")
        self.compile_process.start()

    def _compile_cpp(self):
        if not shutil.which("g++"):
            self.append_output("[!] g++ compiler not found in PATH.\n", "error")
            self.set_status("failed", "Compiler missing")
            return

        stack = get_max_stack_bytes(0.90)
        self._start_compile_process(
            build_cpp_command(self.target_path, self.exe_path, stack),
            f"Compiling C++ (O3 | Stack: "
            f"{stack / (1024 * 1024):.0f} MB)...",
        )

    def _compile_pascal(self):
        if not shutil.which("fpc"):
            self.append_output("[!] fpc compiler not found in PATH.\n", "error")
            self.set_status("failed", "Compiler missing")
            return
        
        self._start_compile_process(
            build_pascal_command(self.target_path, self.exe_path),
            f"Compiling Pascal (Strict Debug | Stack: "
            f"{PASCAL_STACK_BYTES / (1024 * 1024):.0f} MB)...",
        )

    def _compile_stdout(self):
        if self.compile_process:
            data = bytes(
                self.compile_process.readAllStandardOutput()
            ).decode("utf-8", "replace")
            self.append_output(data, "command")

    def _compile_stderr(self):
        if self.compile_process:
            data = bytes(
                self.compile_process.readAllStandardError()
            ).decode("utf-8", "replace")
            self._append_compiler_diagnostics(data)

    def _append_compiler_diagnostics(self, data):
        """Render compiler diagnostics with warnings in yellow and errors in red."""
        if not data:
            return

        lines = data.splitlines(keepends=True)
        if not lines:
            self.append_output(data, "stderr")
            return

        for line in lines:
            normalized = line.lower()
            if re.search(r"\\bwarning(?:\\s+\\w+)?\\s*:", normalized):
                self.append_output(line, "warning")
            elif re.search(r"\\berror(?:\\s+\\w+)?\\s*:", normalized):
                self.append_output(line, "error")
            else:
                self.append_output(line, "stderr")

    def _compile_finished(self, exit_code, _exit_status):
        if self.closing:
            return

        self._compile_stdout()
        self._compile_stderr()

        process = self.compile_process
        self.compile_process = None
        if process:
            process.deleteLater()

        if exit_code != 0 or not self.exe_path.exists():
            self.append_output(
                f"\n[!] Compilation failed (Exit Code: {exit_code})\n",
                "error",
            )
            self.set_status("failed", "Build Failed")
            return

        self.append_output("\nCompilation successful.\n", "success")
        self._launch_program()

    def _check_python(self):
        self.set_status("building", "Checking Python")
        self.append_output("[2/2] Verifying Python syntax...\n", "command")

        result = subprocess.run(
            [sys.executable, "-m", "py_compile", str(self.target_path)],
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
        )

        if result.stdout:
            self.append_output(result.stdout, "command")
        if result.stderr:
            self.append_output(result.stderr, "stderr")

        if result.returncode != 0:
            self.append_output(
                f"\n[!] Python Syntax Check Failed "
                f"(Exit Code: {result.returncode})\n",
                "error",
            )
            self.set_status("failed", "Syntax Error")
            return

        self.append_output("Syntax check successful.\n", "success")
        self._launch_program()

    def _launch_program(self):
        self.append_output("\n[3/3] Launching process...\n", "command")
        self.append_output(format_terminal_separator() + "\n", "info")

        self.stop_requested = False
        self.process = QProcess(self)
        self.process.setWorkingDirectory(str(self.directory))
        self.process.setProcessChannelMode(
            QProcess.ProcessChannelMode.SeparateChannels
        )

        self.process.readyReadStandardOutput.connect(self._stdout_ready)
        self.process.readyReadStandardError.connect(self._stderr_ready)
        self.process.started.connect(self._process_started)
        self.process.errorOccurred.connect(self._process_error)
        self.process.finished.connect(self._process_finished)

        if self.extension in {".py", ".pyw"}:
            command, env_dict = build_python_command(self.target_path)
            environment = QProcessEnvironment.systemEnvironment()
            for key, value in env_dict.items():
                environment.insert(key, value)
            self.process.setProcessEnvironment(environment)
        else:
            command = [str(self.exe_path)]

        self.set_status("running", "Starting")

        # Linux: use a transparent wrapper that records the exact peak RSS
        # of the user process with getrusage(RUSAGE_CHILDREN). Timer sampling
        # alone can report 0 for programs that finish in only a few ms.
        if os.name == "posix" and LINUX_MEMORY_WRAPPER.exists():
            fd, stats_path = tempfile.mkstemp(
                prefix=".runner-memory-", suffix=".txt", dir=str(self.directory)
            )
            os.close(fd)
            self.memory_stats_path = Path(stats_path)
            command = [
                sys.executable,
                str(LINUX_MEMORY_WRAPPER),
                str(self.memory_stats_path),
                *command,
            ]

        use_qt_process_group = configure_linux_process_group(self.process)
        launch_command = command if use_qt_process_group or os.name != "posix" else build_process_launch_command(command)
        self.process.setProgram(launch_command[0])
        self.process.setArguments(launch_command[1:])
        self.process.start()

    def _process_started(self):
        self.run_started_at = time.perf_counter()
        self.peak_memory_bytes = 0

        pid = int(self.process.processId()) if self.process else 0
        if os.name == "nt":
            self.memory_handle = open_memory_handle(pid)
            if self.memory_handle:
                self.peak_memory_bytes = read_peak_memory(self.memory_handle)

        self.return_value.setText("RUNNING")
        self.time_value.setText("0.0ms")
        self.memory_value.setText(
            f"{self.peak_memory_bytes / (1024 * 1024):.2f} MB"
        )

        self.monitor_timer.start()
        self.live_metrics_timer.start()
        self._set_running_controls(True)
        self.set_status("running", "Running")

    def _stdout_ready(self):
        if self.process:
            data = bytes(
                self.process.readAllStandardOutput()
            ).decode("utf-8", "replace")
            self.append_output(data, "stdout")

    def _stderr_ready(self):
        if self.process:
            data = bytes(
                self.process.readAllStandardError()
            ).decode("utf-8", "replace")
            self.append_output(data, "stderr")

    def update_memory(self):
        if not self.process:
            return

        pid = int(self.process.processId())
        if pid:
            if self.memory_handle:
                self.peak_memory_bytes = max(
                    self.peak_memory_bytes,
                    read_peak_memory(self.memory_handle),
                )
            elif self.process.state() == QProcess.ProcessState.Running:
                self.peak_memory_bytes = max(
                    self.peak_memory_bytes,
                    sample_process_memory(pid, self.peak_memory_bytes),
                )

        self.memory_value.setText(
            f"{self.peak_memory_bytes / (1024 * 1024):.2f} MB"
        )

    def update_live_metrics(self):
        if not self.process or self.run_started_at is None:
            return

        elapsed_ms = (time.perf_counter() - self.run_started_at) * 1000
        time_str = (
            f"{elapsed_ms / 1000:.3f}s"
            if elapsed_ms >= 1000
            else f"{elapsed_ms:.1f}ms"
        )
        self.time_value.setText(time_str)
        self.update_memory()

    def send_stdin(self):
        if not self.process:
            return
        if self.process.state() != QProcess.ProcessState.Running:
            return

        text = self.stdin.toPlainText()
        if not text:
            return

        self.append_output(format_stdin_echo(text), "stdin")
        self.process.write(prepare_stdin_payload(text))
        self.process.waitForBytesWritten(1000)
        self.stdin.clear()

    def stop_process(self):
        if not self.process:
            return
        if self.process.state() == QProcess.ProcessState.NotRunning:
            return

        self.stop_requested = True
        self.stop_button.setEnabled(False)
        self.send_button.setEnabled(False)
        self.set_status("stopped", "Stopping…")

        pid = int(self.process.processId())
        kill_process_tree(pid)

        if self.process.state() != QProcess.ProcessState.NotRunning:
            self.process.kill()
            self.process.waitForFinished(1000)

    def _process_error(self, error):
        if self.closing:
            return
        if error == QProcess.ProcessError.FailedToStart:
            if self.memory_stats_path:
                try:
                    self.memory_stats_path.unlink(missing_ok=True)
                except OSError:
                    pass
                self.memory_stats_path = None
            self.append_output(
                "\n[!] Process failed to start.\n", "error"
            )
            self.set_status("failed", "Start Failed")

    def _process_finished(self, exit_code, _exit_status):
        self._stdout_ready()
        self._stderr_ready()

        self.monitor_timer.stop()
        self.live_metrics_timer.stop()

        if self.memory_handle:
            self.peak_memory_bytes = max(
                self.peak_memory_bytes,
                read_peak_memory(self.memory_handle),
            )
            close_memory_handle(self.memory_handle)
            self.memory_handle = None
        else:
            pid = int(self.process.processId()) if self.process else 0
            if pid:
                self.peak_memory_bytes = max(
                    self.peak_memory_bytes,
                    sample_process_memory(pid, self.peak_memory_bytes),
                )

        if self.memory_stats_path:
            self.peak_memory_bytes = max(
                self.peak_memory_bytes,
                read_linux_memory_stats(self.memory_stats_path),
            )
            try:
                self.memory_stats_path.unlink(missing_ok=True)
            except OSError:
                pass
            self.memory_stats_path = None

        self.memory_value.setText(
            f"{self.peak_memory_bytes / (1024 * 1024):.2f} MB"
        )

        elapsed_ms = 0.0
        if self.run_started_at is not None:
            elapsed_ms = (time.perf_counter() - self.run_started_at) * 1000

        code = int(exit_code)
        time_str = (
            f"{elapsed_ms / 1000:.3f}s"
            if elapsed_ms >= 1000
            else f"{elapsed_ms:.1f}ms"
        )
        memory_str = (
            f"{self.peak_memory_bytes / (1024 * 1024):.2f} MB"
            if HAS_PSUTIL or os.name == "posix"
            else "N/A"
        )

        self.return_value.setText(
            f"{code} ({code & 0xFFFFFFFF:#010x})"
        )
        self.time_value.setText(time_str)
        self.memory_value.setText(memory_str)

        self._set_running_controls(False)

        if self.stop_requested:
            self.set_status("stopped", "Stopped")
            self.append_output(
                "\n" + format_terminal_separator() + "\n", "info"
            )
            self.append_output(
                "STOPPED  Process tree terminated by user.\n",
                "warning",
            )
        elif code == 0:
            self.set_status("success", "Success")
            self.append_output(
                "\n" + format_terminal_separator() + "\n", "info"
            )
            self.append_output("SUCCESS\n", "success")
        else:
            self.set_status("failed", "Failed")
            self.append_output(
                "\n" + format_terminal_separator() + "\n", "info"
            )
            self.append_output(
                f"FAILED   Return Code: {code} "
                f"({code & 0xFFFFFFFF:#010x})\n",
                "error",
            )

            message = get_windows_error_message(code)
            if message:
                self.append_output(
                    f"DETAILS  System Error: {message}\n",
                    "warning",
                )

        self.process = None

    def _kill_qprocess(self, process):
        if not process:
            return

        if process.state() == QProcess.ProcessState.NotRunning:
            return

        try:
            pid = int(process.processId())
            kill_process_tree(pid)
        except Exception:
            pass

        if process.state() != QProcess.ProcessState.NotRunning:
            process.kill()
            process.waitForFinished(1000)


    def center_on_current_screen(self):
        """Center the runner on the monitor containing the VS Code window.

        The task is launched by VS Code, so Qt's cursor position is normally
        on the VS Code monitor. If screenAt() cannot resolve a screen, fall
        back to the screen containing the current window, then primary screen.
        """
        screen = QApplication.screenAt(QCursor.pos())

        if screen is None:
            screen = self.screen()

        if screen is None:
            screen = QApplication.primaryScreen()

        if screen is None:
            return

        available = screen.availableGeometry()
        frame = self.frameGeometry()
        frame.moveCenter(available.center())
        self.move(frame.topLeft())


    def closeEvent(self, event):
        self.closing = True
        self.monitor_timer.stop()
        self.live_metrics_timer.stop()

        if self.memory_handle:
            close_memory_handle(self.memory_handle)
            self.memory_handle = None

        if self.memory_stats_path:
            try:
                self.memory_stats_path.unlink(missing_ok=True)
            except OSError:
                pass
            self.memory_stats_path = None

        if self.compile_process:
            self._kill_qprocess(self.compile_process)

        if self.process:
            self._kill_qprocess(self.process)

        event.accept()



# ---------------------------------------------------------------------------
# Shared application icon
#
# Put a real icon.ico beside runner.py:
#   .vscode/icon.ico
#
# The same icon is applied to Qt, the window/title bar, and Windows taskbar.
# AppUserModelID must be set before QApplication is created so Windows does
# not group the window under the generic Python icon.
# ---------------------------------------------------------------------------
ICON_PATH = Path(__file__).resolve().parent / "icon.ico"
WINDOWS_APP_ID = "nmkdeveloper.BuildRun.Runner"


def configure_windows_app_id():
    if os.name != "nt":
        return

    try:
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            WINDOWS_APP_ID
        )
    except Exception:
        # Icon support must never prevent the runner from starting.
        pass


def load_application_icon():
    if not ICON_PATH.is_file():
        return QIcon()

    try:
        icon = QIcon(str(ICON_PATH))
        return icon if not icon.isNull() else QIcon()
    except Exception:
        return QIcon()


def load_application_fonts(app):
    font_dir = Path(__file__).resolve().parent / "fonts"
    loaded = {}

    for filename in ("VNF-Comic Sans.ttf", "JetBrainsMono-Regular.ttf"):
        path = font_dir / filename
        if not path.is_file():
            continue

        font_id = QFontDatabase.addApplicationFont(str(path))
        if font_id < 0:
            continue

        families = QFontDatabase.applicationFontFamilies(font_id)
        if families:
            loaded[filename] = families[0]

    gui_family = loaded.get("VNF-Comic Sans.ttf", "Segoe UI")
    mono_family = loaded.get(
        "JetBrainsMono-Regular.ttf",
        "Cascadia Mono" if os.name == "nt" else "monospace",
    )

    return gui_family, mono_family


def main():
    configure_windows_app_id()

    target_str = os.environ.get("TARGET_FILE", "").strip()

    if not target_str:
        print("[!] TARGET_FILE environment variable is empty.")
        return 2

    target_path = Path(target_str).resolve()

    if not target_path.is_file():
        print(f"[!] File not found: {target_path}")
        print("Please save the current file before running.")
        return 2

    if target_path.suffix.lower() not in SUPPORTED:
        print("[!] Unsupported file type.")
        print("Supported: .cpp .cc .cxx .pas .pp .py .pyw")
        return 1

    app = QApplication.instance() or QApplication(sys.argv)
    app_icon = load_application_icon()
    if not app_icon.isNull():
        app.setWindowIcon(app_icon)
    app.setStyle("Fusion")

    gui_font, mono_font = load_application_fonts(app)

    # Replace the family names in the stylesheet only when the bundled fonts
    # actually loaded. This avoids a hard dependency on font installation.
    app.setFont(QFont(gui_font, 10))
    app.setStyleSheet(
        APP_STYLE.replace('"VNF-Comic Sans"', f'"{gui_font}"')
    )

    window = RunnerWindow(target_path, app_icon)

    # Use the actual loaded mono font for both terminal widgets.
    window.console.setFont(QFont(mono_font, 10))
    window.stdin.setFont(QFont(mono_font, 10))

    window.show()
    window.center_on_current_screen()
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())
