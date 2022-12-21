#ifndef __I2C_H__
#define __I2C_H__

#include "../../app/std_macros.h"


#define F_SCL 400000UL // target SCL frequency 
#define Prescaler 1    // from data sheet

void I2C_Master_init(void);

uint8 I2C_Master_start(uint8 slave_address);
    
uint8 I2C_Master_Repeated_Start(uint8 slave_address);

uint8 I2C_Master_Write(uint8 data);

uint8 I2C_Master_Read_Ack(void);

uint8 I2C_Master_Read_Nack(void);

void I2C_Master_Stop(void);

void I2C_Slave_Init(uint8 slave_address);

int8 I2C_Slave_Listen(void);

int8 I2C_Slave_Transmit(uint8 data);

uint8 I2C_Slave_Receive(void);

#endif 