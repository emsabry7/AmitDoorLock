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

#define CorrectPass	1
#define WrongPass	2

u8 PassEntered[4];
u8 CheckResult=0;
u8 keyPressed = 0;
u8 DigitsNumber=0;
u8 Trials=0;
u8 n=1;

void pass_scan(u8 keyPressed)
{
	PassEntered[DigitsNumber] = keyPressed;
	
	LCD_OutChar('*');
	DigitsNumber++;
	
}
u8 pass_check(void)
{
	for (int j=0;j<4;j++){
		UART_OutChar (PassEntered[j]);	
	}
	CheckResult=UART_InChar();
	return CheckResult;	
}
void pass_reset(void)
{
	DigitsNumber=0;
	CheckResult=0;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter Password: ");
	LCD_GoToXY(1, 7);
}
int main(void)
{	/* *** TEST KEYPad and LCD *** */
	UART_Init();
	LCD_Init();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter Password: ");
	LCD_GoToXY(1, 7);
	Key_Init();
    while(1)
    {    keyPressed = Key_Scan();
		 if (keyPressed >= '0' && keyPressed <= '9')
		 {
			 pass_scan(keyPressed);
			 if(DigitsNumber >= 4)
			 {		CheckResult=pass_check();	
				 if(CheckResult==CorrectPass)
				 {
					 LCD_Clear();
					 LCD_GoToXY(0, 0);
					 LCD_OutString("Correct Pass :)");
					 Timer_Wait1ms (850); // wait n ms
					 LCD_Clear();
					 LCD_GoToXY(0, 0);
					 LCD_OutString("    WELCOME..");
					 LCD_GoToXY(1, 0);
					 LCD_OutString("  System Is On");
					 
				 }
				 else if(CheckResult==WrongPass)
				 {
					 Trials++;
					 LCD_Clear();
					 LCD_GoToXY(0, 0);
					 LCD_OutString("Incorrect Pass!");
					 LCD_GoToXY(1, 0);
					 LCD_OutString("  Try again..");
					 Timer_Wait1ms (500); // wait n ms
					 pass_reset();
				 }
				 
				 if(Trials >= 3)
				 {
					 Trials=0;
					 LCD_Clear();
					 LCD_GoToXY(0, 0);
					 LCD_OutString("    WAITING");
					 
					 for(int b=0;b<n;b++)
					 Timer_Wait1ms	 (5000); // wait n ms
					 
					 pass_reset();
					 n++;
				 }
			 }
		 }
		 else if (keyPressed == '*' || keyPressed == '#')
		 {
			 pass_reset();
		 }
		 else
		 ;
		 _delay_ms(10);
    }
}
