/*
 * UART.c
 *
 * Created: 9/25/2015 2:01:59 PM
 *  Author: alaa
 */ 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include "UART.h"
#include "UART_CFG.h"


// F_CPU clock = 8MHz
#define F_CPU	8000000UL

// Initialize ATmega UART channel
void UART_Init (void) {
	// set baud rate
	uint16_t BR = ((F_CPU/16/UART_Config.baud)-1);
	UBRRH = (uint8_t)(BR>>8);
	UBRRL = (uint8_t)BR;
	// enable receiver and transmitter
	UCSRB = (1<<RXEN) | (1<<TXEN);
	// set frame format
	UCSRB |= ((UART_Config.charSize)>>3)<<UCSZ2;	// 9-bit character
	UCSRC = (1<<URSEL) | ((UART_Config.charSize)&~(1<<3)) | UART_Config.stopBits;
}

// wait for buffer to be empty,
// then output
void UART_OutChar (uint8_t data) {
	while ( !(UCSRA & (1<<UDRE)) )
		;
	UDR = data;
}

// Wait for new input
// then return ASCII code
uint8_t UART_InChar(void) {
	while ( !(UCSRA & (1<<RXC)) )
		;
	return UDR;
}

void UART_OutWord(uint16_t word) {
// 	UART_OutChar('0' + (word / 10000));                 /* Ten-thousands */
// 	UART_OutChar('0' + ((word / 1000) % 10));               /* Thousands */
// 	UART_OutChar('0' + ((word / 100) % 10));                 /* Hundreds */
// 	UART_OutChar('0' + ((word / 10) % 10));                      /* Tens */
// 	UART_OutChar('0' + (word % 10));                             /* Ones */
	
	if(word >= 10){
		UART_OutWord(word / 10);
		word = word % 10;
	}
	UART_OutChar(word + '0'); /* n is between 0 and 9 */
}
