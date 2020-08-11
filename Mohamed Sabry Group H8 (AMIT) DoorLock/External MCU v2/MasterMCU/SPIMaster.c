/*
 * SPIMaster.c
 *
 * Created: 9/26/2015 9:38:56 PM
 *  Author: alaa
 */ 

#include "SPIMaster.h"
#include <avr/io.h>
#define F_CPU 8000000UL

/* Bit Maps for ATMEGA32 SPI module
	PB4 => SS
	PB5	=> MOSI
	PB6	=> MISO
	PB7	=> SCK
*/
#define DDR_SPI		DDRB
#define DD_MOSI		DDRB5
#define DD_MISO		DDRB6
#define	DD_SCK		DDRB7
#define DD_SS		DDRB4
#define	PORT_SPI	PORTB

void SPI_MasterInit (void) {
	// Set MOSI ans SCK out
	DDR_SPI = (1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS);
	// Enable SPI
	// Enable Master
	// Set SPI baud rate
	// Set SPI Mode (CPOL and CPHA)
	SPCR = (1<<SPE) | (1<<MSTR);	// SCK = Fosc / 4
}

uint8_t SPI_MasterTransmit (uint8_t dataOut) {
	uint8_t dataIn;
	// Out LOW on SS
	PORT_SPI &= ~(1<<DD_SS);
	// Send data
	SPDR = dataOut;
	// Wait for transmission complete
	while ( !(SPSR & (1<<SPIF)) )
		;
	dataIn = SPDR;	// Clear SPIF
	// Out HIGH on SS
	PORT_SPI &= ~(1<<DD_SS);
	return dataIn;
}
// 
u8 SPI_MasterReceive (void) {
	u8 dummy;
 	// Send dummy data
 	SPDR = dummy;
 	// Wait for transmission complete
 	while ( !(SPCR & (1<<SPIF)) )
 		;
 	return SPDR;
 }