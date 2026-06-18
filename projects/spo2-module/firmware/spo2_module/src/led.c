#include "led.h"

void LED_Init(){
    DDRB |= LED_PIN; // set LED pin as output
    PORTB &= ~LED_PIN; // disable pull-up resistors
}

void LED_On(){
    PORTB |= LED_PIN;
}

void LED_Off(){
    PORTB &= ~LED_PIN;
}

void LED_Toggle(){
    PORTB ^= LED_PIN;
}