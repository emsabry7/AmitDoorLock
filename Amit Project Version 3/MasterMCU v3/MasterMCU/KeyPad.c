/*
 * KeyPad.c
 *
 * Created: 14-Oct-15 7:57:11 PM
 *  Author: m-hos
 */ 

#include "StdTypes.h"
#include "KeyPad.h"
#include "DIO.h"


typedef struct
{
	u8 direction;
	u8 keyval[3];
}rowtype;

static const rowtype Scan_Tab[5] =
{
	{0x10, "123"},
	
	{0x20, "456"},
	
	{0x40, "789"},
	
	{0x80, "*0#"},
	
	{0, ""}
};


void Key_Init(void)
{
	Dio_InitPortDirection(PC,0x00,0x07);
	Dio_InitPortDirection(PC,0xff,0xf0);
	Dio_WritePort(PC,0x00,0xf0);
}


u8 Key_Scan(void)
{
	u8 column = 0, i = 0, k = 0, j = 0;
	
	while( Scan_Tab[i].direction != 0 )
	{
		Dio_InitPortDirection(PC, Scan_Tab[i].direction, 0xf0);
		
		column = Dio_ReadPort(PC, 0x07);
		
		for(j=0; j<3; j++)
		{
			if((column & 0x01) == 0)
			{
				k = Scan_Tab[i].keyval[j];
				while (Dio_ReadPort(PC, 0x07) != 0x07); // Wait if key still pressed
				return k;
			}
			column = column >> 1;
		}
		
		i++;
	}
	
	return k;
}

