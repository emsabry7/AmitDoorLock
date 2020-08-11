/*
 * i2c.c
 *
 * Created: 10/19/2015 10:33:43 PM
 *  Author: alaa
 */ 

#include "avr/io.h"
#include "i2c.h"

#define START	0xA4
#define STOP		0x94
#define W		0
#define R		1
// Master Transmitter (MT) status codes
#define START_ACK	0x08
#define MT_SLA_ACK	0x18
#define	MT_DATA_ACK	0x28
#define MR_SLA_ACK	0x40
#define	MR_DATA_ACK	0x58

static void I2c_WaitIntFlag (void) {
	while ( !(TWCR & (1<<TWINT)) );
}

static void I2c_ClearIntFlag (void) {
	TWCR = (1<<TWINT) | (1<<TWEN);
}

static uint8_t I2c_Status (void) {
	return (TWSR & 0xF8);
}

void I2c_Init (void) {
	// Set bit rate
	TWBR = 0x01;
	// Set pre-scaler to 0
	TWSR &= ~((1<<TWPS0) | (1<<TWPS1));
}

int8_t I2c_Send1 (uint8_t slave, uint8_t data) {
	/* 1. Send Start */
	TWCR = START;
	I2c_WaitIntFlag();
	if (I2c_Status() != START_ACK)
		return -1;
		
	/* 2. set slave address and issue a write command */
	TWDR = slave + W;
	I2c_ClearIntFlag();	// to start Tx of address
	I2c_WaitIntFlag();
	if (I2c_Status() != MT_SLA_ACK)
		return -1;
		
	/* 3. send data packet */
	TWDR = data;
	I2c_ClearIntFlag();
	I2c_WaitIntFlag();
	if (I2c_Status() != MT_DATA_ACK)
		return -1;
	
	/* 4. send Stop */
	TWCR = STOP;
	while((TWCR & (1<<TWSTO)));
	return 1;
}

uint8_t I2c_Recv1 (uint8_t slave) {
	uint8_t data;
	/* 1. Send Start */
	TWCR = START;
	I2c_WaitIntFlag();
	if (I2c_Status() != START_ACK)
		return -1;
	
	/* 2. set slave address and issue a read command */
	TWDR = slave + R;
	I2c_ClearIntFlag();	// to start Tx of address
	I2c_WaitIntFlag();
	if (I2c_Status() != MR_SLA_ACK)
		return -1;
	
	/* 3. read data packet */
	I2c_ClearIntFlag();
	I2c_WaitIntFlag();
	if (I2c_Status() != MR_DATA_ACK)
		return -1;
	data = TWDR;
	
	/* 4. send Stop */
	TWCR = STOP;
	while((TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
	return data;
}