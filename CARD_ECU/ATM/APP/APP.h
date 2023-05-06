/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_

#include "../SERVICE/standard_types.h"

/** PIN NUMBER ADDRESSES IN EEPROM **/
#define CARD_PINADDRESS_0   0x0311
#define CARD_PINADDRESS_1   0x0313
#define CARD_PINADDRESS_2   0x0315
#define CARD_PINADDRESS_3   0x0317

/** PAGE 0 ADDRESS IN EEPROM **/
#define PAGE_0      0x00
#define PAGE_1      0x01
#define PAGE_2      0x02
#define PAGE_3      0x03

// uint16_t PANS_ADD[20] = {0x0319 , 0x031A , 0x03B , 0x031C , 0x031D , 0x031E , 0x031F , 0x0320 , 0x0321 , 0x0322 , 0x0323 , 0x0324 ,
// 0x0325 , 0x0326 , 0x0327 , 0x0328 , 0x0329 , 0x032A , 0x032B , 0x032C};


/** FIRST ADDRESS OF PAN IN EEPROM **/
#define CARD_PANADDRESS_0  0x0319
#define CARD_PANADDRESS_1  0x031A
#define CARD_PANADDRESS_2  0x031B
#define CARD_PANADDRESS_3  0x031C
#define CARD_PANADDRESS_4  0x031D
#define CARD_PANADDRESS_5  0x031E
#define CARD_PANADDRESS_6  0x031F
#define CARD_PANADDRESS_7  0x0320
#define CARD_PANADDRESS_8  0x0321
#define CARD_PANADDRESS_9  0x0322
#define CARD_PANADDRESS_10  0x0323
#define CARD_PANADDRESS_11 0x0324
#define CARD_PANADDRESS_12 0x0325
#define CARD_PANADDRESS_13 0x0326
#define CARD_PANADDRESS_14 0x0327
#define CARD_PANADDRESS_15 0x0328
#define CARD_PANADDRESS_16 0x0329
#define CARD_PANADDRESS_17 0x032A
#define CARD_PANADDRESS_18 0x032B
#define CARD_PANADDRESS_19 0x032D

				 
/** FUNCTION FOR INITIALIZATION **/
void APP_init(void);

/** MAIN PROGRAM FLOW **/
void APP_start(void) ;

/** FUNCTION TO PROGRAM THE CARD DATA **/
void APP_cardprogram(void);

/** FUNCTION TO STORE CARD DATA IN THE EEPROM **/ 
void APP_storecard(void);

/** FUNCTION TO READ CARD DATA FROM EEPROM **/
void APP_getcarddata(void);

#endif /* APP_H_ */