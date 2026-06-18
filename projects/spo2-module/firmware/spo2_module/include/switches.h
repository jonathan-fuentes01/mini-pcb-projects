#ifndef SWITCHES_H
#define SWITCHES_H
// HEADER INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
// FLAGS FOR ISR
volatile uint8_t switch_state;
volatile bool switch_flag;
// MACROS FOR SWITCH INITIALIZATION
#define DOWN_VALUE 0x04
#define UP_VALUE 0x08
#define MENU_VALUE 0x10
#define PD2_PD3_PD4_VALUE 0x1C
#define PCIE2_EN 0x04
// FUNCTION PROTOTYPE
void Switch_Init(void);
#endif