// Simplified ST7789 video implementation for Raspberry Pi Pico
// Based on Chocolate Doom but adapted for a 240x240 SPI display.

#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

#include "i_video.h"
#include "v_video.h"
#include "magc.h"

static uint8_t framebuffer[SCREENWIDTH * SCREENHEIGHT];
pixel_t *I_VideoBuffer = framebuffer;
static uint16_t palette16[256];

static inline void display_write_command(uint8_t cmd) {
    gpio_put(DISPLAY_PIN_DC, 0);
    gpio_put(DISPLAY_PIN_CS, 0);
    spi_write_blocking(DISPLAY_SPI_PORT, &cmd, 1);
    gpio_put(DISPLAY_PIN_CS, 1);
}

static inline void display_write_data(const uint8_t *data, size_t len) {
    if (!len) return;
    gpio_put(DISPLAY_PIN_DC, 1);
    gpio_put(DISPLAY_PIN_CS, 0);
    spi_write_blocking(DISPLAY_SPI_PORT, data, len);
    gpio_put(DISPLAY_PIN_CS, 1);
}

static void display_set_address(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t buf[4];
    display_write_command(DCS_SET_COLUMN_ADDRESS);
    buf[0] = x0 >> 8; buf[1] = x0 & 0xff; buf[2] = x1 >> 8; buf[3] = x1 & 0xff;
    display_write_data(buf, 4);
    display_write_command(DCS_SET_PAGE_ADDRESS);
    buf[0] = y0 >> 8; buf[1] = y0 & 0xff; buf[2] = y1 >> 8; buf[3] = y1 & 0xff;
    display_write_data(buf, 4);
    display_write_command(DCS_WRITE_MEMORY_START);
}

void I_InitGraphics(void) {
    spi_init(DISPLAY_SPI_PORT, DISPLAY_SPI_CLOCK_SPEED_HZ);
    gpio_set_function(DISPLAY_PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(DISPLAY_PIN_CLK, GPIO_FUNC_SPI);
    gpio_init(DISPLAY_PIN_CS); gpio_set_dir(DISPLAY_PIN_CS, GPIO_OUT); gpio_put(DISPLAY_PIN_CS, 1);
    gpio_init(DISPLAY_PIN_DC); gpio_set_dir(DISPLAY_PIN_DC, GPIO_OUT);
    gpio_init(DISPLAY_PIN_RST); gpio_set_dir(DISPLAY_PIN_RST, GPIO_OUT);
    gpio_put(DISPLAY_PIN_RST, 0); sleep_ms(50); gpio_put(DISPLAY_PIN_RST, 1); sleep_ms(50);
    gpio_init(DISPLAY_PIN_BL); gpio_set_dir(DISPLAY_PIN_BL, GPIO_OUT); gpio_put(DISPLAY_PIN_BL, 1);

    display_write_command(DCS_EXIT_SLEEP_MODE);
    sleep_ms(120);
    display_write_command(DCS_SET_ADDRESS_MODE);
    uint8_t mode = DISPLAY_ADDRESS_MODE;
    display_write_data(&mode, 1);
    display_write_command(DCS_SET_PIXEL_FORMAT);
    uint8_t fmt = DISPLAY_PIXEL_FORMAT;
    display_write_data(&fmt, 1);
    display_write_command(DCS_SET_DISPLAY_ON);
    sleep_ms(20);

    display_set_address(0, DISPLAY_TOP_OFFSET, DISPLAY_WIDTH - 1, DISPLAY_TOP_OFFSET + SCREENHEIGHT - 1);
}

void I_ShutdownGraphics(void) {
    display_write_command(DCS_SET_DISPLAY_ON);
}

void I_SetPalette(should_be_const byte* pal) {
    for (int i = 0; i < 256; ++i) {
        uint8_t r = pal[0];
        uint8_t g = pal[1];
        uint8_t b = pal[2];
        palette16[i] = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
        pal += 3;
    }
}

void I_FinishUpdate(void) {
    uint16_t line[DISPLAY_WIDTH];
    int x_off = (SCREENWIDTH - DISPLAY_WIDTH) / 2;
    for (int y = 0; y < SCREENHEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
            line[x] = palette16[I_VideoBuffer[y * SCREENWIDTH + x + x_off]];
        }
        display_write_data((uint8_t *) line, DISPLAY_WIDTH * 2);
    }
}

void I_UpdateNoBlit(void) {}

void I_ReadScreen(pixel_t* scr) { memcpy(scr, I_VideoBuffer, SCREENWIDTH * SCREENHEIGHT); }

void I_BeginRead(void) {}

void I_StartFrame(void) {}

void I_StartTic(void) {}

void I_EnableLoadingDisk(int x, int y) {}

void I_SetWindowTitle(const char *title) {}
void I_GraphicsCheckCommandLine(void) {}
void I_SetGrabMouseCallback(grabmouse_callback_t func) {}
void I_DisplayFPSDots(boolean dots_on) {}
void I_BindVideoVariables(void) {}
void I_InitWindowTitle(void) {}
void I_InitWindowIcon(void) {}
void I_CheckIsScreensaver(void) {}
int I_GetPaletteIndex(int r, int g, int b) { return 0; }
boolean screensaver_mode = false;
boolean screenvisible = true;
int screen_width = SCREENWIDTH;
int screen_height = SCREENHEIGHT;
int fullscreen = 0;
int aspect_ratio_correct = 0;
int integer_scaling = 0;
int vga_porch_flash = 0;
int force_software_renderer = 1;
should_be_const constcharstar window_position = NULL;
unsigned int joywait = 0;
*** End
