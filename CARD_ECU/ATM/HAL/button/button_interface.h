/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Interface file of buttons            */
/**************************************************/

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

/** TYPE DEFINITION FOR BUTTON RETURN ERROR */
typedef enum { Button_Notpressed  , Button_pressed} button_t;


/*****************************************************************/
/* FUNCTION TO INITIALIZE THE BUTTON                             */
/* ARGUMENTS : TAKES THE BUTTON PIN                              */
/* RETURN    : void                                              */
/*****************************************************************/
void Button_init(uint8_t Button_port , uint8_t Button_pin);


/*****************************************************************/
/* FUNCTION TO CHECK THE BUTTON STATUS PRESSED OR NOT            */
/* ARGUMENTS : TAKES THE BUTTON PIN                              */
/* RETURN    : RETURNS BUTTON_t type                             */
/*****************************************************************/
button_t Is_pressed(uint8_t Button_port , uint8_t Button_pin , uint8_t * value);




#endif