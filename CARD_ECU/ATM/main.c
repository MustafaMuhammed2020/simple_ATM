/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : Card_ECU                             */
/**************************************************/
 
#include "APP/APP.h"

int main(void)
{
	APP_init();
	APP_cardprogram();
    APP_storecard();
	APP_getcarddata();
    APP_start();
    while (1) 
    {
		
    }
}

