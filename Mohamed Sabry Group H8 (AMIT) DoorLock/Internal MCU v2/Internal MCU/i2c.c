/*
 * i2c.c
 *
 * Created: 10/19/2015 10:33:43 PM
 *  Author: alaa
 */ 

#include "avr/io.h"
#include "i2c.h"

// Slave Receiver (SR) status codes
#define SR_SLA_ACK	0x60
#define SR_DATA_ACK	0x80
// Slave Transmitter (ST) status codes
#define ST_SLA_ACK	 0xA8
#define ST_DATA_NACK	 0xAC0

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
	// Address of the slave, programmable
	TWAR = 0x20;
}

int8_t I2c_Send1 (uint8_t data) {
	TWCR = (1<<TWEA) | (1<<TWEN);
	/* Wait to be addressed */
	while (I2c_Status() != ST_SLA_ACK)
		;
	TWDR = data;
	I2c_ClearIntFlag();
	I2c_WaitIntFlag();
	if (I2c_Status() != ST_DATA_NACK)
		return -1;
		
	return 0;
}

uint8_t I2c_Recv1 (void) {
	uint8_t data;
	TWCR = (1<<TWEA) | (1<<TWEN);
	/* Wait to be addressed */
	while (I2c_Status() != SR_SLA_ACK)
		;
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	I2c_WaitIntFlag();
	if (I2c_Status() != SR_DATA_ACK)
		return 0;
	data = TWDR;
	return data;
}