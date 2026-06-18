#ifndef UART_H
#define UART_H
// HEADER INCLUDES
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
// MACROS FOR INITIALIZATION
#define DOUBLE_TRANSMISSION_RATE 0x02
#define BAUD_RATE 115200
#define UBRR0H_VALUE 0x00 // upper bits of UBRR0
#define UBRR0L_VALUE 0x10 // select 115200 baud rate (using 16 MHz clock)
#define UDRE0_VALUE 0x20 // bit 5 of UCSR0A
#define TXEN_VALUE 0x08 // bit 3 of UCSR0B
#define MODE_SELECT 0x06 // set UCSZ01 & UCSZ00 bits (8-bit mode), 1 stop bit, and no parity
// FUNCTION PROTOTYPES
void UART_Init(void);
void UART_sendChar(char data);
void UART_printString(const char *s);
#endif