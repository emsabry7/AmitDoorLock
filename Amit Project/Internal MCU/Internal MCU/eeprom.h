/*
 * eeprom.h
 *
 * Created: 10/17/2015 1:35:06 PM
 *  Author: alaa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <inttypes.h>

void Eeprom_Write (uint16_t, uint8_t); // address , data

uint8_t Eeprom_Read (uint16_t); //address

#endif /* EEPROM_H_ */