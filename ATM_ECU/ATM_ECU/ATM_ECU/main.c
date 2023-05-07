/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : ATM_ECU                              */
/**************************************************/

#include "APP/APP.h"

int main(void)
{
	APP_init(); /** INITIALIZATION **/
	
	APP_readuserpin(); /** READ USER PIN **/
	
	APP_startcardcomm();  /** START **/ 
	
	APP_getamount(); /** GET NEEDED MONEY **/


	
// 	while (1)
// 	{
// 		
// 	
// 	}
}

