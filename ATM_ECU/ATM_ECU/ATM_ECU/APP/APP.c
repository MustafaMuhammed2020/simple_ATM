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

#include "../SERVICE/data_base.h" /** DATA BASE FILE **/

/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t u8_g_cardpin[5] = "0000";                  /** GLOBAL VARIABLE TO HOLD THE CARD PIN     **/
uint8_t u8_g_cardpan[20] = "0000000000000000000";  /** GLOBAL VARIABLE TO HOLD THE CARD PAN     **/
uint8_t u8_g_userpin[5] = "0000"; /** GLOBAL VARIABLE TO GET USER PIN **/

uint8_t u8_g_bell[8] =  { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00}; /** BELL SHAPE PATTERN **/

uint8_t u8_a_pressednum = 0 ; /** VARIABLE TO STORE THE PRESSED NUM FROM KEYPAD **/

KEYPAD_readError u8_returnstatus = KEYPAD_readFail ; /** VARIABLE FOR KEYPAD STATUS **/

uint8_t counter , number = 0 , status = 0 , u8_a_pintry = 0 , u8_a_pinnotmatched = 1 , triggerstatus = 0;

uint16_t u16_g_amount = 0 ; /** AMOUNT NEEDED BY USER **/

/** INITIALIZATION FUNCTION **/
void APP_init()
{
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
	
	LCD_writecustomchar(u8_g_bell , bell); /** STORE THE BELL SHAPE IN CGRAM OF LCD **/
	
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
	
	LCD_goto(0 , 0);
	LCD_writestr("Enter Your PIN"); /** SAK USER TO INSERT CARD PIN **/
	
	for(counter = 0 ; counter < 4 ; counter++)
	{
		while ((KEYPAD_read(&u8_a_pressednum) == KEYPAD_readFail)); /** POLLING UNTILL NUMBER PRESSED **/
		
		LCD_goto(1 , counter+4); /** DISPLAY * WITH EACH PRESSED NUMBER **/
		LCD_writechar('*');
		
		u8_g_userpin[counter] = u8_a_pressednum ; /** STORE THE PRESSED NUMBER **/
		TMR0_delayms(200);
		
		u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
	}
	
	do /** LONG PRESS FOR 2 SECONDS ON ZERO **/
	{
		KEYPAD_read(&status); /** READ THE ZERO FROM KEYPAD **/
		TMR0_delayms(940);   /** DELAY FOR 2000 SECONDS    **/
		KEYPAD_read(&status); /** READ THE ZERO FROM KEYPAD **/
		
	} while (status != '0');
	
}

/** FUNCTION TO COMMUNICATE WITH CARD ECU TO GET PIN/PAN **/
void APP_startcardcomm()
{
	/** INITIATE COMMUNICATION BETWEEN THE CARD ECU VIA TRIGGER ACTION **/
	DIO_setpinvalue(DIO_PORTB , DIO_PIN0 , DIO_PIN_HIGH);
	
	TMR0_delayms(30);
	
	SPI_receivestring(&u8_g_cardpin); /** RECEIVE THE PIN **/
	TMR0_delayms(30);

	SPI_receivestring(&u8_g_cardpan); /** RECEIVE THE PAN **/
	
	/** VERIFY THE USER INSERTED PIN **/
	u8_a_pinnotmatched = 1 ;
	while (u8_a_pintry <= MAX_TRY && u8_a_pinnotmatched != 0  ) /** CHECK PIN MATCHING FOR TWO TIMES **/
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
			
			u8_a_pintry++ ; /** TRY FOR MORE ATTEMPT **/ /** 0 , 1 , 2 **/
			
			if (u8_a_pintry > MAX_TRY) /** WHEN THIRD TRY IS WRONG **/
			{
				while (1)
				{
					LCD_goto(0,0);
					LCD_writestr("PIN NOT MATCHED !"); /** DISPLAY MESSAGE **/
					
					BUZZ_on();
					TMR0_delayms(500);
					
					BUZZ_off();
					TMR0_delayms(500);
				}
			}
			
			APP_readuserpin(); /** READ THE PIN AGAIN **/ 
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

	for(counter = 0 ; counter <= AMOUNT_DIGITS ; counter++)
	{
		u8_a_pressednum = KEYPAD_readFail ;
		
		if (counter == DECIMEL_POS)
		{
			LCD_writechar('.'); /** DECIMEL POINT **/
			u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
			continue ;
		}
		
		while ((KEYPAD_read(&u8_a_pressednum) == KEYPAD_readFail)); /** POLLING UNTILL NUMBER PRESSED **/
		
		TMR0_delayms(200);
		LCD_writechar(u8_a_pressednum);
		
		if (counter < DECIMEL_POS) 
		{
			u16_l_amout += (u8_a_pressednum - 48) * u8_a_pos ; /** CHARACTER TO INTEGER **/
			u8_a_pos /= 10 ; /** GO TO THE NEXT POSITION **/
		}
		
		u16_g_amount = u16_l_amout ; /** STORE THE NEEDED AMOUNT GLOBALLY **/
		
		u8_returnstatus = KEYPAD_readFail; /** REINITIALIZE STATE TO ACCEPT NEW NUMBER **/
	}

}

