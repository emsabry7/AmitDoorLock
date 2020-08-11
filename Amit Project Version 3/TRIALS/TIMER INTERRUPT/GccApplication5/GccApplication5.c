/*
 * GccApplication5.c
 *
 * Created: 28-Aug-15 7:01:33 PM
 *  Author: Mohamed Sabry
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
ISR(TIMER0_COMP_vect){
	PORTD |=0x40; // enable led of pin 7
}
ISR(TIMER0_OVF_vect){
	PORTD |=0x80; // enable led of pin 8
}
int main(void)
{
	DDRD |=0xc0;	// set pin 7,8 (leds) as 
	TCCR0 |=0x02;	//clock / 1024 (pre scaler)
	OCR0=1024;		//copmare match value =100
	TCNT0=0;		// timer starts from 0
	SREG |=0x80;	// global int
	TIMSK |=0x03;
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}