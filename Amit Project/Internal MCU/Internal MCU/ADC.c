/*
 * ADC.c
 *
 * Created: 10/17/2015 5:59:17 PM
 *  Author: Happy
 */ 

#include <avr/io.h>
#include "STDTypes.h"
void Adc_Init(void)
{
	ADMUX = (1<<REFS0); // set reference to vcc
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // set the prescaler to 64 , Enable the ADC 
}

uint16_t Adc_Read(uint8_t Channel)
{	u16 Data;
	
	ADMUX |= (Channel & 0x07); // masking & set channel 
	ADCSRA |= (1<<ADSC); // Start Conversion 
	while ( ADCSRA & (1<<ADSC) ); // adsc = 6 .. wait until conversion is complete ( adsc=0)
	Data = ADC;
	return Data;
}