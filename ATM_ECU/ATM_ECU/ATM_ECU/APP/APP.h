/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_

/** INITIALIZATION FUNCTION **/
void APP_init(void);

/** FUNCTION TO READ USER PIN **/
void APP_readuserpin(void);

/** FUNCTION TO COMMUNICATE WITH CARD ECU TO GET PIN/PAN **/
void APP_startcardcomm(void);

/** FUNCTION TO GET THE AMOUNT OF MONEY NEEDED **/
void APP_getamount();

/** FUNCTION TO VERIFY USER PIN **/
//void APP_pinvalidate();

#endif /* APP_H_ */