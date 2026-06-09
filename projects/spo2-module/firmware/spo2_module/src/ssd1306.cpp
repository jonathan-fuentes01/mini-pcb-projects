#include "ssd1306.h"

Adafruit_SSD1306 screen_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const unsigned char PROGMEM hrt_rt_logo [] = {
  
}