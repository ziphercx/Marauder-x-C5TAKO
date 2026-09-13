"""Check the carrier wiring and, when present, the flash-at-zero image."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def defines(path):
    return dict(re.findall(r"^#define\s+(\w+)\s+(-?\d+)\s*$", path.read_text(), re.M))


if __name__ == "__main__":
    board = defines(ROOT / "esp32_marauder/configs_c5tako.h")
    display = defines(ROOT / "User_Setup_c5tako.h")
    assert {key: int(board[key]) for key in ("U_BTN", "D_BTN", "L_BTN", "R_BTN", "C_BTN")} == {
        "U_BTN": 24, "D_BTN": 28, "L_BTN": 23, "R_BTN": 0, "C_BTN": 4}
    assert int(board["SD_CS"]) == 5
    assert int(board["BATTERY_ADC_PIN"]) == 6
    assert int(board["BATTERY_ADC_ENABLE_PIN"]) == 26
    assert {key: int(display[key]) for key in ("TFT_CS", "TFT_DC", "TFT_RST", "TFT_BL", "TFT_SCLK", "TFT_MOSI", "TFT_MISO")} == {
        "TFT_CS": 7, "TFT_DC": 1, "TFT_RST": -1, "TFT_BL": 25, "TFT_SCLK": 8, "TFT_MOSI": 10, "TFT_MISO": 9}
    merged = ROOT / "Marauder-c5tako-8MB-merged.bin"
    if merged.exists():
        image = merged.read_bytes()
        assert len(image) == 8 * 1024 * 1024
        build = ROOT / ".pio/build/c5tako"
        for offset, name in ((0x2000, "bootloader.bin"), (0x8000, "partitions.bin"), (0x10000, "firmware.bin")):
            part = (build / name).read_bytes()
            assert image[offset:offset + len(part)] == part, name
        assert image[0x2000] == image[0x10000] == 0xE9
        assert image[0x2003] >> 4 == 3, "Bootloader must declare 8MB flash"
        factory = (build / "firmware.factory.bin").read_bytes()
        assert image[:len(factory)] == factory, "Include the builder's OTA boot_app0 image"
    print("C5TAKO wiring and available merged image: OK")
