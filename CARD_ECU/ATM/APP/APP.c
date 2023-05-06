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
#include "../MCAL/dio/DIO_private.h"

#include "../MCAL/uart/UART_interface.h"

#include "../MCAL/spi/SPI_interface.h"

#include "../MCAL/i2c/I2C_interface.h"
#include "../MCAL/i2c/I2C_config.h"

#include "../HAL/lcd/LCD_interface.h"

#include "../HAL/eeprom/EEPROM_interface.h"

/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[5] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/ 
uint8_t u8_g_cardpan[20] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/
uint8_t u8_g_cardpinconfirm[5] = "0000";           /** GLOBAL VARIABLE TO HOLD PAN CONFIRMATION **/

uint8_t u8_a_notmatched = 0 ;

uint8_t readpin[5] = "0000" ;
uint8_t readpan[20] = "0000000000000000000";


/** FUNCTION FOR INITIALIZATION **/
void APP_init()
{
//  	DDRA = 0xFF ;  /** OUTPUT **/
//  	PORTA = 0x00 ; /** INITIAL VALUE 0 **/

   TMR0_init(); /** TIMER 0 INITIALIZATION **/
	
	UART_init();  /** INITIALIZATION UART MODULE **/
	
	SPI_initmaster(); /** INITIALIZE SPI MASTER **/
	
	EEPROM_init(); /** INITIALIZE EEPROM MODULE **/
}

/** FUNCTION TO PROGRAM THE CARD DATA **/
void APP_cardprogram()
{
	uint8_t u8_a_num = 0 , u8_character = 0; /** PIN NUMBER ITERATOR **/
	/************************************************************************/
	/**                     PROGRAMMING THE CARD                           **/
	/************************************************************************/
	uint8_t u8_a_try = 0 ; /** COUNTER FOR PIN ATTEMPTS **/
	
	UART_sendstr("\r\n          you are in the programming mode\r\n"); /** MESSAGE **/
	
	UART_sendstr("Please enter card PAN\r\n"); /** ASK USER TO INTER CARD PAN **/
	UART_receivestr(&u8_g_cardpan); /** RECEIVE PAN FROM USER **/
	
	while (u8_a_try <= 2) /** JUST TWO ATTEMPTS TO SET CARD PIN **/
	{
		UART_sendstr("\r\nPlease enter new 4-numbers PIN\r\n");/** ASK USER TO INTER CARD PIN **/
		UART_receivestr(&u8_g_cardpin);  /** RECEIVE PIN FROM USER **/
		
		UART_sendstr("\r\nPlease confirm your PIN\r\n");/** ASK USER TO INTER CARD PIN **/
		UART_receivestr(&u8_g_cardpinconfirm); /** RECEIVE PIN CONFIRMATION **/
		
		/** CHECK IF CHARACTER ENTERED **/
		while(u8_a_num < 4)
		{
			/** VALIDATE THE USER INPUT AS NUMBERS ONLY **/
			if (!((u8_g_cardpin[u8_a_num] > 48) && (u8_g_cardpin[u8_a_num] < 57)))
			{
				u8_character = 1 ; /** CHARACTER FOUND **/
			}
			u8_a_num++ ; /** JUMP TO THE NEXT NUMBER **/
		}
		
		u8_a_notmatched = strcmp(u8_g_cardpin , u8_g_cardpinconfirm); /** CHECK IF PIN MATCHED OR NOT **/
		
		if (u8_a_notmatched == 0 && u8_character == 0) /** IF PIN MATCHED AND NO CHARACTERS **/
		{
			UART_sendstr("\r\nData received successfully\r\n");
			break ;
		}
		u8_a_num = 0 ; /** REINITIALIZE ITERATOR AND CHARACTER STATUS TO 0 AGAIN **/
		u8_character = 0 ;

		u8_a_try++ ; /** NEXT TRY **/
		
		if(u8_a_try >= 1) /** NOT THE FIRST MESSAGE **/
		{
			if (u8_character == 1) /** USER ENTERED CHARACTER **/
			{
				UART_sendstr("\r\n Letters not allowed , numbers only\r\n");
			}
			else /** PIN NOT MATCHED **/
			{
				UART_sendstr("\r\nPIN didn't match !\r\n");/** ASK USER TO INTER CARD PIN **/
			}
		}
	}
}

/** FUNCTION TO STORE CARD DATA IN THE EEPROM **/
void APP_storecard()
{
	/** STORE PIN NUMBER **/
	for (uint16_t pin_counter = 0x0000 ; pin_counter < 0x0004 ; pin_counter++)
	{
		EEPROM_writebyte(CARD_PINADDRESS_0+pin_counter , u8_g_cardpin[pin_counter] , PAGE_0 );
		TMR0_delayms(20);
	}

	/** STORE PAN NUMBER **/
	for (uint16_t pan_counter = 0x0000 ; pan_counter < 0x0014 ; pan_counter++)
	{
		EEPROM_writebyte(CARD_PANADDRESS_0+pan_counter , u8_g_cardpan[pan_counter] , PAGE_0 );
		TMR0_delayms(20);
	}

}

/** FUNCTION TO READ CARD DATA FROM EEPROM **/
void APP_getcarddata(void)
{
	for (uint16_t counter = 0x0000 ; counter < 0x0004 ; counter++)
	{
		EEPROM_readbyte(CARD_PINADDRESS_0+counter , &readpin[counter] , PAGE_0 );
		TMR0_delayms(20);
	}
	
	for (uint16_t pan_counter = 0x0000 ; pan_counter < 0x0014 ; pan_counter++)
	{
		EEPROM_readbyte(CARD_PANADDRESS_0+pan_counter , &readpan[pan_counter] , PAGE_0 );
		TMR0_delayms(20);
	}
			
}

void APP_start() 
{
 	SPI_masterinittransmit();
 	
 	SPI_sendstring(u8_g_cardpin);
	
	SPI_masterendtransmit();
	
	TMR0_delayms(30);
	
	SPI_masterinittransmit();
	
	SPI_sendstring(u8_g_cardpan);
	
	SPI_masterendtransmit();
   
}