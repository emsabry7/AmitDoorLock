/*
 * btn.c
 *
 * Created: 10/3/2015 12:23:42 PM
 *  Author: alaam
 */ 

#include <avr/io.h>
#include "btn.h"
#include "macros.h"
#include "STDTypes.h"
void Btn_Init (void) {
	DDRD &= ~(1<<PD6);	// Sw on PC0
	PORTD |= (1<<PD6);	// Enable pull up resistor
}

u8 Btn_Read (void) {
	u8 btnState;
	btnState = READ_BIT(PIND, 6);
	return btnState;
}
