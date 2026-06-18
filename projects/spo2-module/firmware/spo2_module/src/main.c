#include <avr/iom328p.h>
#include <util/delay.h>
#include "switches.h"
#include "max30102.h"
#include "ssd1306.h"

void System_Init(void);

void main(){
    System_Init();
    while(1){
        if (switch_flag){
            switch_flag = false;
            if (switch_state & DOWN_VALUE){
                // change the state of the OLED (DOWN)
            }
            if (switch_state & UP_VALUE){
                // change the state of the OLED (UP)
            }
            if(switch_state & MENU_VALUE){
                // change the state of the OLED (MENU)
            }
        }
    }
}

void System_Init(){
    Switch_Init();
    MAX30102_Init();
    SSD1306_Init();
    _delay_ms(100); // delay 100 ms for inits
}
