import ast
from pathlib import Path
import subprocess
import sys

RUNNER = Path(__file__).with_name("runner.py")
SOURCE = RUNNER.read_text(encoding="utf-8")


def test_runner_compiles():
    ast.parse(SOURCE)


def _load_helpers(*names):
    tree = ast.parse(SOURCE)
    selected = [
        node for node in tree.body
        if isinstance(node, ast.FunctionDef) and node.name in names
    ]
    ns = {}
    exec(compile(ast.Module(body=selected, type_ignores=[]), str(RUNNER), "exec"), ns)
    return ns


def test_stdin_payload_adds_real_newline():
    ns = _load_helpers("prepare_stdin_payload")
    assert ns["prepare_stdin_payload"]("42") == b"42\n"
    assert ns["prepare_stdin_payload"]("42\n") == b"42\n"


def test_stdin_echo():
    ns = _load_helpers("format_stdin_echo")
    assert ns["format_stdin_echo"]("5\n11000\n00000") == "> 5\n> 11000\n> 00000\n"


def test_separator_is_ascii_only():
    ns = _load_helpers("format_terminal_separator")
    separator = ns["format_terminal_separator"]()
    assert separator
    assert set(separator) == {"-"}


def test_pyqt_import_error_message_is_not_faked():
    assert "except Exception as exc:" in SOURCE
    assert "PyQt6 initialization/import failed." in SOURCE
    assert "raise" in SOURCE


def test_dynamic_controls_are_hidden_after_finish():
    assert "_set_running_controls(False)" in SOURCE
    assert "self._animate_visibility(self.input_card, running)" in SOURCE
    assert "self._animate_visibility(self.stop_button, running)" in SOURCE


def test_stop_is_remembered_until_process_finished():
    assert "self.stop_requested = True" in SOURCE
    assert "if self.stop_requested:" in SOURCE


def test_ascii_separators_surround_final_status():
    assert 'format_terminal_separator() + "\\n", "info"' in SOURCE
    assert 'self.append_output("SUCCESS\\n", "success")' in SOURCE


def test_correct_plain_text_input_selector():
    assert "QPlainTextEdit#Input" in SOURCE
    assert "QTextEdit#Input" not in SOURCE


def test_has_live_metrics_timer():
    assert "self.live_metrics_timer.setInterval(50)" in SOURCE
    assert "self.live_metrics_timer.timeout.connect(self.update_live_metrics)" in SOURCE


def test_live_execution_time_updates():
    assert "def update_live_metrics(self):" in SOURCE
    assert "self.time_value.setText(time_str)" in SOURCE


def test_windows_peak_working_set_is_used():
    assert "PeakWorkingSetSize" in SOURCE
    assert "GetProcessMemoryInfo" in SOURCE
    assert "OpenProcess" in SOURCE


def test_peak_memory_is_read_after_process_finishes_before_handle_close():
    pos = SOURCE.index("self.live_metrics_timer.stop()")
    tail = SOURCE[pos:pos + 1800]
    assert "read_peak_memory(self.memory_handle)" in tail
    assert "close_memory_handle(self.memory_handle)" in tail


def test_optional_icon_ico():
    assert 'ICON_PATH = Path(__file__).resolve().parent / "icon.ico"' in SOURCE
    assert "QIcon(str(ICON_PATH))" in SOURCE


def test_windows_app_user_model_id_for_taskbar_icon():
    assert "SetCurrentProcessExplicitAppUserModelID" in SOURCE
    assert "nmkdeveloper.BuildRun.Runner" in SOURCE


def test_qapplication_gets_shared_icon():
    assert "app.setWindowIcon(app_icon)" in SOURCE


def test_window_gets_shared_icon():
    assert "self.setWindowIcon(app_icon)" in SOURCE


def test_icon_is_optional_and_resolved_next_to_runner():
    assert 'ICON_PATH = Path(__file__).resolve().parent / "icon.ico"' in SOURCE


