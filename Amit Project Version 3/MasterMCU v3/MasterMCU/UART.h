/*
 * UART.h
 *
 * Created: 9/25/2015 2:02:09 PM
 *  Author: alaa
 */ 


#ifndef UART_H_
#define UART_H_

#include <inttypes.h>

// Initialize ATmega UART channel
void UART_Init (void);

// wait for buffer to be empty,
// then output
void UART_OutChar (uint8_t data);

// Wait for new input
// then return ASCII code
uint8_t UART_InChar(void);

void UART_OutWord(uint16_t word);


#endif /* UART_H_ */