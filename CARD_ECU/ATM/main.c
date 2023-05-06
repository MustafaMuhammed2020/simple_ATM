/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : Card_ECU                             */
/**************************************************/
 
#include "APP/APP.h"

int main(void)
{
	APP_init(); /** INITIALIZATION **/
	APP_cardprogram(); /** PROGRAMMING THE CARD **/
    APP_storecard(); /** STORE CARD DATA IN EEPROM **/
	APP_getcarddata(); /** GET CARD DATA FROM THE EEPROM **/
    APP_sendcarddata(); /** START THE **/
//     while (1) 
//     {
// 		
//     }
}

