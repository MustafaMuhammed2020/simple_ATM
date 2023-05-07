/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_


/** FIRST ADDRESS OF PIN IN EEPROM **/
#define CARD_PINADDRESS_0   0x0311

/** PAGE 0 ADDRESS IN EEPROM **/
#define PAGE_0      0x00
#define PAGE_1      0x01
#define PAGE_2      0x02
#define PAGE_3      0x03


/** FIRST ADDRESS OF PAN IN EEPROM **/
#define CARD_PANADDRESS_0  0x0319


				 
/** FUNCTION FOR INITIALIZATION **/
void APP_init(void);

/** FUNCTION TO SEND CARD DATA TO ATM ECU **/
void APP_sendcarddata() ;

/** FUNCTION TO PROGRAM THE CARD DATA **/
void APP_cardprogram(void);

/** FUNCTION TO STORE CARD DATA IN THE EEPROM **/ 
void APP_storecard(void);

/** FUNCTION TO READ CARD DATA FROM EEPROM **/
void APP_getcarddata(void);

/** FUNCTION TO SEND TRIGGER TO ATM ECU **/
APP_sendtrigger();

#endif /* APP_H_ */