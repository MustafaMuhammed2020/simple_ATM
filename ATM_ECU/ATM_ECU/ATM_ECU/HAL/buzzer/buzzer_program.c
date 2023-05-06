/***************************************************************/
/** Author  : Mustafa Mohammed Abdou                          **/
/** Date    : 20 April, 2023                                  **/
/** Version : V01                                             **/
/** Hint    : implementation of buzzer APIs                   **/
/***************************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE INTERFACE FILE OF LOWER LAYERS **/
#include "../../MCAL/dio/DIO_interface.h"

/** INCLUDE DRIVER FILES */
#include "buzzer_interface.h"
#include "buzzer_private.h"
#include "buzzer_config.h"



/*******************************************************/
/** FUNCTION TO INITIALIZE BUZZER                     **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_init()
{
	/** SET THE DIRECTION OF BUZZER PIN AS OUTPUT **/
	DIO_setpindir(BUZZ_PORT , BUZZ_PIN , DIO_PIN_OUTPUT);
}

/*******************************************************/
/** FUNCTION TO PUT BUZZER IN ON STATUS               **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_on()
{
	/** SET THE BUZZER PIN AS HIGH **/
	DIO_setpinvalue(BUZZ_PORT , BUZZ_PIN , DIO_PIN_HIGH);
}


/*******************************************************/
/** FUNCTION TO STOP BUZZER                           **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_off()
{
	/** SET THE BUZZER PIN AS LOW **/
	DIO_setpinvalue(BUZZ_PORT , BUZZ_PIN , DIO_PIN_LOW);
}
