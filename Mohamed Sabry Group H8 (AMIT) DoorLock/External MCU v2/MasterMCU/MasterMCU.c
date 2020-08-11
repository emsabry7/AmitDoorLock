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
}
void Wrong_Check(void){
	Trials++;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("Incorrect Pass ");
	Timer_Wait1ms(900);
	LCD_GoToXY(1, 0);
	if (Trials!=3){
		LCD_OutString("  Try Again..");
		Timer_Wait1ms (1000); // wait n ms
	}	
	Pass_Reset();
}
void Three_Trials_wait(void){
	Trials=0;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("    WAITING");
	for(int i=0;i<n;i++)
	Timer_Wait1ms(5000); // Wait n of 5 seconds
	Pass_Reset();
	n++;
}
void Pass_Reset(void){
	DigitsNumber=0;
	CheckResult=0;
	LCD_Clear();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter User Pin:");
	LCD_GoToXY(1, 7);
}
int main(void){	
	
	UART_Init();
	LCD_Init();
	LCD_GoToXY(0, 0);
	LCD_OutString("Enter User Pin:");
	LCD_GoToXY(1, 7);
	Key_Init();
	DDRD |=(1<<PD7);	//set pin 8 to (o/p)
	PORTD &=~(1<<PD7);	// set pin 8 to 0 volt
    while(1)
    {    
		keyPressed = Key_Scan();
		
		 if (keyPressed >= '0' && keyPressed <= '9')
		 {	 Pass_Scan(keyPressed);
			 if(DigitsNumber >= 4){ 
				 CheckResult=Pass_Check();	
				 
					if(CheckResult==CorrectPass)
						 Correct_Check();				
					else if(CheckResult==WrongPass)
						 Wrong_Check();				
	
				if(Trials >= 3)
					Three_Trials_wait();				 
			 }
		 }
		 else if (keyPressed == '*' || keyPressed == '#')
		 	 Pass_Reset();		 
		 else
		 ;
		 	 
			///////////////////////////////////
			////// Send Interrupt Trigger /////
			/////  For TurningOff Motor  //////
			///////////////////////////////////
			
			if(CheckResult==CorrectPass)
				MotorFlag=UART_InChar(); // Receiving Timer flag to Start Waiting
			
			if(MotorFlag==MotorInterruptFlag){
			
				Timer_Wait1ms(5000);
				PORTD |=(1<<PD7);	// Pin D8 =1
				Timer_Wait1ms(250);	
				PORTD &=~(1<<PD7);	// Pin D8 =0
				MotorFlag=Reset;
				CheckResult=Reset;
		}
	}
}