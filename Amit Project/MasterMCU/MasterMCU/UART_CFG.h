/*
 * UART_CFG.h
 *
 * Created: 9/25/2015 2:57:47 PM
 *  Author: alaa
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_

#include <inttypes.h>

enum {
	CH_SIZE_5 = 0x00, 
	CH_SIZE_6 = 0x02, 
	CH_SIZE_7 = 0x04, 
	CH_SIZE_8 = 0x06,
	CH_SIZE_9 = 0x0E,  
	};
enum {
	STOP_1 = 0x00,
	STOP_2 = (1<<3),	// USBS
	};
	
// UART Configuration table elements
typedef struct {
	uint32_t baud;		/* The baud rate */
	uint8_t charSize;		/* 5, 6, 7, 8 or 9 */
	uint8_t stopBits;		/* LOW or HIGH */
} UART_ConfigType;

extern const UART_ConfigType UART_Config;

#endif /* UART_CFG_H_ */