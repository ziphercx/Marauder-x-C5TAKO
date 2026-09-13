#pragma once

// Same ST7789 panel and wiring as the working Bruce C5TAKO port.
#define ST7789_DRIVER
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#define CGRAM_OFFSET
#define TFT_RGB_ORDER TFT_RGB
#define TFT_INVERSION_ON
#define TFT_CS 7
#define TFT_DC 1
#define TFT_RST -1
#define TFT_BL 25
#define TFT_BACKLIGHT_ON HIGH
#define TFT_SCLK 8
#define TFT_MOSI 10
#define TFT_MISO 9
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 20000000
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_GFXFF
#define SMOOTH_FONT
