/*
 * UART_CFG.c
 *
 * Created: 9/25/2015 2:57:59 PM
 *  Author: alaa
 */ 

#include	 "UART_CFG.h"

// UART configuration table
const UART_ConfigType UART_Config =
{
	//
	// baud		charSize		stopBits
	//
	38400,		CH_SIZE_8,	STOP_1
};