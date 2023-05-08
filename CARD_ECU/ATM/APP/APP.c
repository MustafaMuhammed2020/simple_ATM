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

#include "../MCAL/uart/UART_interface.h"

#include "../MCAL/spi/SPI_interface.h"

#include "../MCAL/i2c/I2C_interface.h"
#include "../MCAL/i2c/I2C_config.h"

#include "../HAL/lcd/LCD_interface.h"

#include "../HAL/eeprom/EEPROM_interface.h"

#include "../HAL/button/button_interface.h"
#include "../HAL/button/button_config.h"


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
    TMR0_init(); /** TIMER 0 INITIALIZATION **/
	
	UART_init();  /** INITIALIZATION UART MODULE **/
	
	SPI_initmaster(); /** INITIALIZE SPI MASTER **/
	
	EEPROM_init(); /** INITIALIZE EEPROM MODULE **/
	
	Button_init(BUTTON1_PORT , BUTTON1_PIN); /** COMMUNICATION TRIGGER **/
	
	DIO_setpindir(DIO_PORTA , DIO_PIN0 , DIO_PIN_OUTPUT); /** OUTPUT PIN TO TRIGGER ATM ECU **/
	DIO_setpinvalue(DIO_PORTA , DIO_PIN0 , DIO_PIN_LOW);  /** PIN IS LOW (TRIGGER OFF)      **/
}

/** FUNCTION TO SET THE ENTRY POINT USER / PROGRAMMING OR REPROGRAMMING MODE **/
uint8_t APP_entrypoint()
{
	uint8_t u8_l_eepromcheck = 0 , u8_l_returnmode = 0 , u8_receiveddata = 0;
	
	EEPROM_readbyte(TEST_ADDRESS , &u8_l_eepromcheck , PAGE_0); /** READ THE FIRST BYTE WHICH WE WRITE TO  **/
	
	if (u8_l_eepromcheck == 0xFF) /** IF THE ADDRESS IS EMPTY **/
	{
		UART_sendstr("\r\n First insertion for this card wait to program it\r\n");
		
		u8_l_returnmode = PROGRAM_MODE ; /** RETURN THE PROGRAMMING MODE **/
	}
	
	else if(u8_l_eepromcheck == TEST_DATA) /** CARD PROGRAMMED PREVIOUSLY **/
	{
		UART_sendstr("\r\nTo reprogram your card press 2 , for user mode press 1 \r\n");
		
		UART_receivechar(&u8_receiveddata);
		
		if (u8_receiveddata == '2')
		{
			u8_l_returnmode = REPROGRAM_MODE ; /** RETURN THE REPROGRAMMING MODE **/ 
		}
		
		else if (u8_receiveddata == '1')
		{
			u8_l_returnmode = USER_MODE ; /** RETURN THE USER MODE **/
		}
		
		else 
		{
			UART_sendstr("\r\nNot valid choice\r\n");
			exit(0);
		}
	}
	
	return u8_l_returnmode ; /** RETURN THE FINAL MODE **/
}


/** FUNCTION TO PROGRAM THE CARD DATA **/
uint8_t APP_cardprogram()
{
	uint8_t u8_a_cardstatus = CARD_NOT_OK ;
	
	/** PIN NUMBER ITERATOR , CHARACTER FOUND STATUS , COUNTER FOR PIN ATTEMPTS **/
	uint8_t u8_a_num = 0 , u8_character = 0 , u8_a_try = 0; 
	
	/************************************************************************/
	/**                     PROGRAMMING THE CARD                           **/
	/************************************************************************/
	
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
			if (!((u8_g_cardpin[u8_a_num] >= 47) && (u8_g_cardpin[u8_a_num] <= 57)))
			{
				u8_character = 1 ; /** CHARACTER FOUND **/
			}
			u8_a_num++ ; /** JUMP TO THE NEXT NUMBER **/
		}
		
		u8_a_notmatched = strcmp(u8_g_cardpin , u8_g_cardpinconfirm); /** CHECK IF PIN MATCHED OR NOT **/
		
		if (u8_a_notmatched == 0 && u8_character == 0) /** IF PIN MATCHED AND NO CHARACTERS **/
		{
			UART_sendstr("\r\nData received successfully\r\n");
			u8_a_cardstatus = CARD_OK ;
			break ;
		}
		
		else /** TRY FAILED **/
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
		
    	u8_a_try++ ; /** NEXT TRY **/
		u8_a_num = 0 ; /** REINITIALIZE ITERATOR AND CHARACTER STATUS TO 0 AGAIN **/
		u8_character = 0 ;
		
	}
	
	return u8_a_cardstatus ; /** RETURN THE CARD STATUS **/
}

