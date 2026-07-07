#include "ssd1306.h"


const unsigned char hrt_rt_logo[] = {
  
};

void SSD1306_Init(){
    SSD1306_Command(DISPLAY_OFF); 

    SSD1306_Command(SET_CHARGE_PUMP);
    SSD1306_Command(ENABLE_CHARGE_PUMP);

    SSD1306_Command(SET_DISPLAY_CLOCK);
    SSD1306_Command(DISPLAY_CLOCK); // refer to macro

    SSD1306_Command(SET_MULTIPLEX_RATIO);
    SSD1306_Command(MULTIPLEX_RATIO); // refer to macro
    
    SSD1306_Command(SET_MEMORY_ADDRESSING_MODE);
    SSD1306_Command(HORIZONTAL_ADDRESSING_MODE);

    SSD1306_Command(SET_COM_PINS);
    SSD1306_Command(COM_PINS); // refer to macro

    SSD1306_Command(SET_DISPLAY_MODE);
    SSD1306_Command(NORMAL_DISPLAY);

    SSD1306_Command(DISPLAY_ON);
}

void SSD1306_Command(uint8_t command){
    uint8_t status;
    MAX30102_Start(); 
    status = MAX30102_Write(SSD1306_SLA_W); // slave write address
    if (status != TWI_SLA_W_ACK){ // check status code for acknowledgement of write mode
        MAX30102_Stop();
    }
    MAX30102_Write(SSD1306_COMMAND);
    MAX30102_Write(command);
    MAX30102_Stop();
}

void SSD1306_Data(uint8_t data){
    uint8_t status;
    MAX30102_Start(); 
    status = MAX30102_Write(SSD1306_SLA_W); // slave write address
    if (status != TWI_SLA_W_ACK){ // check status code for acknowledgement of write mode
        MAX30102_Stop();
    }
    MAX30102_Write(SSD1306_DATA);
    MAX30102_Write(data);
    MAX30102_Stop();
}