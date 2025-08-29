#ifndef __I_MAGC__
#define __I_MAGC__

#include "pico.h"

// Display command codes
#define DCS_SOFT_RESET                 0x01
#define DCS_EXIT_SLEEP_MODE            0x11
#define DCS_EXIT_INVERT_MODE           0x20
#define DCS_ENTER_INVERT_MODE          0x21
#define DCS_SET_DISPLAY_ON             0x29
#define DCS_SET_COLUMN_ADDRESS         0x2A
#define DCS_SET_PAGE_ADDRESS           0x2B
#define DCS_WRITE_MEMORY_START         0x2C
#define DCS_SET_ADDRESS_MODE           0x36
#define DCS_SET_PIXEL_FORMAT           0x3A
#define DCS_WRITE_DISPLAY_BRIGHTNESS   0x51
#define DCS_GAMMA_SET                  0x26

// Pixel formats
#define DCS_PIXEL_FORMAT_16BIT         0x55
#define DCS_PIXEL_FORMAT_8BIT          0x22

// Address mode flags
#define DCS_ADDRESS_MODE_MIRROR_Y      0x80
#define DCS_ADDRESS_MODE_MIRROR_X      0x40
#define DCS_ADDRESS_MODE_SWAP_XY       0x20
#define DCS_ADDRESS_MODE_BGR           0x08
#define DCS_ADDRESS_MODE_RGB           0x00
#define DCS_ADDRESS_MODE_FLIP_X        0x02

// ST7789 display settings
#define DISPLAY_SPI_PORT spi0
#define DISPLAY_SPI_CLOCK_SPEED_HZ 63000000
#define DISPLAY_PIXEL_FORMAT DCS_PIXEL_FORMAT_16BIT
#define DISPLAY_ADDRESS_MODE (DCS_ADDRESS_MODE_RGB | DCS_ADDRESS_MODE_SWAP_XY | DCS_ADDRESS_MODE_MIRROR_Y)
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240
#define DISPLAY_OFFSET_X 0
#define DISPLAY_OFFSET_Y 0

// Display pins
#define DISPLAY_PIN_CS   21
#define DISPLAY_PIN_RST  20
#define DISPLAY_PIN_MOSI 19
#define DISPLAY_PIN_CLK  18
#define DISPLAY_PIN_DC   17
#define DISPLAY_PIN_BL   16

// Audio PWM pins
#define AUDIO_PIN_L 15
#define AUDIO_PIN_R 14
#define PICO_AUDIO_PWM_L_PIN AUDIO_PIN_L
#define PICO_AUDIO_PWM_R_PIN AUDIO_PIN_R

// Button pins
#define PIN_RT 2
#define PIN_LT 3
#define PIN_UP 4
#define PIN_DN 5
#define PIN_SL 6
#define PIN_ST 7
#define PIN_A 8
#define PIN_B 9

#endif // __I_MAGC__