/** FUNCTION TO VALIDATE THE CARD DATA **/
void APP_cardvalidate(void)
{
	uint8_t u8_l_cards = 0  , u8_l_panstate = 1 , u8_l_cardnum = 0; /** COUNTER FOR NUMBER OF CARDS **/
	
	for (u8_l_cards = 0 ; u8_l_cards < NUMBER_OF_CARDS ; u8_l_cards++)
	{
		/** VALIDATING CARD PAN **/
		u8_l_panstate = strcmp(database[u8_l_cards].u8_a_card_pan , u8_g_cardpan);
		
		if (!u8_l_panstate) /** PAN FOUND IN THE DATABASE **/
		{
			u8_l_cardnum = u8_l_cards ; /** GET THE CARD INDEX IN THE DATABASE **/ 
			break ; 
		}
	}
	
	if (!u8_l_panstate) /** CONTINUE ONLY IF THE CARD IS FOUND IN THE DATABASE **/
	{
		/** CHECK IF THE CARD RUNNING / BLOCKED **/
		if(database[u8_l_cardnum].en_a_cardstatus == BLOCKED)
		{
			BUZZ_on();  /** ALARM IS ON **/
			
			/** DISPLAY STATUS OVER THE LCD **/
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			LCD_goto(0,0);
			LCD_writestr("CARD IS STOLEN");
		}
		
		/** CHECK IF NEEDED AMOUNT MORE THAN THE TRANSACTION AMOUNT **/
		else if (u16_g_amount > MAX_AMOUNT) /** MAX AMOUNT FOR EACH TRANSACTION IS 5000 **/
		{
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			LCD_goto(0 , 0);
			LCD_writestr("MAX TRANSACTION ");
			
			LCD_goto(1 , 0);
			LCD_writestr("AMOUNT EXCEEDED");
			
			TMR0_delayms(1000);
		}
		
		/** CHECK IF BALANCE IS ENOUGH **/
		else if (database[u8_l_cardnum].f_a_cardbalance < u16_g_amount)
		{
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			LCD_goto(0,1);
			LCD_writestr("INSUFFICIENT ");
			
			LCD_goto(1,3);
			LCD_writestr("FUND");
		}
		
		else
		{
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			LCD_goto(0,3);
			LCD_writestr("APPROVED");
			LCD_goto(1,3);
			LCD_writestr("TRANSACTION");
			
			TMR0_delayms(1000);
			
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			/** CALCULATE THE NEW BALANCE **/
			database[u8_l_cardnum].f_a_cardbalance -= u16_g_amount ; 
			
			LCD_goto(0,0);
			LCD_writestr("NEW BALANCE :");
			LCD_goto(1,4);
			LCD_writeint(database[u8_l_cardnum].f_a_cardbalance);
			
			TMR0_delayms(1000);
			
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			LCD_goto(0,0);
			LCD_writestr("EJECTING CARD");
		}
		
	}
	
	else
	{
		BUZZ_on();  /** ALARM IS ON **/
		
		/** DISPLAY STATUS OVER THE LCD **/
		LCD_sendcmd(LCD_CLEAR);
		TMR0_delayms(20);
		
		LCD_goto(0,0);
		LCD_writestr("THIS IS A");
		LCD_goto(1,0);
		LCD_writestr("FRAUD CARD");
		
		/** DISPLAY BELL SHAPE **/
		LCD_goto(0 , 15);
		LCD_writechar(bell);
	}
}

