/*
 * Timer0.h
 *
 * Created: 14-Oct-15 11:01:26 PM
 *  Author: m-hos
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "StdTypes.h"

void Timer_Init (void);
void Timer_Wait (u16 cycles); // wait n us
void Timer_Wait1ms (u16 delay); // wait n ms

#endif /* TIMER0_H_ */