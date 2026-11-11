#pragma once

// XIAO ESP32-C5 carrier: reuse Marauder's button-driven screen and shared SPI SD.
#define HAS_BT
#define HAS_BT_REMOTE
#define HAS_SCREEN
#define HAS_MINI_SCREEN
#define HAS_BUTTONS
#define HAS_MINI_KB
#define HAS_BATTERY
#define BATTERY_ADC_PIN 6
#define BATTERY_ADC_ENABLE_PIN 26
#define HAS_SD
#define HAS_C5_SD
#define USE_SD
#define HAS_DUAL_BAND
#define HAS_PSRAM
#define HAS_NIMBLE_2
#define HAS_IDF_3
#define HAS_DIRECT_UPLOAD
#define HAS_CSI_MOTION
#define HAS_CSI_BUTTON_CONTROLS
#define HAS_TEMP_SENSOR

#define L_BTN 23
#define C_BTN 4
#define U_BTN 24
#define R_BTN 0
#define D_BTN 28
#define HAS_L
#define HAS_C
#define HAS_U
#define HAS_R
#define HAS_D
#define L_PULL true
#define C_PULL true
#define U_PULL true
#define R_PULL true
#define D_PULL true

#define SD_CS 5
#define SD_MISO TFT_MISO
#define SD_MOSI TFT_MOSI
#define SD_SCK TFT_SCLK

// Button screen geometry follows Marauder Mini, resized for 240x240.
#define CHAN_PER_PAGE 7
#define SCREEN_CHAR_WIDTH 40
#define SCREEN_BUFFER
#define MAX_SCREEN_BUFFER ((TFT_HEIGHT - TOP_FIXED_AREA) / TEXT_HEIGHT)
#define BANNER_TEXT_SIZE 2
#define GRAPH_VERT_LIM (TFT_HEIGHT / 2 - 1)
#define EXT_BUTTON_WIDTH 0
#define SCREEN_ORIENTATION 0
#define CHAR_WIDTH 6
#define SCREEN_WIDTH TFT_WIDTH
#define SCREEN_HEIGHT TFT_HEIGHT
#define HEIGHT_1 TFT_WIDTH
#define WIDTH_1 TFT_WIDTH
#define STANDARD_FONT_CHAR_LIMIT (TFT_WIDTH / CHAR_WIDTH)
#define TEXT_HEIGHT 12
#define BOT_FIXED_AREA 0
#define TOP_FIXED_AREA 48
#define YMAX TFT_HEIGHT
#define minimum(a,b) (((a) < (b)) ? (a) : (b))
#define MENU_FONT &FreeMono9pt7b
#define BUTTON_SCREEN_LIMIT ((TFT_HEIGHT - TOP_FIXED_AREA) / (KEY_H + KEY_SPACING_Y))
#define BUTTON_ARRAY_LEN BUTTON_SCREEN_LIMIT
#define STATUS_BAR_WIDTH 16
#define LVGL_TICK_PERIOD 6
#define FRAME_X 60
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W / 2)
#define REDBUTTON_H FRAME_H
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W / 2)
#define GREENBUTTON_H FRAME_H
#define STATUSBAR_COLOR 0x4A49

#define BANNER_TIME 50
#define COMMAND_PREFIX "!"
#define KEY_X (TFT_WIDTH / 2)
#define KEY_Y (TOP_FIXED_AREA + KEY_H / 2)
#define KEY_W TFT_WIDTH
#define KEY_H 23
#define KEY_SPACING_X 0
#define KEY_SPACING_Y 1
#define KEY_TEXTSIZE 2
#define ICON_W 22
#define ICON_H 22
#define BUTTON_PADDING 10

static_assert(STATUS_BAR_WIDTH + 8 * BANNER_TEXT_SIZE <= TOP_FIXED_AREA, "Banner overlaps content");
static_assert(TOP_FIXED_AREA + BUTTON_SCREEN_LIMIT * (KEY_H + KEY_SPACING_Y) <= TFT_HEIGHT, "Menu exceeds screen");
static_assert(TOP_FIXED_AREA + MAX_SCREEN_BUFFER * TEXT_HEIGHT <= TFT_HEIGHT, "Log exceeds screen");
