#include "uart.h"

void UART_Init(void){
    UCSR0A |= DOUBLE_TRANSMISSION_RATE; // double transmission rate (8 instead of 16 divisor)
    UBRR0H = UBRR0H_VALUE; // upper half of UBRR value
    UBRR0L = UBRR0L_VALUE; // lower half of UBRR value
    UCSR0B = TXEN_VALUE; // enable just transmit (only transmit needed for the project)
    UCSR0C = MODE_SELECT; // 8-bit mode, no parity, one stop bit
}

void UART_sendChar(char data){
    while (!(UCSR0A & UDRE0_VALUE));
    UDR0 = data;
}

void UART_printString(const char *s){
    while(*s){
        UART_sendChar(*s++); // iterate through the string and print
    }
}