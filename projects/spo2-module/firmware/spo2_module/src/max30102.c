#include "max30102.h"

void MAX30102_Init(){
    DDRC &= ~PC4_PC5_VALUE; // set pins A4, A5 as inputs 
    PORTC |= PC4_PC5_VALUE; // enable pull ups on A4, A5
    TWSR = TWSR_VALUE; // *1 (prescaler) 
    TWBR = TWBR_VALUE; // 72 = 100kHz
    TWCR |= TWI_EN; // enable TWI
}

void MAX30102_Start(){
    TWCR |= TWCR_START; // start TWI
    TWCR |= TWINT_CLEAR; // to clear TWINT set the bit to 1
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear
}

void MAX30102_Stop(){
    TWCR = TWCR_STOP; // clear every other bit and set it to stop
}

uint8_t MAX30102_Write(uint8_t data){
    TWDR = data; // write data to the register
    TWCR = (TWINT_CLEAR | TWI_EN); 
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear

    return TWSR&0xF8; // return only bits 7-3 (status bits)
}

uint8_t MAX30102_ReadNack(void){
    TWCR = (TWINT_CLEAR | TWI_EN);
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear
    return TWDR; 
}

bool MAX30102_WriteReg(uint8_t reg, uint8_t data){
    uint8_t status;

    MAX30102_Start(); 
    
    status = MAX30102_Write(MAX30102_SLA_W); // slave write address pg. 29
    if (status != TWI_SLA_W_ACK){ // check status code for ACK at MAX30102 write address
        MAX30102_Stop();
        return false;
    }
    status = MAX30102_Write(reg); // write to register first to determine what value it needs to put there
    if (status != TWI_DATA_ACK){ // check to see if data was transmitted
        MAX30102_Stop();
        return false;
    }
    status = MAX30102_Write(data); // write to register first to determine what value it needs to put there
    if (status != TWI_DATA_ACK){ // check to see if data was transmitted
        MAX30102_Stop();
        return false;
    }

    MAX30102_Stop();
    return true;
}

bool MAX30102_ReadReg(uint8_t reg, uint8_t *data){
    uint8_t status;

    MAX30102_Start();

    status = MAX30102_Write(MAX30102_SLA_W); // slave write address pg. 29
    if (status != TWI_SLA_W_ACK){ // check status code for ACK at MAX30102 write address
        MAX30102_Stop();
        return false;
    }
    status = MAX30102_Write(reg); // write to register first to determine what value it needs to put there
    if (status != TWI_DATA_ACK){ // check to see if data was transmitted
        MAX30102_Stop();
        return false;
    }
    
    MAX30102_Start();

    status = MAX30102_Write(MAX30102_SLA_R); // slave read address pg. 29
    if (status != TWI_SLA_R_ACK){
        MAX30102_Stop();
        return false;
    }

    *data = MAX30102_ReadNack();

    MAX30102_Stop();
    return true;
}