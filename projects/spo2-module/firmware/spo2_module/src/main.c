#include <avr/io.h>
#include <util/delay.h>
#include "switches.h"
#include "max30102.h"
#include "ssd1306.h"
#include "uart.h"

#define MAX_THRESHOLD 0

void System_Init(void);

int main(){
    System_Init();
    while(1){
        if (switch_flag){
            switch_flag = false;
            if (!(switch_state & DOWN_VALUE)){ // logical negation because of pull-up resistors
                UART_printString("Hello");
                // change the state of the OLED (DOWN)
            }
            if (!(switch_state & UP_VALUE)){
                UART_printString("What's up!!");
                LED_On();
                // change the state of the OLED (UP)
            }
            if(!(switch_state & MENU_VALUE)){
                UART_printString("Goodbye!");
                LED_Off();
                // change the state of the OLED (MENU)
            }
        }
    }
}

void System_Init(){
    UART_Init();
    Switch_Init();
    MAX30102_Init();
    SSD1306_Init();
    _delay_ms(100); // wait for initializations to finish
}
