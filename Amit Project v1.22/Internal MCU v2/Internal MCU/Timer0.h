/*
 * Timer0.h
 *
 * Created: 10/16/2015 4:34:02 PM
 *  Author: Mohamed
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_


#include "STDTypes.h"

void Timer_Init (void);
void Timer_Wait (u16 cycles);
void Timer_Wait1ms (u16 delay);





#endif /* TIMER0_H_ */