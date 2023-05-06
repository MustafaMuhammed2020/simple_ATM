/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : interface file of UART               */
/**************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define F_CPU  8000000  /** DEFINE THE CLOCK SOURCE SPEED **/

/** TYPEDEFINITION TO RETURN ERROR STATUS FORM THE FUNCTION **/
typedef enum {UART_VALID , UART_NOT_VALID}uart_errorstatus;

/** MACROS TO CONFIGURE THE UART MODE **/
#define SYNCRONOUS_MODE        0
#define ASYNCRONOUS_MODE       1

/** MACROS TO CONFIGURE THE CLOCK POLARITY IN THE SYNCRONOUS MODE **/
#define RISING_EDGE_POLARITY   0
#define FALLING_EDGE_POLARITY  1


/** MACROS TO CONFIGURE THE STOP BITS **/
#define ONE_STOP_BIT       0
#define TWO_STOP_BITS      1

/** MACROS TO CONFIGURE THE PARITY BIT **/
#define DISABLE_PARITY_BIT 0
#define EVEN_PARITY_BIT    1
#define ODD_PARITY_BIT     2

/** MACROS TO CONFIGURE THE CHARACTER SIZE **/
#define CHAR_SIZE_5BIT     0
#define CHAR_SIZE_6BIT     1
#define CHAR_SIZE_7BIT     2
#define CHAR_SIZE_8BIT     3
#define CHAR_SIZE_9BIT     4

/** MACROS TO CONFIGURE THE BAUD RATE **/
#define BAUDRATE_9600      0
#define BAUDRATE_115200    1
#define BAUDRATE_4800      2
#define BAUDRATE_2400      3


/** MACROS TO CONFIGURE THE MULTI PROCESSORS MODE **/
#define ENABLE_MULTIPROCESSOR_MODE  0
#define DISABLE_MULTIPROCESSOR_MODE 1

/** MACROS TO CONFIGURE THE DOUBLE SPEED MODE **/
#define ENABLE_DOUBLE_SPEED_MODE  0
#define DISABLE_DOUBLE_SPEED_MODE  1

/** MACROS TO CONFIGURE THE TRANSMISSION INTEURRUPT ENABLE **/
#define ENABLE_TRANSMITTING_INTERRUPT 0
#define DISABLE_TRANSMITTING_INTERRUPT 1

/** MACROS TO CONFIGURE THE RECEIVING INTERRUPT ENABLE **/
#define ENABLE_RECEIVING_INTERRUPT 0
#define DISABLE_RECEIVING_INTERRUPT 1

/** MACROS TO CONFIGURE THE UDR EMPTY INTERRUPT **/
#define ENABLE_UDR_INTERRUPT 0
#define DISABLE_UDR_INTERRUPT 1


/**************************************************************/
/** FUNCTION TO INITIALIZE THE UART                          **/
/** ARGUMENTS : VOID                                         **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/  
uart_errorstatus UART_init(void);

/**************************************************************/
/** FUNCTION TO SEND BYTE VIA UART                           **/
/** ARGUMENTS : ua_a_data                                    **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendchar(uint8_t ua_a_data);

/**************************************************************/
/** FUNCTION TO SEND STRING VIA UART                         **/
/** ARGUMENTS : ua_a_string                                  **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendstr(uint8_t * ua_a_string);

/********************************************************************/
/** FUNCTION TO RECEIVE BYTE VIA UART                              **/
/** ARGUMENTS : u8_recdata (POINTER TO STORE THE RECEIVED DATA)    **/
/** RETURNS   : uart_errorstatus                                   **/
/********************************************************************/
uart_errorstatus UART_receivechar(uint8_t * u8_a_recdata);


/***************************************************************************/
/** FUNCTION TO RECEIVE STRING VIA UART                                   **/
/** ARGUMENTS : u8_a_recstring (POINTER TO STORE THE RECEIVED DATA)       **/
/** RETURNS   : uart_errorstatus                                          **/
/***************************************************************************/
uart_errorstatus UART_receivestr(uint8_t * u8_a_recstring);


#endif /* UART_INTERFACE_H_ */