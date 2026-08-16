#!/usr/bin/env python3
"""Transparent Linux child launcher with exact peak-RSS reporting."""

import resource
import subprocess
import sys
import threading
from pathlib import Path


def _forward(source, destination):
    try:
        while True:
            chunk = source.read(65536)
            if not chunk:
                return
            destination.write(chunk)
            destination.flush()
    finally:
        try:
            source.close()
        except Exception:
            pass


def main() -> int:
    if len(sys.argv) < 3:
        print("memory_wrapper: missing stats path or command", file=sys.stderr)
        return 2

    stats_path = Path(sys.argv[1])
    command = sys.argv[2:]

    try:
        child = subprocess.Popen(
            command,
            stdin=sys.stdin.buffer,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            close_fds=True,
        )
    except OSError as exc:
        print(f"memory_wrapper: failed to start child: {exc}", file=sys.stderr)
        return 127

    stdout_thread = threading.Thread(
        target=_forward, args=(child.stdout, sys.stdout.buffer), daemon=True
    )
    stderr_thread = threading.Thread(
        target=_forward, args=(child.stderr, sys.stderr.buffer), daemon=True
    )
    stdout_thread.start()
    stderr_thread.start()

    return_code = child.wait()
    stdout_thread.join()
    stderr_thread.join()

    # Linux reports ru_maxrss in KiB. This is the maximum RSS of the waited
    # child, not the wrapper itself, so it remains correct for very short runs.
    usage = resource.getrusage(resource.RUSAGE_CHILDREN)
    peak_rss_bytes = int(usage.ru_maxrss) * 1024

    try:
        stats_path.write_text(str(peak_rss_bytes), encoding="ascii")
    except OSError:
        pass

    return return_code


if __name__ == "__main__":
    raise SystemExit(main())
