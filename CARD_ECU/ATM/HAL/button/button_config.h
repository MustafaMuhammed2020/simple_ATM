/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Configuration file of buttons        */
/**************************************************/

#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

#include "../../MCAL/dio/DIO_interface.h"

/** BUTTON 1 CONFIGURATIONS IN PORTB , PIN4  */
#define BUTTON1_PORT  DIO_PORTB 
#define BUTTON1_PIN   DIO_PIN0  


#define BUTTON2_PORT  DIO_PORTA
#define BUTTON2_PIN   DIO_PIN0

#endif