/*
 * BTN.c
 *
 * Created: 14-Oct-15 10:43:51 AM
 *  Author: m-hos
 */ 

#include "DIO.h"
#include "BTN.h"
#include "BTN_CFG.h"

#define BTN_INACTIVE 0x00
#define BTN_ACTIVE 0x01

#define STAT_OPEN 0x00
#define STAT_RIS_EDGE 0x01
#define STAT_CLOSED 0x02

static u8 BtnState[btn_num];

void BTN_Init()
{
	for(u8 a = 0 ; a<btn_num ; a++)
	{
		Dio_InitPortDirection(PortName, 0x00, (0x01<<a));
		BtnState[a] = STAT_OPEN;
	}
}

u8 BTN_Read()
{
	u8 x = 0, BtnVal = 0, PinVal = 0;
	
	for(u8 a = 0 ; a<btn_num ; a++)
	{
		BtnVal = BTN_INACTIVE;
		PinVal = Dio_ReadPort(PortName, (0x01<<a));
		
		switch (BtnState[a])
		{
			case STAT_OPEN:
			BtnVal = BTN_INACTIVE;
			if(PinVal == (0x01<<a))
			{
				BtnState[a] = STAT_RIS_EDGE;
			}
			else
			{
				BtnState[a] = STAT_OPEN;
			}
			break;
			
			case STAT_RIS_EDGE:
			BtnVal = BTN_ACTIVE;
			if(PinVal == (0x01<<a))
			{
				BtnState[a] = STAT_CLOSED;
			}
			else
			{
				BtnState[a] = STAT_OPEN;
			}
			break;
			
			case STAT_CLOSED:
			BtnVal = BTN_INACTIVE;
			if(PinVal == (0x01<<a))
			{
				BtnState[a] = STAT_CLOSED;
			}
			else
			{
				BtnState[a] = STAT_OPEN;
			}
			break;
		}
		
		x = x | (BtnVal<<a);
	}
	return x;
}
