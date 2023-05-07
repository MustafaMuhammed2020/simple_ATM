/*
 * File: keypad.c
 * Created Date: Tuesday, April 18th 2023, 11:14:04 pm
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYER INTERFACE FILES **/
#include "../../MCAL/dio/DIO_interface.h"


/** INCLUDE DRIVER FILES **/
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"


#define ROWS_SIZE 4
#define COLUMNS_SIZE 3

/***************************************************************************/
/** @brief  Keypad initialization                                          */
/** @param  void                                                           */
/** @return KEYPAD_initSuccess                                             */
/** @return KEYPAD_initFail                                                */
/***************************************************************************/
KEYPAD_initError KEYPAD_init(void)
{
    /*Rows direction initialization*/
    DIO_setpindir(ROW_PORT_DATA, R1 , DIO_PIN_OUTPUT);
	DIO_setpindir(ROW_PORT_DATA, R2 , DIO_PIN_OUTPUT);
	DIO_setpindir(ROW_PORT_DATA, R3 , DIO_PIN_OUTPUT);
	DIO_setpindir(DIO_PORTD, R4 , DIO_PIN_OUTPUT);
	
    /*Columns direction initialization*/
	DIO_setpindir(COLUMN_PORT_DATA , C1 , DIO_PIN_INPUT);
	DIO_setpindir(COLUMN_PORT_DATA , C2 , DIO_PIN_INPUT);
	DIO_setpindir(COLUMN_PORT_DATA , C3 , DIO_PIN_INPUT);
	
    /*Initial pin values*/
    #if CONNECTION == 'D'
    DIO_setpinvalue(ROW_PORT_DATA , R1 ,  DIO_PIN_LOW);
	DIO_setpinvalue(ROW_PORT_DATA , R2 ,  DIO_PIN_LOW);
	DIO_setpinvalue(ROW_PORT_DATA , R3 ,  DIO_PIN_LOW);
	DIO_setpinvalue(DIO_PORTD , R4 ,  DIO_PIN_LOW);
	

    #elif CONNECTION == 'U'
	
	DIO_setpinvalue(ROW_PORT_DATA , R1 , DIO_PIN_HIGH);
	DIO_setpinvalue(ROW_PORT_DATA , R2 , DIO_PIN_HIGH);
	DIO_setpinvalue(ROW_PORT_DATA , R3 , DIO_PIN_HIGH);
	DIO_setpinvalue(DIO_PORTD , R4 , DIO_PIN_HIGH);
	
	DIO_setpinvalue(COLUMN_PORT_DATA , C1 , DIO_PIN_HIGH);
	DIO_setpinvalue(COLUMN_PORT_DATA , C2 , DIO_PIN_HIGH);
	DIO_setpinvalue(COLUMN_PORT_DATA , C3 , DIO_PIN_HIGH);
	
    #endif
    return KEYPAD_initSuccess;
}

/***************************************************************************/
/** @brief Reads keypad strokes                                            */
/** @param *u8_a_value refrence to store the read value in                 */
/** @return KEYPAD_readSuccess                                             */
/** @return KEYPAD_readFail                                                */
/***************************************************************************/
KEYPAD_readError KEYPAD_read(uint8_t *u8_a_value)
{
    uint8_t u8_a_rowiterator = 0 ;
    uint8_t u8_a_coulumniterator = 0 ;

    #if CONNECTION == 'U'
    #define u8_l_readCheck DIO_PIN_LOW
    #define u8_l_pinValue  DIO_PIN_LOW
   
    #elif CONNECTION == 'D'
    #define u8_l_readCheck DIO_PIN_HIGH
    #define u8_l_pinValue  DIO_PIN_HIGH
    #endif

    uint8_t u8_l_Rows[ROWS_SIZE] = {R1, R2, R3};
    uint8_t u8_l_Columns[COLUMNS_SIZE] = {C1, C2, C3};

    for (u8_a_rowiterator = 0; u8_a_rowiterator < ROWS_SIZE; u8_a_rowiterator++)
    {
		if (u8_a_rowiterator == 3 )
		{
			DIO_setpinvalue(DIO_PORTD , DIO_PIN0, u8_l_pinValue);
		}
		else
		{
			DIO_setpinvalue(ROW_PORT_DATA , u8_l_Rows[u8_a_rowiterator] , u8_l_pinValue);
		}

        for (u8_a_coulumniterator = 0; u8_a_coulumniterator < COLUMNS_SIZE; u8_a_coulumniterator++)
        {
            DIO_readpin(COLUMN_PORT_DATA , u8_l_Columns[u8_a_coulumniterator] , u8_a_value);
            if (*u8_a_value == u8_l_readCheck)
            {
                if (u8_a_rowiterator == 0)
                {
                    if (u8_a_coulumniterator == 0)
                    {
                        *u8_a_value = '1' ;
                    }
                    else if (u8_a_coulumniterator == 1)
                    {
                        *u8_a_value = '2' ;
                    }
                    else if (u8_a_coulumniterator == 2)
                    {
                        *u8_a_value = '3' ;
                    }
                }

                else if (u8_a_rowiterator == 1)
                {
                    if (u8_a_coulumniterator == 0)
                    {
                        *u8_a_value = '4' ;
                    }
                    else if (u8_a_coulumniterator == 1)
                    {
                        *u8_a_value = '5' ;
                    }
                    else if (u8_a_coulumniterator == 2)
                    {
                        *u8_a_value = '6' ;
                    }
                }

                else if (u8_a_rowiterator == 2)
                {
                    if (u8_a_coulumniterator == 0)
                    {
                        *u8_a_value = '7' ;
                    }
                    else if (u8_a_coulumniterator == 1)
                    {
                        *u8_a_value = '8' ;
                    }
                    else if (u8_a_coulumniterator == 2)
                    {
                        *u8_a_value = '9' ;
                    }
                }
				
				else if (u8_a_rowiterator == 3)
				{
					if (u8_a_coulumniterator == 0)
					{
						*u8_a_value = '0' ;
					}
				}
				if (u8_a_rowiterator == 3)
				{
					DIO_togglepin( DIO_PORTD , DIO_PIN0);
					return KEYPAD_readSuccess;
				}
				else
				{
					
					DIO_togglepin( ROW_PORT_DATA , u8_l_Rows[u8_a_rowiterator] );
					return KEYPAD_readSuccess;
				}
            }
        }
		if (u8_a_rowiterator == 3)
		{
			DIO_togglepin( DIO_PORTD , DIO_PIN0);
		}
		else
		{
			DIO_togglepin( ROW_PORT_DATA , u8_l_Rows[u8_a_rowiterator] );
		}
    }
    return KEYPAD_readFail;
}