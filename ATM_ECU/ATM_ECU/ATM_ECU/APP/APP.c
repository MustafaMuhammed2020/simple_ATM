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
#include "../HAL/button/button_interface.h"
#include "../HAL/button/button_config.h"
#include "../HAL/lcd/LCD_interface.h"
#include "../HAL/keypad/KEYPAD_interface.h"
#include "../HAL/buzzer/buzzer_interface.h"
#include "../HAL/buzzer/buzzer_config.h"

/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[5] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/
uint8_t u8_g_cardpan[20] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/

uint8_t u8_g_userpin[5] = "0000"; /** GLOBAL VARIABLE TO GET USER PIN **/

uint8_t u8_a_pressednum = 0 ; /** VARIABLE TO STORE THE PRESSED NUM FROM KEYPAD **/

KEYPAD_readError u8_returnstatus = KEYPAD_readFail ; /** VARIABLE FOR KEYPAD STATUS **/

uint8_t counter , number = 0 , status = 0 , u8_a_pintry = 0 , u8_a_pinnotmatched = 1 , triggerstatus = 0;


/** INITIALIZATION FUNCTION **/
void APP_init()
{
	//Button_init(BUTTON1_PORT , BUTTON1_PIN); /** ZERO/SET BUTTON **/
	Button_init(BUTTON2_PORT , BUTTON2_PIN); /** START TRIGGER FROM CARD ECU **/
	
	BUZZ_init(); /** ALARM INITIALIZATION **/
	BUZZ_off();  /** ALARM IS OFF **/
	
	DIO_setpindir(DIO_PORTB , DIO_PIN0 , DIO_PIN_OUTPUT); /** TRIGGER PIN TO START COMMUNICATION **/
	DIO_setpinvalue(DIO_PORTB , DIO_PIN0 , DIO_PIN_LOW);  /** INITIAL VALUE IS ZERO **/
	
	TMR0_init(); /** TIMER 0 INITIALIZATION **/
	
	SPI_initslave(); /** INITIALIZE SPI MASTER **/
	
	KEYPAD_init(); /** INITIALIZE THE KEYPAD **/
	
	LCD_init();  /** INITIALIZE LCD **/
	TMR0_delayms(20); /** SET DELAY FOR LCD INITILIZATION **/
	
	LCD_writestr(" WELCOME TO ATM !"); /** DISPLAY WELCOME MESSAGE FOR 1 SEC **/
	TMR0_delayms(500);
	
	LCD_sendcmd(LCD_CLEAR);
	TMR0_delayms(20);
	
	LCD_goto(0 ,1);
	LCD_writestr("Insert A Card"); /** ASK USER TO INSERT HIS CARD **/
	
	do  /** WAIT FOR THE CARD ECU TRIGGER **/
	{
		Is_pressed(BUTTON2_PORT , BUTTON2_PIN , &triggerstatus);
	} while (triggerstatus == 0);
	
	/** WAIT UNTILL TRIGGER ACTION FROM THE CARD ECU **/
	LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
}

/** FUNCTION TO READ USER PIN **/
void APP_readuserpin()
{
	LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
	LCD_goto(0 , 1);
	LCD_writestr("Enter Your PIN"); /** SAK USER TO INSERT CARD PIN **/
	
	for(counter = 0 ; counter < 4 ; counter++)
	{
		while ((KEYPAD_read(&u8_a_pressednum) == KEYPAD_readFail)); /** POLLING UNTILL NUMBER PRESSED **/
		
		LCD_goto(1 , counter); /** DISPLAY * WITH EACH PRESSED NUMBER **/
		LCD_writechar('*');
		
		u8_g_userpin[counter] = u8_a_pressednum ; /** STORE THE PRESSED NUMBER **/
		TMR0_delayms(200);
		
		u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
	}
	
	do /** LONG PRESS FOR 2 SECONDS ON ZERO **/
	{
		KEYPAD_read(&status); /** READ THE ZERO FROM KEYPAD **/
		TMR0_delayms(1000);   /** DELAY FOR 2000 SECONDS    **/
		KEYPAD_read(&status); /** READ THE ZERO FROM KEYPAD **/
		
	} while (status != '0');
	
}

/** FUNCTION TO COMMUNICATE WITH CARD ECU TO GET PIN/PAN **/
void APP_startcardcomm()
{
	/** INITIATE COMMUNICATION BETWEEN THE CARD ECU VIA TRIGGER ACTION **/
	DIO_setpinvalue(DIO_PORTB , DIO_PIN0 , DIO_PIN_HIGH);
	
	SPI_receivestring(&u8_g_cardpin); /** RECEIVE THE PIN **/
	TMR0_delayms(30);
	
	SPI_receivestring(&u8_g_cardpan); /** RECEIVE THE PAN **/
	
	/** VERIFY THE USER INSERTED PIN **/
	u8_a_pinnotmatched = 1 ;
	while (u8_a_pintry <= 1 && u8_a_pinnotmatched != 0  ) /** CHECK PIN MATCHING FOR TWO TIMES **/
	{
		u8_a_pinnotmatched = strcmp(u8_g_cardpin , u8_g_userpin); /** COMPARE THE TWO PINs **/
		
		if (u8_a_pinnotmatched == 0) /** PIN MATCHED **/
		{
			break ;
		}
		
		else /** PIN NOT MATCHED **/
		{
			LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
			TMR0_delayms(20);
			
			LCD_goto(0,0);
			LCD_writestr("PIN NOT MATCHED !"); /** DISPLAY MESSAGE FOR 1 SEC **/
			TMR0_delayms(500);
			
			LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
			TMR0_delayms(20);
			
			APP_readuserpin(); /** READ THE PIN AGAIN **/
		}
		
		u8_a_pintry++ ; /** TRY FOR MORE ATTEMPT **/
		
		if (u8_a_pintry > 1)
		{
			while (1)
			{
				BUZZ_on();
				TMR0_delayms(500);
				
				BUZZ_off();
				TMR0_delayms(500);
			}
		}
	}
}


/** FUNCTION TO GET THE AMOUNT OF MONEY NEEDED **/
void APP_getamount()
{
	uint16_t u16_l_amout = 0 , u8_a_pos = 1000 ;
	
	LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
	LCD_writestr("ENTER THE AMOUNT"); /** ASK USER TO ENTER THE AMOUNT NEEDED **/
	TMR0_delayms(200);
	
	LCD_goto(1,2);

	for(counter = 0 ; counter <= 6 ; counter++)
	{
		u8_a_pressednum = KEYPAD_readFail ;
		
		if (counter == 4)
		{
			LCD_writechar('.'); /** DECIMEL POINT **/
			u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
			continue ;
		}
		
		while ((KEYPAD_read(&u8_a_pressednum) == KEYPAD_readFail)); /** POLLING UNTILL NUMBER PRESSED **/
		
		TMR0_delayms(200);
		LCD_writechar(u8_a_pressednum);
		
		if (counter < 4)
		{
			u16_l_amout += (u8_a_pressednum - 48) * u8_a_pos ; /** CHARACTER TO INTEGER **/
			u8_a_pos /= 10 ; /** GO TO THE NEXT POSITION **/
		}
		
		u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
	}
	
	TMR0_delayms(100);
	
	if (u16_l_amout > 5000)
	{
		LCD_sendcmd(LCD_CLEAR);
		TMR0_delayms(20);
		
		LCD_goto(0 , 0);
		LCD_writestr("MAX TRANSACTION ");
		
		LCD_goto(1 , 0);
		LCD_writestr("AMOUNT EXCEEDED");
		
		TMR0_delayms(1000);
	}
	
}

