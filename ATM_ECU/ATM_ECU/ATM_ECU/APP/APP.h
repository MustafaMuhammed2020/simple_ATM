/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_

#define bell  0 /** MACRO FOR BELL **/
#define MAX_AMOUNT     5000
#define DECIMEL_POS    4
#define AMOUNT_DIGITS  6
#define MAX_TRY        2

/** INITIALIZATION FUNCTION **/
void APP_init(void);

/** FUNCTION TO READ USER PIN **/
void APP_readuserpin(void);

/** FUNCTION TO COMMUNICATE WITH CARD ECU TO GET PIN/PAN **/
void APP_startcardcomm(void);

/** FUNCTION TO GET THE AMOUNT OF MONEY NEEDED **/
void APP_getamount(void);

/** FUNCTION TO VALIDATE THE CARD FROM THE DATABASE **/
void APP_cardvalidate(void);

/** FUNCTION TO VERIFY USER PIN **/
//void APP_pinvalidate();

#endif /* APP_H_ */