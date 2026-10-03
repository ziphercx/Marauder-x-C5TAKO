# C5TAKO / XIAO ESP32-C5

Build with `pio run -e c5tako`. The post-build step creates
`Marauder-c5tako-8MB-merged.bin`, a complete 8MB image to flash at **0x0**.
Use `pio run -e c5tako -t upload` for direct PlatformIO upload.

The port uses Arduino 3.3.11 and the C5-capable TFT_eSPI 2.5.43 sources copied
from the working Bruce C5TAKO port. Only library runtime files are included;
upstream examples and tools are omitted. Original TFT_eSPI license is retained.
The older Arduino-layout libraries remain separate from the PIO environment.
NimBLE is pinned to 2.5.1, which includes the upstream C5/C6 compatibility fix
for Arduino 3.3.11; see the [release notes](https://github.com/h2zero/NimBLE-Arduino/releases/tag/2.5.1).

Supported carrier hardware: ST7789 240x240 without touch, five active-low
buttons, shared SPI SD card, 8MB PSRAM, and battery ADC with switched divider.
CC1101, buzzer, GPS, and addressable LEDs are not enabled. The unused CC1101
is deselected because it shares the display/SD bus; the buzzer is held low.

| Signal | GPIO |
| --- | --- |
| SPI SCK / MOSI / MISO | 8 / 10 / 9 |
| TFT CS / DC / reset / backlight | 7 / 1 / none / 25 |
| SD CS | 5 |
| Up / Down / Left / Right / OK | 24 / 28 / 23 / 0 / 4 |
| Battery ADC / divider enable | 6 / 26 |

Pin and display definitions live in `esp32_marauder/configs_c5tako.h` and
`User_Setup_c5tako.h`. The existing Mini menu rendering is reused at 240x240.
USB CDC waiting is bounded so the carrier can boot without a USB host.

The 240x240 layout shows eight menu rows with 2x bitmap text. Titles and the
16-pixel status bar use 2x bitmap text and the original Mini status colors. Logs
and other centered messages use 1x text; logs start below the title and use
sixteen 12-pixel rows. The status bar keeps the Mini GPS indicator conditional:
it appears only when GPS support is configured and a module responds. This
carrier has no GPS wiring, so no indicator is shown. Up/Down select menu rows or
change scan channels, OK selects or exits scans, and Right toggles channel
hopping in applicable scans. The Mini button keyboard handles SSIDs, passwords,
and geofence text. Packet
Monitor and Recon draw the upstream Mini v3 128x128 layout into a sprite, then
scale it to the 240x240 panel without changing the source colors or positions.
Recon keeps the C5TAKO status bar at the top. The Packet Monitor key hint is
hidden because the C5TAKO button mapping differs from Mini v3. Other scan views
use the shared Mini renderer with the C5TAKO screen geometry.
Geometry stays in `configs_c5tako.h`; the shared rendering hooks are guarded
by `MARAUDER_C5TAKO`. Preserve those hooks when merging upstream updates and
run the build to check the compile-time layout bounds. Upstream changes to
the shared functions can still require merge conflict resolution.

The display and SD use the same `SPI` instance. Do not copy `SPIClass` into a
global object: initialization order can copy its mutex before construction,
causing `xQueueSemaphoreTake` to assert in SD's `beginTransaction()` at boot.

Run `python tools/test_c5tako_hardware.py` to check wiring and the merged
bootloader/partition/application offsets. A successful build does not verify
physical display colors, orientation, buttons, SD, battery readings, or radio
behavior; those need checking on the carrier.
