
#include <avr/io.h>
#include "Timer0.h"

// ATmega32 at 8MHz
// Initialize TCNT to 1us
// Input: none
// Output: none
void Timer_Init (void){
	TCCR0 = 0x02;	// Normal Mode, Set pre-scaler at 8
}

// Input: delay time in 1us units
// Output: none
void Timer_Wait (u16 cycles) {
	TCNT0 = 0;
	u16 i;
	for (i = 0 ; i < (cycles / 256) ; i++)
		while (TCNT0 < 255)
			;
	while (TCNT0 <= cycles % 256)
		;
}

// Input: delay time in 1ms units
// Output: none
void Timer_Wait1ms (u16 delay){
	u32 i;	for (i = 0; i < (4 * delay); i++)		Timer_Wait(250);}

