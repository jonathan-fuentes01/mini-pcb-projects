#ifndef SSD1306_H
#define SSD1306_H
// HEADER INCLUDES
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "max30102.h"
// MACROS
#define ASCII_PIXEL_WIDTH 5 // pixel width of each character
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 8) // size of the full screen
#define SSD1306_COMMAND 0x00 // write a command to the display (Co, D/C#, followed by six 0's) D/C# set to 0
#define SSD1306_DATA 0x40 // write data to the display (Co, D/C#, followed by six 0's) D/C# set to 1
#define SSD1306_SLA_W 0x78 // 0x3C << 0 ([I2C Slave Address][W Bit]) (full-byte)
#define SSD1306_SLA_R 0x79 // 0x3C << 1 ([I2C Slave Address][R Bit]) (full-byte)
#define DISPLAY_CLOCK 0x80 // oscillator setting of 8 and divide ratio of 1
#define MULTIPLEX_RATIO 0x1F // 32 - 1 = 31 (Screen Height) 31 vertical rows
#define NO_OFFSET 0x00 // for display offset command
#define HORIZONTAL_ADDRESSING_MODE 0x00 // horizontal addressing mode
#define PAGE_ADDRESSING_MODE 0x02 // page addressing mode
#define COM_PINS 0x02 // sequential COM config, disable COM left/right remap, bit 1 (reserved)
#define ENABLE_CHARGE_PUMP 0x14 // enable charge pump
#define DISPLAY_START_LINE 0x40 // set display start line
#define CONTRAST 0x7F // Contrast
#define PAGE_ADDRESS_START 0xB0 // start of the page address
#define SET_LOWER_COLUMN 0x00 // start of lower column address
#define SET_UPPER_COLUMN 0x10 // start of upper column address
// COMMAND TABLE
#define ENTIRE_DISPLAY_ON 0xA5 // will turn on the display regardless of contents of display data RAM
#define DISPLAY_ON 0xAF // command for turning on the display
#define DISPLAY_OFF 0xAE // command for turning off the display
#define SET_DISPLAY_MODE 0xA4 // command for enabling display outputs
#define NORMAL_DISPLAY 0xA6 // command for normal display
#define INVERSE_DISPLAY 0xA7 // command for inverse display
#define SET_MEMORY_ADDRESSING_MODE 0x20 // command for setting memory addressing mode 
#define SET_MULTIPLEX_RATIO 0xA8 // command for switching the multiplexing mode
#define SET_DISPLAY_OFFSET 0xD3 // command for setting display offset
#define SET_DISPLAY_CLOCK 0xD5 // command for setting oscillator frequency
#define SET_PRECHARGE_PERIOD 0xD9 // command for setting the duration of precharge period
#define SET_COLUMN_ADDRESS 0x21 // command for setting the start, end, and start address of a column
#define SET_PAGE_ADDRESS 0x22 // command for setting the page address
#define SET_DISPLAY_START_LINE 0x40 // command for setting the starting address of the display (0-60, 0x40-0x7F)
#define NO_OPERATION_CMD 0xE3 // command for no operation
#define SET_COM_PINS 0xDA // command for setting COM pins
#define COM_OUTPUT_SCAN_DIRECTION 0xC8 // command for setting scan direction of COM output (C0 sets from COM0 to COM63) 
#define SET_CHARGE_PUMP 0x8D // command for setting charge bump
#define SEGMENT_REMAPPING 0xA1 // command for segment remapping (characters are good now)
#define NORMAL_SEGMENT_MAP 0xA0 // command for normal segment mapping
#define SET_CONTRAST_CONTROL 0x81 // command to set the contrast
// SSD1306 Registers
#define SCREEN_ADDRESS 0x3C // 7-bit slave address
// BITMAPS
extern const uint8_t heart_rate[];
extern const uint8_t ASCII[][ASCII_PIXEL_WIDTH]; 
// FUNCTION PROTOTYPES
void SSD1306_Init(void);
void SSD1306_Command(uint8_t command);
void SSD1306_Data(uint8_t data);
void SSD1306_Clear(void);
void SSD1306_ClearLine(uint8_t y);
void SSD1306_SetCursor(uint8_t x, uint8_t y);
void SSD1306_DrawChar(char c);
void SSD1306_DrawString(const char *str);
void SSD1306_DrawBitmap(const uint8_t *bitmap);
#endif