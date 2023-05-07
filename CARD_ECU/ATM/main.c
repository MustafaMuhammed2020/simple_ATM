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
	APP_init();        /** INITIALIZATION **/
	APP_cardprogram(); /** PROGRAMMING THE CARD **/
    APP_storecard();   /** STORE CARD DATA IN EEPROM **/
	APP_getcarddata(); /** GET CARD DATA FROM THE EEPROM **/
	APP_sendtrigger(); /** SEND TRIGGER TO ATM ECU **/
	
	do
	{
		Is_pressed(BUTTON1_PORT , BUTTON1_PIN , &u8_a_commtrig);
	} while (u8_a_commtrig == 0); /** UNTILL COMMUNICATION INITIATED **/
	
	APP_sendcarddata(); /** START THE **/
	
	
//     while (1) 
//     {
// 		
//     }

}

