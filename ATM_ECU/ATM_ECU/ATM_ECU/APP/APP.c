/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : implementation of application layer  */
/**************************************************/

#include <string.h>

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE INTERFACE FILES OF LOWER LAYERS **/
#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/timer0/TMR0_config.h"

#include "../MCAL/dio/DIO_interface.h"

#include "../MCAL/spi/SPI_interface.h"

#include "../HAL/lcd/LCD_interface.h"

#include "../HAL/keypad/KEYPAD_interface.h"


/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[5] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/ 
uint8_t u8_g_cardpan[20] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/

uint8_t u8_g_userpin[5] = "0000"; /** GLOBAL VARIABLE TO GET USER PIN **/


KEYPAD_readError returnstatus = KEYPAD_readFail ;  /** VARIABLE TO HOLD THE RETURN STATUS OF KEYPAD **/
uint8_t u8_a_pressednum = 0 ; /** VARIABLE TO STORE THE PRESSED NUM FROM KEYPAD **/


void APP_init()
{
	//DIO_setpindir(DIO_PORTA , DIO_PIN0 , DIO_PIN_INPUT);   /** TRIGGER PIN INPUT FROM CARD MCU **/
	
	TMR0_init();
	
	//SPI_initslave(); /** INITIALIZE SPI MASTER **/
	
	KEYPAD_init(); /** INITIALIZE THE KEYPAD **/
	
	LCD_init();  /** INITIALIZE LCD **/
	TMR0_delayms(20); /** SET DELAY FOR LCD INITILIZATION **/
	
	LCD_writestr(" YA WELCOME !"); /** DISPLAY WELCOME MESSAGE FOR 1 SEC **/
	TMR0_delayms(500);
	
	LCD_sendcmd(LCD_CLEAR);
	TMR0_delayms(20);
	
	LCD_goto(1 ,1);
	LCD_writestr("Insert A Card"); /** ASK USER TO INSERT HIS CARD **/
	
	LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
}

void APP_readuserpin()
{
	uint8_t counter ;
	
	  	for(counter = 0 ; counter<4 ; counter++)
	 	{
	 		KEYPAD_read(&u8_a_pressednum); /** READ THE PRESSED BUTTON **/
	
	 		if(returnstatus == KEYPAD_readSuccess)
	 		{
 				LCD_writechar(u8_a_pressednum);
	 			u8_g_userpin[counter] = u8_a_pressednum ;
				TMR0_delayms(200);
			//	returnstatus = KEYPAD_readFail ;
			}
		 }
		 
		 //KEYPAD_read(&u8_a_pressednum); /** READ THE PRESSED BUTTON **/
		 
}

void APP_start() 
{
	
  //while (bit_is_clear(DIO_PORTA , DIO_PIN0)); /** POLLING UNTILL TRIGGER FROM CARD MCU **/
  
	LCD_goto(0 , 1);
	LCD_writestr("Enter Your PIN");
	
	LCD_goto(1,1);
    APP_readuserpin();
	
	LCD_sendcmd(LCD_CLEAR);
	TMR0_delayms(20);
	
	LCD_goto(0,0);
	
	LCD_writestr(u8_g_userpin);
	//TMR0_delayms(2000);
	
	/****************
	SPI_receivestring(&u8_g_cardpin);
	
	TMR0_delayms(30);
	
	SPI_receivestring(&u8_g_cardpan);
	
	LCD_goto(0,1);
	LCD_writestr(u8_g_cardpin);
	
	LCD_goto(1,1);
	LCD_writestr(u8_g_cardpan);
******/
   
}