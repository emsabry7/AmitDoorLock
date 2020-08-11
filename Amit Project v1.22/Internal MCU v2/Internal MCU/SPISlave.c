/*
 * SPISlave.c
 *
 * Created: 9/26/2015 10:19:37 PM
 *  Author: alaam
 */ 

#include "SPISlave.h"
#include <avr/io.h>
#define F_CPU 8000000UL

/* Bit Maps for ATMEGA32 SPI module
	PB4 => SS
	PB5	=> MOSI
	PB6	=> MISO
	PB7	=> SCK
*/
#define DDR_SPI	DDRB
#define DD_MOSI	6
#define DD_MISO	7
#define	DD_SCK	8

void SPI_SlaveInit (void) {
	// Set MISO out
	DDR_SPI = (1<<DD_MISO);
	// Enable SPI module: Slave
	SPCR = (1<<SPE);
}

u8 SPI_SlaveReceive (u8 dataOut) {
	SPDR = dataOut;
	// Wait for reception complete
	while ( !(SPSR & (1<<SPIF)) )
		;
	// Return received data
	return SPDR;
}
 
 void SPI_SlaveTransmit(u8 data) {
	// wait for reception complete
while ( !(SPSR & (1<<SPIF)) )
 		;
 	SPDR = data;
 }