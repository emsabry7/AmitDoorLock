/*
 * pwm.c
 *
 * Created: 10/10/2015 12:41:56 PM
 *  Author: alaa
 */ 

#include <avr/io.h>
#include "pwm.h"

// Atmega32A
// Timer 2
// phase correct PWM mode, non-inverting mode, pre scaler 256
// Input: none
// output: none
void Pwm_Init (void) {
	DDRD |= (1<<7);	// OC2 output
	TCCR2 |= (1<<WGM20) | (1<<COM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 10;
}

// Input: duty in percentage
// output: none
void Pwm_Duty (uint8_t duty) {
	OCR2 = (uint8_t) (255 * duty / 100);
}