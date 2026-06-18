#ifndef MAX30201_H
#define MAX30201_H

// HEADER INCLUDES
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
// MACROS FOR TWI & INITIALIZATION
#define PC4_PC5_VALUE 0x30
#define MAX30102_ADDRESS 0x57 // i2c address for the at328p (0b1010111) pg. 29 of datasheet
#define MAX30102_SLA_W 0xAE // write address for MAX30201
#define MAX30102_SLA_R 0xAF // read address for MAX30201
#define TWSR_VALUE 0x0 // prescaler value of 00 on bit 0,1 enables prescaler value * 1
#define TWBR_VALUE 72 // 100kHz standard mode for max30102
#define TWI_EN 0x04 // TWEN is the bit 2, set high to enable TWI
#define TWINT_CLEAR 0x80// clear bit 7 (TWINT)
#define TWCR_START 0x20 // TWI start condition TWSTA bit 5 (master)
#define TWCR_STOP 0x10 // TWI stop condition TWSTO bit 4 ()
// AVR STATUS CODES
#define TWI_SLA_W_ACK 0x18 // SLA+W has been transmitted & ACK has been received (Master Transmitter)
// FUNCTION PROTOTYPES
void MAX30102_Init(void);
void MAX30102_Start(void);
void MAX30102_Stop(void);
uint8_t MAX30102_Write(uint8_t data);
uint8_t MAX30102_WriteReg(uint8_t register, uint8_t data);
#endif