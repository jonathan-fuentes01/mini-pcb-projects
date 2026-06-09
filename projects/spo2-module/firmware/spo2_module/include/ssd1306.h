#ifndef SSD1306_H
#define SSD1306_H
#include<Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

extern const unsigned char PROGMEM hrt_rt_logo[]; 
#endif