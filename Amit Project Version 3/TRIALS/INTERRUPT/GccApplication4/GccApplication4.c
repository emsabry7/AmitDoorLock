/*
 * GccApplication4.c
 *
 * Created: 28-Aug-15 4:43:38 PM
 *  Author: Mohamed Sabry
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"

	ISR (INT0_vect){
	PORTD |=0x80;
	}

int main(void)
{
	SREG |=0x80; // global int
	MCUCR |=0x02;// rising edge conf int
	GICR |=0x40; //enable int0
	DDRD &=~0x04; //set pin 3 to 0 (i/p)
	DDRD |=0x80; //set pin 8 to 1 (o/p)
	
    while(1)
    {
        
    }
}