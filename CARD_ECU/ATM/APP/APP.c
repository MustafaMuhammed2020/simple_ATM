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
#include "../MCAL/uart/UART_interface.h"
#include "../MCAL/spi/SPI_interface.h"

#include "../HAL/lcd/LCD_interface.h"
#include "../HAL/eeprom/EEPROM_interface.h"
#include "../HAL/button/button_interface.h"
#include "../HAL/button/button_config.h"


/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[PIN_NUM_SIZE] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/ 
uint8_t u8_g_cardpan[PAN_NUM_SIZE] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/
uint8_t u8_g_cardpinconfirm[PIN_NUM_SIZE] = "0000";           /** GLOBAL VARIABLE TO HOLD PAN CONFIRMATION **/

uint8_t u8_a_notmatched = 0 ;

uint8_t readpin[PIN_NUM_SIZE] = "0000" ;
uint8_t readpan[PAN_NUM_SIZE] = "0000000000000000000";

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
	
	if (u8_l_eepromcheck == EMPTY_ADDRESS) /** IF THE ADDRESS IS EMPTY **/
	{
		UART_sendstr("\r\n First insertion for this card wait to program it\r\n");
		
		u8_l_returnmode = PROGRAM_MODE ; /** RETURN THE PROGRAMMING MODE **/
	}
	
	else if(u8_l_eepromcheck == TEST_DATA) /** CARD PROGRAMMED PREVIOUSLY **/
	{
		UART_sendstr("\r\nTo reprogram your card press 2 , for user mode press 1 \r\n");
		
		UART_receivechar(&u8_receiveddata);
		
		if (u8_receiveddata == CARD_REPROGRAM) /** USER SELECTED PROGRAMMING MODE **/
		{
			u8_l_returnmode = REPROGRAM_MODE ; /** RETURN THE REPROGRAMMING MODE **/ 
		}
		
		else if (u8_receiveddata == CARD_USE) /** USER SELECTED TO ENTER USER MODE **/
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
	
	while (u8_a_try <= MAX_PIN_ATTEMPT) /** JUST TWO ATTEMPTS TO SET CARD PIN **/
	{
		UART_sendstr("\r\nPlease enter new 4-numbers PIN\r\n");/** ASK USER TO INTER CARD PIN **/
		UART_receivestr(&u8_g_cardpin);  /** RECEIVE PIN FROM USER **/
		
		UART_sendstr("\r\nPlease confirm your PIN\r\n");/** ASK USER TO INTER CARD PIN **/
		UART_receivestr(&u8_g_cardpinconfirm); /** RECEIVE PIN CONFIRMATION **/
		
		/** CHECK IF CHARACTER ENTERED **/
		while(u8_a_num < PIN_SIZE)
		{
			/** VALIDATE THE USER INPUT AS NUMBERS ONLY FROM 0 to 9 **/
			if (!((u8_g_cardpin[u8_a_num] >= ZERO_ASCII) && (u8_g_cardpin[u8_a_num] <= NINE_ASCII)))
			{
				u8_character = TRUE ; /** CHARACTER FOUND **/
			}
			u8_a_num++ ; /** JUMP TO THE NEXT NUMBER **/
		}
		
		u8_a_notmatched = strcmp(u8_g_cardpin , u8_g_cardpinconfirm); /** CHECK IF PIN MATCHED OR NOT **/
		
		if (u8_a_notmatched == FALSE && u8_character == FALSE) /** IF PIN MATCHED AND NO CHARACTERS **/
		{
			UART_sendstr("\r\nData received successfully\r\n");
			u8_a_cardstatus = CARD_OK ;
			break ;
		}
		
		else /** TRY FAILED **/
		{
			if (u8_character == TRUE) /** USER ENTERED CHARACTER **/
			{
				UART_sendstr("\r\n Letters not allowed , numbers only\r\n");
			}
			else /** PIN NOT MATCHED **/
			{
				UART_sendstr("\r\nPIN didn't match !\r\n");/** ASK USER TO INTER CARD PIN **/
			}
		}
		
    	u8_a_try++       ;   /** NEXT TRY **/
		u8_a_num = FALSE     ;   /** REINITIALIZE ITERATOR AND CHARACTER STATUS TO 0 AGAIN **/
		u8_character = FALSE ;
		
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
	uint16_t pin_counter = 0x0000 ;
	uint16_t pan_counter = 0x0000 ;
	
	
	/** STORE THE TEST DATA IN THE EEPROM **/
	EEPROM_writebyte(TEST_ADDRESS , TEST_DATA , PAGE_0 );
	TMR0_delayms(MS_DELAY_40);
	
	/** STORE PIN NUMBER **/
	for (pin_counter = PIN_FIRST_DIGIT ; pin_counter < LAST_PIN_DIGIT ; pin_counter++)
	{
		EEPROM_writebyte(CARD_PINADDRESS_0+pin_counter , u8_g_cardpin[pin_counter] , PAGE_0 );
		TMR0_delayms(MS_DELAY_20);
	}

	/** STORE PAN NUMBER **/
	for (pan_counter = PAN_FIRST_DIGIT ; pan_counter < LAST_PAN_DIGIT ; pan_counter++)
	{
		EEPROM_writebyte(CARD_PANADDRESS_0+pan_counter , u8_g_cardpan[pan_counter] , PAGE_0 );
		TMR0_delayms(MS_DELAY_20);
	}

}

/** FUNCTION TO READ CARD DATA FROM EEPROM **/
void APP_getcarddata(void)
{
	uint16_t pin_counter = 0x0000 ;
	uint16_t pan_counter = 0x0000 ;
	
	/** GET PIN FROM THE EEPROM **/
	for (pin_counter = PIN_FIRST_DIGIT ; pin_counter < LAST_PIN_DIGIT ; pin_counter++)
	{
		EEPROM_readbyte(CARD_PINADDRESS_0+pin_counter , &readpin[pin_counter] , PAGE_0 );
		TMR0_delayms(MS_DELAY_40);
	}
	
	/** GET PAN FROM THE EEPROM **/ 
	for (pan_counter = PAN_FIRST_DIGIT ; pan_counter < LAST_PAN_DIGIT ; pan_counter++)
	{
		EEPROM_readbyte(CARD_PANADDRESS_0+pan_counter , &readpan[pan_counter] , PAGE_0 );
		TMR0_delayms(MS_DELAY_40);
	}	
}

void APP_sendtrigger(void)
{
	/** ACTIVATE THE TRIGGER PIN **/
	DIO_setpinvalue(DIO_PORTA , DIO_PIN0 , DIO_PIN_HIGH);
}

/** FUNCTION TO SEND CARD DATA TO ATM ECU **/
void APP_sendcarddata() 
{
	TMR0_delayms(MS_DELAY_30);
	
 	SPI_masterinittransmit(); /** START SPI TRANSMISSION **/
 	
 	SPI_sendstring(readpin); /** SEND STORED PIN TO ATM **/
	
	SPI_masterendtransmit(); /** END TRANSMISSION **/
	
	TMR0_delayms(MS_DELAY_30); /** DELAY FOR 30 MS **/
	
	SPI_masterinittransmit(); /** START SPI TRANSMISSION **/
	
	SPI_sendstring(readpan); /** SEND STORED PIN TO ATM **/
	
	SPI_masterendtransmit();/** END TRANSMISSION **/
   
}