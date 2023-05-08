/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 8 , May 2023                                         */
/* Version : V01                                                  */
/* Hint    : data base file                                       */
/******************************************************************/

#ifndef DATA_BASE_H_
#define DATA_BASE_H_

#include "standard_types.h"

/** MACROS TO DEFINE CARD STATUS **/
#define BLOCKED   0
#define RUNNING   1

#define NUMBER_OF_CARDS  3

/** CREATE TYPE DEFINITION FOR CARD MODULE **/
typedef struct{
	
	float32 f_a_cardbalance ;    /** CARD BALANCE **/
	uint8_t  en_a_cardstatus ;   /** CARD STATUS  **/
	uint8_t  u8_a_card_pan[20] ; /** CARD PAN     **/ 
	
	} CARD; 

/** ARRAY FOR CARDS **/
CARD database[3] = { { 6000.00 , BLOCKED , "1234567890123214567"}, 
                     { 10000.00 , RUNNING , "1234567890123456789"},
					 { 9000.00 , RUNNING , "1001355678200976512"} };

	

#endif /* DATA_BASE_H_ */