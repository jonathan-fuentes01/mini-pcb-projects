#ifndef SSD1306_H
#include <stdint.h>
#include <avr/io.h>
#define SSD1306_H
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

extern const unsigned char hrt_rt_logo[]; 
#endif