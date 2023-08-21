/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_

/** MACROS FOR THE CARD RETURN STATUS **/
#define CARD_OK      1
#define CARD_NOT_OK  0

/** MACRO FOR TESTING ADDRESS AND TEST DATA **/
#define TEST_ADDRESS 0x0000
#define TEST_DATA    0x12

/** MACROS FOR CARD DIFFERENT MODES **/
#define PROGRAM_MODE    0
#define USER_MODE       1
#define REPROGRAM_MODE  2

/** FIRST ADDRESS OF PIN IN EEPROM **/
#define CARD_PINADDRESS_0   0x00F0

/** PAGE 0 ADDRESS IN EEPROM **/
#define PAGE_0      0x00
#define PAGE_1      0x01
#define PAGE_2      0x02
#define PAGE_3      0x03


/** FIRST ADDRESS OF PAN IN EEPROM **/
#define CARD_PANADDRESS_0  0x00C0

#define EMPTY_ADDRESS        0xFF
#define MAX_PIN_ATTEMPT      2
#define PIN_SIZE             4
#define ZERO_ASCII           48
#define NINE_ASCII           57
#define TRUE                 1
#define FALSE                0
#define CARD_REPROGRAM       '2'
#define CARD_USE             '1'
#define LAST_PIN_DIGIT       0x0004
#define LAST_PAN_DIGIT       0x0014
#define PIN_FIRST_DIGIT      0x0000
#define PAN_FIRST_DIGIT      0x0000
#define MS_DELAY_20          20
#define MS_DELAY_30          30
#define MS_DELAY_40          40 
#define PIN_NUM_SIZE         5
#define PAN_NUM_SIZE         20
#define BTN1_PIN             0
#define BTN1_PORT            1


/** FUNCTION FOR INITIALIZATION **/
void APP_init(void);

/** FUNCTION TO SET THE ENTRY POINT USER / PROGRAMMING OR REPROGRAMMING MODE **/
uint8_t APP_entrypoint(void);

/** FUNCTION TO SEND CARD DATA TO ATM ECU **/
void APP_sendcarddata(void) ;

/** FUNCTION TO PROGRAM THE CARD DATA **/
uint8_t APP_cardprogram(void);

/** FUNCTION FOR CARD PROGRAMMING FAILURE **/
void APP_cardfailed(void);

/** FUNCTION TO STORE CARD DATA IN THE EEPROM **/ 
void APP_storecard(void);

/** FUNCTION TO READ CARD DATA FROM EEPROM **/
void APP_getcarddata(void);

/** FUNCTION TO SEND TRIGGER TO ATM ECU **/
void APP_sendtrigger(void);

#endif /* APP_H_ */