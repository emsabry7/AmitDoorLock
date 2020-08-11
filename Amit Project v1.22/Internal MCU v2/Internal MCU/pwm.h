/*
 * pwm.h
 *
 * Created: 10/10/2015 12:42:05 PM
 *  Author: alaam
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <inttypes.h>
// Atmega32A
// Timer 2
// phase correct PWM mode, non-inverting mode, pre scaler 256
// Input: none
// output: none
void Pwm_Init (void);

// Input: duty in percentage
// output: none
void Pwm_Duty (uint8_t duty);

#endif /* PWM_H_ */