def test_center_on_current_screen_helper_exists():
    assert "def center_on_current_screen(self):" in SOURCE
    assert "QApplication.screenAt" in SOURCE
    assert "availableGeometry()" in SOURCE


def test_centering_happens_after_window_is_shown():
    assert "window.show()" in SOURCE
    assert "window.center_on_current_screen()" in SOURCE


def test_app_icon_is_passed_to_runner_window():
    assert "def __init__(self, target_path, app_icon=None):" in SOURCE
    assert "window = RunnerWindow(target_path, app_icon)" in SOURCE


def test_window_icon_assignment_handles_missing_icon():
    assert "if app_icon is not None and not app_icon.isNull():" in SOURCE

def test_pascal_uses_independent_stack_limit():
    assert "PASCAL_STACK_BYTES = 32 * 1024 * 1024" in SOURCE
    assert 'cmd.append(f"-Cs{PASCAL_STACK_BYTES}")' in SOURCE

def test_pascal_command_does_not_use_available_ram():
    start=SOURCE.index("def build_pascal_command")
    end=SOURCE.index("def build_python_command", start)
    block=SOURCE[start:end]
    assert "max_stack_bytes" not in block

def test_cpp_still_uses_dynamic_stack_limit():
    assert 'f"-Wl,--stack,{max_stack_bytes}"' in SOURCE


def test_linux_runtime_uses_process_group_launcher():
    assert 'LINUX_PROCESS_GROUP_LAUNCHER = "setsid"' in SOURCE
    assert 'build_process_launch_command' in SOURCE
    assert 'configure_linux_process_group' in SOURCE
    assert 'setChildProcessModifier' in SOURCE
    assert 'os.setsid' in SOURCE


def test_linux_kills_process_group_without_taskkill():
    start = SOURCE.index('def kill_process_tree')
    end = SOURCE.index('STATUS_COLORS', start)
    block = SOURCE[start:end]
    assert 'os.name == "posix"' in block
    assert 'os.killpg' in block
    assert 'signal.SIGKILL' in block
    assert '["taskkill"' in block


def test_linux_peak_memory_reads_vm_hwm():
    assert 'VmHWM:' in SOURCE
    assert 'read_linux_peak_memory' in SOURCE


def test_linux_peak_memory_uses_child_rusage_wrapper_for_short_lived_processes():
    assert 'LINUX_MEMORY_WRAPPER = Path(__file__).resolve().parent / "memory_wrapper.py"' in SOURCE
    assert 'read_linux_memory_stats' in SOURCE
    wrapper = Path(__file__).with_name("memory_wrapper.py").read_text(encoding="utf-8")
    assert 'resource.RUSAGE_CHILDREN' in wrapper
    assert 'ru_maxrss' in wrapper


def test_linux_compiler_commands_avoid_windows_flags():
    cpp_start = SOURCE.index('def build_cpp_command')
    cpp_end = SOURCE.index('def build_pascal_command', cpp_start)
    cpp = SOURCE[cpp_start:cpp_end]
    assert 'if os.name == "nt":' in cpp

    pas_start = SOURCE.index('def build_pascal_command')
    pas_end = SOURCE.index('def build_python_command', pas_start)
    pas = SOURCE[pas_start:pas_end]
    assert 'if os.name == "nt":' in pas


def test_tasks_uses_workspace_venv_python():
    tasks = Path(__file__).with_name('tasks.json').read_text(encoding='utf-8')
    assert '"${workspaceFolder}/.vscode/venv/bin/python"' in tasks
    assert '"TARGET_FILE": "${file}"' in tasks


def test_linux_memory_wrapper_exists_and_uses_child_rusage():
    wrapper = Path(__file__).with_name('memory_wrapper.py')
    assert wrapper.exists()
    source = wrapper.read_text(encoding='utf-8')
    assert 'resource.RUSAGE_CHILDREN' in source
    assert 'ru_maxrss' in source
    assert 'stats_path' in source