/** FUNCTION FOR CARD PROGRAMMING FAILURE **/
void APP_cardfailed()
{
	/** DISPLAY MESSAGE WHEN CARD PROGRAMMING FAILS **/
	UART_sendstr("\r\n Sorry card programming failed\r\n");
}

/** FUNCTION TO STORE CARD DATA IN THE EEPROM **/
void APP_storecard()
{
	/** STORE THE TEST DATA IN THE EEPROM **/
	EEPROM_writebyte(TEST_ADDRESS , TEST_DATA , PAGE_0 );
	TMR0_delayms(40);
	
	/** STORE THE TEST DATA IN THE EEPROM **/
	//EEPROM_writebyte(0x0150 , 0x34 , PAGE_0 );
	
// 	EEPROM_writebyte(CARD_PINADDRESS_0 , u8_g_cardpin[0] , PAGE_0 );
// 	TMR0_delayms(40);
// 	
// 	EEPROM_writebyte(CARD_PINADDRESS_1 , u8_g_cardpin[1] , PAGE_0 );
// 	TMR0_delayms(40);
// 	
// 	EEPROM_writebyte(CARD_PINADDRESS_2 , u8_g_cardpin[2] , PAGE_0 );
// 	TMR0_delayms(40);
// 	
// 	EEPROM_writebyte(CARD_PINADDRESS_3 , u8_g_cardpin[3] , PAGE_0 );
// 	TMR0_delayms(40);
	
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
	/** GET PIN FROM THE EEPROM **/
	for (uint16_t counter = 0x0000 ; counter < 0x0004 ; counter++)
	{
		EEPROM_readbyte(CARD_PINADDRESS_0+counter , &readpin[counter] , PAGE_0 );
		TMR0_delayms(40);
	}
	
	/** GET PAN FROM THE EEPROM **/ 
	for (uint16_t pan_counter = 0x0000 ; pan_counter < 0x0014 ; pan_counter++)
	{
		EEPROM_readbyte(CARD_PANADDRESS_0+pan_counter , &readpan[pan_counter] , PAGE_0 );
		TMR0_delayms(40);
	}	
}

APP_sendtrigger()
{
	/** ACTIVATE THE TRIGGER PIN **/
	DIO_setpinvalue(DIO_PORTA , DIO_PIN0 , DIO_PIN_HIGH);
}

/** FUNCTION TO SEND CARD DATA TO ATM ECU **/
void APP_sendcarddata() 
{
	TMR0_delayms(30);
	
 	SPI_masterinittransmit(); /** START SPI TRANSMISSION **/
 	
 	SPI_sendstring(readpin); /** SEND STORED PIN TO ATM **/
	
	SPI_masterendtransmit(); /** END TRANSMISSION **/
	
	TMR0_delayms(30); /** DELAY FOR 30 MS **/
	
	SPI_masterinittransmit(); /** START SPI TRANSMISSION **/
	
	SPI_sendstring(readpan); /** SEND STORED PIN TO ATM **/
	
	SPI_masterendtransmit();/** END TRANSMISSION **/
   
}