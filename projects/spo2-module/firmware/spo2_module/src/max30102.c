#include "max30102.h"

void MAX30102_Init(){
    DDRC &= ~PC4_PC5_VALUE; // set pins A4, A5 as inputs 
    PORTC |= PC4_PC5_VALUE; // enable pull ups on A4, A5
    TWSR = TWSR_VALUE; // *1 (prescaler) 
    TWBR = TWBR_VALUE; // 72 = 100kHz
    TWCR |= TWI_EN; // enable TWI
}

void MAX30102_Start(){
    TWCR = TWINT_CLEAR | TWCR_START | TWI_EN ; // start TWI, to clear TWINT set the bit to 1
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear
}

void MAX30102_Stop(){
    TWCR = TWINT_CLEAR | TWCR_STOP | TWI_EN; // clear every other bit and set it to stop
}

uint8_t MAX30102_Write(uint8_t data){
    TWDR = data; // write data to the register
    TWCR = (TWINT_CLEAR | TWI_EN); 
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear

    return TWSR&0xF8; // return only bits 7-3 (status bits)
}

uint8_t MAX30102_ReadAck(void){
    TWCR = (TWINT_CLEAR | TWI_EN | TWI_ACK);
    while (!(TWCR & TWINT_CLEAR)); // wait for the bit to clear
    return TWDR; 
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

    *data = MAX30102_ReadNack(); // read last byte

    MAX30102_Stop();
    return true;
}

bool MAX30102_ReadBytes(uint8_t reg, uint8_t *data, uint8_t length){
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

    // reading for the length of the bytes
    for(uint8_t i = 0; i < length; i++){
        if(i == length - 1){
            data[i] = MAX30102_ReadNack(); // last byte
        }
        else{
            data[i] = MAX30102_ReadAck();
        }
    }

    MAX30102_Stop();
    return true;
}

bool MAX30102_ReadFIFO(uint32_t *red, uint32_t *ir){
    uint8_t fifo_data[6];

    if(!MAX30102_ReadBytes(MAX30102_FIFO_DATA_REG, fifo_data, SPO2_DATA_LENGTH)){
        return false; // if read fails
    }

    // the LED samples are on bytes 0-2 respectively, so store them in order 0, 1, 2
    // same thing for IR sensor
    *red = (fifo_data[2] | (uint32_t) fifo_data[1] << 8 | (uint32_t) fifo_data[0] << 16);
    *ir = (fifo_data[5] | (uint32_t) fifo_data[4] << 8 | (uint32_t) fifo_data[3] << 16);

    *red &= ADC_18_BIT_LENGTH;
    *ir &= ADC_18_BIT_LENGTH;

    return true;
}

bool MAX30102_Setup(){
    // reset sensor
    if (!MAX30102_WriteReg(MAX30102_MODE_CONFIG, MAX30102_MODE_RESET)){
        return false;
    }
    _delay_ms(100);
    // reset write pointer
    if (!MAX30102_WriteReg(MAX30102_FIFO_WR_PTR, MAX30102_PTR_RESET)){
        return false;
    }
    // reset read pointer
    if(!MAX30102_WriteReg(MAX30102_FIFO_READ_PTR, MAX30102_PTR_RESET)){
        return false;
    }
    // reset overflow counter pointer
    if(!MAX30102_WriteReg(MAX30102_OVERFLOW_COUNT, MAX30102_PTR_RESET)){
        return false;
    }
    // FIFO configuration
    if (!MAX30102_WriteReg(MAX30102_FIFO_CONFIG, MAX30102_FIFO_CONFIG_VALUE)){
        return false;
    }
    // SPO2 mode select
    if(!MAX30102_WriteReg(MAX30102_MODE_CONFIG, SPO2_MODE)){
        return false;
    }
    // SPO2 ADC configuration
    if(!MAX30102_WriteReg(MAX30102_SP02_CONFIG, SPO2_ADC_VALUE)){
        return false;
    }
    // LED current configuration
    if(!MAX30102_WriteReg(MAX30102_LED1, LED_CURRENT_VALUE)){
        return false;
    }
    if(!MAX30102_WriteReg(MAX30102_LED2, LED_CURRENT_VALUE)){
        return false;
    }

    return true;
}