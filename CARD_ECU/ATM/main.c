/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : Card_ECU                             */
/**************************************************/

#include "SERVICE/standard_types.h"

uint8_t u8_a_commtrig = 0 ;

#include "APP/APP.h"

#include "HAL/button/button_config.h"

int main(void)
{
	uint8_t u8_a_card_valid = CARD_NOT_OK , u8_a_entrypoint ;
	
	APP_init();        /** INITIALIZATION **/
	
	u8_a_entrypoint = APP_entrypoint(); /** DECIDE THE PROGRAM ENTRY POINT **/
	
	if (u8_a_entrypoint == PROGRAM_MODE)
	{
		u8_a_card_valid = APP_cardprogram(); /** PROGRAMMING THE CARD **/
		
		if(!u8_a_card_valid) /** CARD PROGRAMMING FAILURE **/
		{
			/** DISPLAY A MESSAGE TO GET OUT OF THE SYSTEM **/
			APP_cardfailed();
			
			exit(0); /** STOP THE SYSTEM **/
		}
		
		APP_storecard();   /** STORE CARD DATA IN EEPROM **/
		
		APP_getcarddata(); /** GET CARD DATA FROM THE EEPROM **/
		
		APP_sendtrigger(); /** SEND TRIGGER TO ATM ECU **/
		
		do
		{
			Is_pressed(BUTTON1_PORT , BUTTON1_PIN , &u8_a_commtrig);
		} while (u8_a_commtrig == 0); /** UNTILL COMMUNICATION INITIATED **/
			
		APP_sendcarddata(); /** START THE **/
	}
	
	else if (u8_a_entrypoint == REPROGRAM_MODE)
	{
		u8_a_card_valid = APP_cardprogram(); /** PROGRAMMING THE CARD **/
		
		if(!u8_a_card_valid) /** CARD PROGRAMMING FAILURE **/
		{
			/** DISPLAY A MESSAGE TO GET OUT OF THE SYSTEM **/
			APP_cardfailed();
			
			exit(1); /** STOP THE SYSTEM **/
		}
		
		APP_storecard();   /** STORE CARD DATA IN EEPROM **/
		
		APP_getcarddata(); /** GET CARD DATA FROM THE EEPROM **/
		
		APP_sendtrigger(); /** SEND TRIGGER TO ATM ECU **/
		
		do
		{
			Is_pressed(BUTTON1_PORT , BUTTON1_PIN , &u8_a_commtrig);
		} while (u8_a_commtrig == 0); /** UNTILL COMMUNICATION INITIATED **/
			
		APP_sendcarddata(); /** START THE **/
	}
	
	else if (u8_a_entrypoint == USER_MODE)
	{
		APP_getcarddata(); /** GET CARD DATA FROM THE EEPROM **/
		
		APP_sendtrigger(); /** SEND TRIGGER TO ATM ECU **/
		
		do
		{
			Is_pressed(BUTTON1_PORT , BUTTON1_PIN , &u8_a_commtrig);
		} while (u8_a_commtrig == 0); /** UNTILL COMMUNICATION INITIATED **/
			
		APP_sendcarddata(); /** START THE COMMUNICATION & SEND CARD DATA **/
	}
	
//     while (1) 
//     {
// 		
//     }

}

