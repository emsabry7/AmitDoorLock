/*
 * DIO.c
 *
 * Created: 14-Oct-15 10:42:03 AM
 *  Author: m-hos
 */ 

#include <avr/io.h>
#include "DIO.h"

// write a macro to write a register with a certain value on specific bits locations
#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask)

//read a macro to read specific bits from a register
#define READ_REG(Reg,Mask) Reg & Mask

void Dio_InitPortDirection(u8 PortName,u8 PortDirection,u8 PortMask)
{
	//check the required port, specified bits and direction on the Data Direction Register
	switch(PortName)
	{
		case PA:
			WRITE_REG(DDRA,PortDirection,PortMask);
			break;
		
		case PB:
			WRITE_REG(DDRB,PortDirection,PortMask);
			break;
			
		case PC:
			WRITE_REG(DDRC,PortDirection,PortMask);
			break;
			
		case PD:
			WRITE_REG(DDRD,PortDirection,PortMask);
			break;
	}
}

void Dio_WritePort(u8 PortName,u8 PortData,u8 PortMask)
{
	//check the required port, specified bits and value on the Port Data Register
	switch(PortName)
	{
		case PA:
			WRITE_REG(PORTA,PortData,PortMask);
			break;
		
		case PB:
			WRITE_REG(PORTB,PortData,PortMask);
			break;
		
		case PC:
			WRITE_REG(PORTC,PortData,PortMask);
			break;
		
		case PD:
			WRITE_REG(PORTD,PortData,PortMask);
			break;
	}
}

u8 Dio_ReadPort(u8 PortName,u8 PortMAsk)
{
	u8 x=0;
	//check the required port, specified bits and value from the Port input Register
	switch(PortName)
	{
		case PA:
			x = READ_REG(PINA,PortMAsk);
			break;
		
		case PB:
			x = READ_REG(PINB,PortMAsk);
			break;
		
		case PC:
			x = READ_REG(PINC,PortMAsk);
			break;
		
		case PD:
			x = READ_REG(PIND,PortMAsk);
			break;
	}
	return x;
}
