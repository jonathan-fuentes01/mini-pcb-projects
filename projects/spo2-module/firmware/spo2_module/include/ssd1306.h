#ifndef SSD1306_H
#define SSD1306_H
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
void SSD1306_Init(void);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
extern const unsigned char hrt_rt_logo[]; 

#endif