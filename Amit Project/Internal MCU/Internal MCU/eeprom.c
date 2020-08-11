/*
 * eeprom.c
 *
 * Created: 10/17/2015 1:34:55 PM
 *  Author: alaa
 */ 

#include <avr/io.h>
#include "eeprom.h"

void Eeprom_Write (uint16_t address, uint8_t data) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
		;
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

uint8_t Eeprom_Read (uint16_t address) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
		;
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}