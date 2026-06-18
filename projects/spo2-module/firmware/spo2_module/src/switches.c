#include "switches.h"

void Switch_Init(){
    DDRD &= ~PD2_PD3_PD4_VALUE; // set PD2, PD3, PD4 as inputs
    PORTD &= ~PD2_PD3_PD4_VALUE; // disable pull-up resistors (external pull ups)

    PCICR |= PCIE2_EN; // enable pin change interrupts for PCINT16-23
    PCMSK2 |= PD2_PD3_PD4_VALUE; // enable pin change interrupt on PCINT18(PD2), PCINT19(PD3), PCINT20(PD4)

    sei(); // enable global interrupts
}

ISR(PCINT2_vect){
    switch_state = PIND & PD2_PD3_PD4_VALUE;
    switch_flag = true;
}