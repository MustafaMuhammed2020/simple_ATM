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

/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[5] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/ 
uint8_t u8_g_cardpan[20] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/

void APP_init()
{
	TMR0_init();
	
	SPI_initslave(); /** INITIALIZE SPI MASTER **/
	
	LCD_init();  /** INITIALIZE LCD **/
	
	TMR0_delayms(20); /** SET DELAY FOR LCD INITILIZATION **/
	
	LCD_writestr(" ATM !");
	
	TMR0_delayms(500);
	
	LCD_sendcmd(LCD_CLEAR);
	
	TMR0_delayms(20);
}

void APP_start() 
{

	SPI_receivestring(&u8_g_cardpin);
	
	TMR0_delayms(30);
	
	SPI_receivestring(&u8_g_cardpan);
	
	LCD_goto(0,1);
	LCD_writestr(u8_g_cardpin);
	
	LCD_goto(1,1);
	LCD_writestr(u8_g_cardpan);

   
}