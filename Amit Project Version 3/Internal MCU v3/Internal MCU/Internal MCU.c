/*
 * Internal_MCU.c
 *
 * Created: 28-Oct-15 6:43:29 PM
 *  Author: Mohamed Sabry
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "STDTypes.h"
#include "UART.h"
#include "eeprom.h"
#include "ADC.h"
#include "LCD.h"
#include "Timer0.h"
#include "macros.h"
#include "pwm.h"

#define Reset		0
#define CorrectPass	1
#define WrongPass	2
#define MotorInterruptFlag	3

u8 PermissionFlag=0;
u8 InitMotorFlag=0;
u16 Temp;

void Send_CheckResult (u8 CheckResult){
	if(CheckResult != WrongPass){
		CheckResult=CorrectPass;
		UART_OutChar(CheckResult);	//UART send MatchingResult (flag)
		PermissionFlag=CheckResult;	// permissionFlag=CorrectPass
	}
	else if (CheckResult==WrongPass){
		UART_OutChar(CheckResult);	//UART send MatchingResult (flag)
		PermissionFlag=CheckResult;	// permissionFlag=WrongPass
		CheckResult=Reset;
	}
}
void TempSensor_Init(void){
	LCD_Init();
	Adc_Init();
	Timer_Init();
	LCD_GoToXY(0, 0);
	LCD_OutString("Temperature =");
}
void TempSensor_On (void){
	LCD_GoToXY(0, 0);
	LCD_OutString("Temperature =");
	Temp= (Adc_Read(0)/2)-1;
	LCD_OutUDec(Temp);
	Timer_Wait1ms(50);			
}
void Init_INT0(void){
	SREG |=0x80; // global int
	MCUCR |=0x02;// rising edge conf int
	GICR |=0x40; //enable int0
	DDRD &=~0x04; //set pin 3 to 0 (i/p)
	PIND &=0x7f;
}
ISR (INT0_vect){
	Pwm_Duty(0);
	LCD_GoToXY(1, 0);
	LCD_OutString("  Motor OFF ");
	Timer_Wait1ms(5);
}	
void MotorPWMOn (void){
		Pwm_Init();
		Pwm_Duty(90);
		LCD_GoToXY(1, 0);
		LCD_OutString("  Motor ON ");
		Timer_Wait1ms(5);		
}
int main(void){
	
	u8 ReceivedPass[4];
	u8 CheckResult=0;
		
	UART_Init ();
	
	// setting password into the Eeprom
	Eeprom_Write (0,1); 
	Eeprom_Write (1,2); 
	Eeprom_Write (2,3); 
	Eeprom_Write (3,4);
	while(1)
    {
		////////////////////////////////
		////// Receiving Password  /////
		////////////////////////////////
		
		for (u8 i=0;i<4;i++) {
			ReceivedPass[i]=UART_InChar()-'0';
		}
		////////////////////////////////
		// Checking Password Matching //
		////////////////////////////////
		for (u8 i=0;i<4;i++) {
			if (ReceivedPass[i]==Eeprom_Read(i)){
				;
			}
			else{
				CheckResult=WrongPass; //check result 
			}
		}
		////////////////////////////////
		//////   Sending Flag   ////////
		////////////////////////////////
		Send_CheckResult(CheckResult);
		
		////////////////////////////////
		//// Turning On Functions   ////
		////////////////////////////////	
		
		if(PermissionFlag==CorrectPass){
			TempSensor_Init();
			Init_INT0();	
		/////////////// Temp Sensor Init////////////////
		
			MotorPWMOn ();	// motor turn on
			UART_OutChar(MotorInterruptFlag);
			while(1){
				TempSensor_On (); 
			}
		}			
	}	
}

/*
using SPI 

#include <avr/io.h>
#include "STDTypes.h"
#include "SPISlave.h"
#include "eeprom.h"


#define CorrectPass	1
#define WrongPass	2

int main(void)
{
	u8 ReceivedPass[4];
	u8 CheckResult=0;
	
	SPI_SlaveInit ();
	
	// setting password into the Eeprom
	Eeprom_Write (0,1);
	Eeprom_Write (1,2);
	Eeprom_Write (2,3);
	Eeprom_Write (3,4);
	
	
	while(1)
	{
		// Receiving Password
		for (int i=0;i<4;i++) {
			ReceivedPass[i]=SPI_SlaveReceive(0);
		}
		// Checking Password Matching
		for (int i=0;i<4;i++) {
			if (ReceivedPass[i]==Eeprom_Read(i)){
				;
			}
			else{
				CheckResult=WrongPass; //check result =
			}
			
		}
		if(CheckResult != WrongPass)
		CheckResult=CorrectPass;
		
		SPI_SlaveTransmit(CheckResult);	//send MatchingResult (flag)
	}
}

*/

/*


#include <avr/io.h>
#include "STDTypes.h"
#include "SPISlave.h"
#include "eeprom.h"

#define CorrectPass	1
#define WrongPass	2

int main(void)
{	
	u8 ReceivedPass[4];
	u8 CheckResult=0;
		
	void SPI_SlaveInit (void);
	
	// setting password into the Eeprom
	Eeprom_Write (0,1); 
	Eeprom_Write (1,2); 
	Eeprom_Write (2,3); 
	Eeprom_Write (3,4);
	
	
    while(1)
    {
		// Receiving Password
		for (int i=0;i<4;i++) {
				ReceivedPass[i]=SPI_SlaveReceive(2);
		}
		// Checking Password Matching
		for (int i=0;i<4;i++) {
			if (ReceivedPass[i]==Eeprom_Read(i)){
				;
			}
			else{
				CheckResult=WrongPass; //check result =
			}
			
		}
		if(CheckResult != WrongPass)
			CheckResult=CorrectPass;						
			
		SPI_SlaveTransmit(CheckResult);	//send MatchingResult (flag)
	}	
}
*/