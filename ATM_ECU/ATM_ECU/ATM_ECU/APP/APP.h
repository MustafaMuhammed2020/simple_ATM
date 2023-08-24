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

#define PIN_NUM_SIZE    5
#define PAN_NUM_SIZE    20
#define MS_DELAY_20     20 
#define MS_DELAY_30     30
#define MS_DELAY_500    500 
#define MS_DELAY_200    200 
#define MS_DELAY_940    940
#define MS_DELAY_1000   1000
#define LCD_POS_0       0
#define LCD_POS_1       1
#define LCD_POS_2       2
#define LCD_POS_3       3
#define LCD_POS_4       4
#define LCD_POS_15      15
#define TRUE            1
#define FALSE           0
#define DECIMEL_DOT     '.'
#define DIGIT_DIVIDER   10
#define CHAR_INT_DIFF   48
#define ZERO_CHAR       '0'
#define LAST_PIN_DIGIT   4
#define FIRST_PIN_DIGIT  0
#define BELL_SHAPE_SIZE  8
#define BELL_ROW_1       0x04
#define BELL_ROW_2       0x0E
#define BELL_ROW_3       0x0E
#define BELL_ROW_4       0x0E
#define BELL_ROW_5       0x1F
#define BELL_ROW_6       0x00
#define BELL_ROW_7       0x04
#define BELL_ROW_8       0x00


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

#endif /* APP_H_ */