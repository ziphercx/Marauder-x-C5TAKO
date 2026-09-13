"""Merge the builder's actual flash images into one 8MB image for address 0x0."""
from pathlib import Path
import subprocess
from SCons.Script import Import

Import("env")


def merge_c5tako(target, source, env):
    build = Path(env.subst("$BUILD_DIR"))
    output = Path(env.subst("$PROJECT_DIR")) / "Marauder-c5tako-8MB-merged.bin"
    command = [env.subst("$PYTHONEXE"), "-m", "esptool", "--chip", "esp32c5",
               "merge-bin", "--pad-to-size", "8MB", "-o", str(output)]
    for offset, filename in env.get("FLASH_EXTRA_IMAGES", []):
        command.extend((str(offset), env.subst(str(filename))))
    command.extend((env.subst("$ESP32_APP_OFFSET"), str(build / "firmware.bin")))
    subprocess.check_call(command)
    assert output.stat().st_size == 8 * 1024 * 1024
    print(f"[C5TAKO] {output}; flash at 0x0")


env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", merge_c5tako)
