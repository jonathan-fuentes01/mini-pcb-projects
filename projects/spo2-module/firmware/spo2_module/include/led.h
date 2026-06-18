#ifndef LED_H
#define LED_H
// HEADER INCLUDES
#include <avr/io.h>
// MACROS FOR LED INITIALIZATION
#define LED_PIN 0x10 // pin PB4
// FUNCTION PROTOTYPES
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
#endif