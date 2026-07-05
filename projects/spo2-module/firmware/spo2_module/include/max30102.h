#ifndef MAX30201_H
#define MAX30201_H
// HEADER INCLUDES
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
// MACROS FOR TWI & INITIALIZATION
#define PC4_PC5_VALUE 0x30
#define MAX30102_ADDRESS 0x57 // i2c address for the at328p (0b1010111) pg. 29 of datasheet
#define MAX30102_FIFO_DATA_REG 0x07 // register address for the FIFO data pg. 10
#define MAX30102_SLA_W 0xAE // write address for MAX30201
#define MAX30102_SLA_R 0xAF // read address for MAX30201
#define TWSR_VALUE 0x0 // prescaler value of 00 on bit 0,1 enables prescaler value * 1
#define TWBR_VALUE 72 // 100kHz standard mode for max30102
#define TWI_EN 0x04 // TWEN is the bit 2, set high to enable TWI
#define TWI_ACK 0x40 // TWEA acknowledge bit set to 1
#define TWINT_CLEAR 0x80// clear bit 7 (TWINT)
#define TWCR_START 0x20 // TWI start condition TWSTA bit 5 (master)
#define TWCR_STOP 0x10 // TWI stop condition TWSTO bit 4 ()
#define SPO2_DATA_LENGTH 6 // 6 bytes
#define ADC_18_BIT_LENGTH 0x3FFFF // 18-bit values (full 3 bytes is 24 bits)
#define MAX30102_MODE_RESET 0x40 // bit 6 of the mode configuration register macro
#define MAX30102_PTR_RESET 0x00 // reset values for overflow & read & write pointers
#define MAX30102_FIFO_CONFIG_VALUE 0x4F // 010 = 4 samples averaged per FIFO sample, bit 4 = 0 (no rollover), bit 3-0 = 0xF (interrupt issued when 15 data samples remain)  
#define SPO2_MODE 0x03 // select SPO2 mode from mode config register
#define SPO2_ADC_VALUE 0x27 // bit 6-5: 01 (4096 nA), bit 4-2: 001: 100 samples per second, bit 1-0: 18-bit ADC resolution
#define LED_CURRENT_VALUE 0x2F // 9.4 mA
// AVR STATUS CODES
#define TWI_SLA_W_ACK 0x18 // SLA+W has been transmitted & ACK has been received (Master Transmitter)
#define TWI_SLA_R_ACK 0x40 // SLA+R has been transmitted & ACK has been received (Master Receiver)
#define TWI_DATA_ACK 0x28 // Data has been transmitted and ACK has been received (Master Transmitter)
// MAX30102 REGISTERS
#define MAX30102_MODE_CONFIG 0x09
#define MAX30102_FIFO_REG 0x07
#define MAX30102_FIFO_WR_PTR 0x04
#define MAX30102_FIFO_READ_PTR 0x06
#define MAX30102_FIFO_CONFIG 0x08
#define MAX30102_SP02_CONFIG 0x0A
#define MAX30102_OVERFLOW_COUNT 0x05
#define MAX30102_LED1 0x0C
#define MAX30102_LED2 0x0D
// FUNCTION PROTOTYPES
void MAX30102_Init(void);
void MAX30102_Start(void);
void MAX30102_Stop(void);
uint8_t MAX30102_Write(uint8_t data);
uint8_t MAX30102_ReadNack(void);
uint8_t MAX30102_ReadAck(void);
bool MAX30102_WriteReg(uint8_t reg, uint8_t data);
bool MAX30102_ReadReg(uint8_t reg, uint8_t *data);
bool MAX30102_ReadBytes(uint8_t reg, uint8_t *data, uint8_t length);
bool MAX30102_ReadFIFO(uint32_t *red, uint32_t *ir);
bool MAX30102_Setup(void);
#endif