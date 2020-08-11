/*
 * MasterMCU.c
 *
 * Created: 28-Oct-15 8:49:55 PM
 *  Author: Mohamed Sabry
 */ 


#include <avr/io.h>
#include "util/delay.h"
#include "StdTypes.h"
#include "KeyPad.h"
#include "LCD.h"
#include "UART.h"
#include "UART_CFG.h"
#include "eeprom.h"

#define Reset	0
#define CorrectPass	1
#define WrongPass	2
#define MotorInterruptFlag	3


u8 PassEntered[4];
u8 CheckResult=0;
u8 keyPressed = 0;
u8 DigitsNumber=0;
u8 Trials=0;
u8 n=1;
u8 MotorFlag;

void Pass_Scan(u8 keyPressed){
	PassEntered[DigitsNumber] = keyPressed;
	LCD_OutChar('*');
	DigitsNumber++;
}
u8 Pass_Check(void){
	for (int j=0;j<4;j++){
		UART_OutChar (PassEntered[j]);	
	}
	CheckResult=UART_InChar();
	return CheckResult;	
}
void Correct_Check(void){
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("    WELCOME..");
	Timer_Wait1ms(500);
	LCD_GoToXY(1, 0);
	LCD_OutString("  System Is On");
	PORTD &=~0x80;	//send (0)inturrpt flag
}
void Wrong_Check(void){
	Trials++;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("Incorrect Pass!");
	Timer_Wait1ms(500);
	LCD_GoToXY(1, 0);
	LCD_OutString("  Try again..");
	Timer_Wait1ms (500); // wait n ms
	Pass_Reset();
}
void Pass_Reset(void){
	DigitsNumber=0;
	CheckResult=0;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter The Pin : ");
	LCD_GoToXY(1, 7);
}
int main(void){	
	/* *** TEST KEYPad and LCD *** */
	UART_Init();
	LCD_Init();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter The Pin : ");
	LCD_GoToXY(1, 7);
	Key_Init();
	DDRD |=(1<<PD7); //set pin 8 to 1 (o/p)
	PORTD &=~(1<<PD7);
    while(1)
    {    keyPressed = Key_Scan();
		 if (keyPressed >= '0' && keyPressed <= '9')
		 {	 Pass_Scan(keyPressed);
			 
			 if(DigitsNumber >= 4){
				 CheckResult=Pass_Check();	
				 
				 if(CheckResult==CorrectPass){
					 Correct_Check();
				 }
				 else if(CheckResult==WrongPass){
					 Wrong_Check();				
				 }
				 if(Trials >= 3){
					 Trials=0;
					 LCD_Clear();
					 LCD_GoToXY(0, 0);
					 LCD_OutString("    WAITING");
					 for(int b=0;b<n;b++)
					 Timer_Wait1ms(5000); // Wait n of 5 seconds 
					 Pass_Reset();
					 n++;
				 }
			 }
		 }
		 else if (keyPressed == '*' || keyPressed == '#')
		 {
			 Pass_Reset();
		 }
		 else
		 ;
		 _delay_ms(10);
		 if(CheckResult==CorrectPass){
			MotorFlag=UART_InChar();
		 }
		 if(MotorFlag==MotorInterruptFlag){
			Timer_Wait1ms(5000);
			PORTD |=(1<<PD7);	//send inturrpt flag
			Timer_Wait1ms(400);
			PORTD &=~(1<<PD7);
			
			MotorFlag=Reset;
			CheckResult=Reset;
		}
			
		
	}
}	 
   

	