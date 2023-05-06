/***************************************************************/
/** Author  : Mustafa Mohammed Abdou                          **/
/** Date    : 20 April, 2023                                  **/
/** Version : V01                                             **/
/** Hint    : APIs of buzzer                                  **/
/***************************************************************/

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

/*******************************************************/
/** FUNCTION TO INITIALIZE BUZZER                     **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_init();

/*******************************************************/
/** FUNCTION TO PUT BUZZER IN ON STATUS               **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_on();


/*******************************************************/
/** FUNCTION TO STOP BUZZER                           **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : VOID                                 **/
/*******************************************************/
void BUZZ_off();



#endif /* BUZZER_INTERFACE_H_ */