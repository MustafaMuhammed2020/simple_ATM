/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : implementation of UART APIs          */
/**************************************************/

/*** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYERS INTERFACE FILES **/
#include "../dio/DIO_interface.h"


/*** INCLUDE DRIVER FILES ***/
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



/**************************************************************/
/** FUNCTION TO INITIALIZE THE UART                          **/
/** ARGUMENTS : VOID                                         **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_init(void)
{
		/** SET DIRECTIONS OF TX AND RX PINS **/
		DIO_setpindir(DIO_PORTD , DIO_PIN1 , DIO_PIN_OUTPUT);  /** SET TX PIN AS OUTPUT **/
		DIO_setpindir(DIO_PORTD , DIO_PIN0 , DIO_PIN_INPUT);   /** SET RX PIN AS INPUT  **/
		
		/* Set baud rate */
// 		UBRRH = 0 ;
// 		UBRRL = (uint8_t)103 ;
// 		
// 		/* Enable receiver and transmitter */
// 		UCSRB = (1<<3)|(1<<4);
// 		
// 		/* Set frame format: 8data, 2stop bit */
// 		UCSRC = (1<<7)|(1<<2)|(3<<1);
		
// 		UBRRL = 103;       /** ASSIGN UBRRL **/
// 		UBRRH = 0 ;
		
		#if BAUDRATE_VALUE == BAUDRATE_9600
		uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
		u32_a_BRVALUE = ((80000) / (16 * 96)) - 1; /** CALCULATE THE UBRRL VALUE **/
		UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
	
		#elif BAUDRATE_VALUE == BAUDRATE_4800
		uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
		u32_a_BRVALUE = ((160000) / (16 * 48)) - 1; /** CALCULATE THE UBRRL VALUE **/
		UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
		
		#elif BAUDRATE_VALUE == BAUDRATE_2400
		uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
		u32_a_BRVALUE = ((F_CPU) / (16 * 2400)) - 1; /** CALCULATE THE UBRRL VALUE **/
		UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
		
		#elif BAUDRATE_VALUE == BAUDRATE_115200
		uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
		u32_a_BRVALUE = ((16000000) / (16 * 115200)) - 1; /** CALCULATE THE UBRRL VALUE **/
		UBRRL = u32_a_BRVALUE ;       /** ASSIGN UBRRL **/
		#endif
		
		/** ENABLE TRANSMISSION AND RECEIVING **/
		set_bit(UCSRB , 3);
		set_bit(UCSRB , 4);
		
		/** SELECT THE FIRST BIT TO WRITE TO THE UCSRC REGISTER **/
 		set_bit(UCSRC , 7);
 			
		#if CHARACTER_SIZE == CHAR_SIZE_5BIT
		clear_bit(UCSRC , 1);
		clear_bit(UCSRC , 2);
		clear_bit(UCSRB , 2);
		
		#elif CHARACTER_SIZE == CHAR_SIZE_6BIT
		set_bit(UCSRC , 1);
		clear_bit(UCSRC , 2);
		clear_bit(UCSRB , 2);
		
		#elif CHARACTER_SIZE == CHAR_SIZE_7BIT
		clear_bit(UCSRC , 1);
		set_bit(UCSRC , 2);
		clear_bit(UCSRB , 2);
		
		#elif CHARACTER_SIZE == CHAR_SIZE_8BIT
		set_bit(UCSRC , 1);
		set_bit(UCSRC , 2);
		clear_bit(UCSRB , 2);
		
		#elif CHARACTER_SIZE == CHAR_SIZE_9BIT
		set_bit(UCSRC , 1);
		set_bit(UCSRC , 2);
		set_bit(UCSRB , 2);
		#endif
		
		
		#if PARITY_BIT_MODE == DISABLE_PARITY_BIT
		clear_bit(UCSRC , 4);
		clear_bit(UCSRC , 5);
		
		#elif PARITY_BIT_MODE == EVEN_PARITY_BIT
		clear_bit(UCSRC , 4);
		set_bit(UCSRC , 5);
		
		#elif PARITY_BIT_MODE == ODD_PARITY_BIT
		set_bit(UCSRC , 4);
		set_bit(UCSRC , 5);
		#endif
		
		#if STOP_BITS == ONE_STOP_BIT
		clear_bit(UCSRC , 3);
		
		#elif STOP_BITS == TWO_STOP_BITS
		set_bit(UCSRC , 3);
		#endif
		
		/** SET THE UART SYNCRONYZATION MODE **/
		#if UART_MODE == ASYNCRONOUS_MODE
		    clear_bit(UCSRC , 6);
		  
		#elif UART_MODE == SYNCRONOUS_MODE
			/** SET THE CLOCK POLARITY IN THE SYNCRONOUS MODE **/
			#if UART_CLOCK_POLARITY == RISING_EDGE_POLARITY
			set_bit(UCSRB , 0);
		
			#elif UART_CLOCK_POLARITY == FALLING_EDGE_POLARITY
			clear_bit(UCSRB , 0);
			#endif
       		
			set_bit(UCSRC , 6);
		#endif
		
		#if DOUBLE_SPEED_MODE == ENABLE_DOUBLE_SPEED_MODE
		    set_bit(UCSRA , 1);
		
		#elif DOUBLE_SPEED_MODE == DISABLE_DOUBLE_SPEED_MODE
		     clear_bit(UCSRA , 1);
		#endif
		
		#if MULTI_PROCESSOR_MODE == ENABLE_MULTIPROCESSOR_MODE
		    set_bit(UCSRA , 0);
		
		#elif MULTI_PROCESSOR_MODE == DISABLE_MULTIPROCESSOR_MODE
		     clear_bit(UCSRA , 0);
		#endif
		
		#if RECEIVING_INTERRUPT == ENABLE_RECEIVING_INTERRUPT
     		set_bit(UCSRB , 7);
		
		#elif RECEIVING_INTERRUPT == DISABLE_RECEIVING_INTERRUPT	
		      clear_bit(UCSRB , 7);
		#endif

		#if TRANSMITTING_INTERRUPT == ENABLE_TRANSMITTING_INTERRUPT
     		set_bit(UCSRB , 6);
		
		#elif TRANSMITTING_INTERRUPT == DISABLE_TRANSMITTING_INTERRUPT	
		    clear_bit(UCSRB , 6);
		#endif
		
		#if UDR_INTERRUPT == ENABLE_UDR_INTERRUPT
		    set_bit(UCSRB , 5);
		
		#elif UDR_INTERRUPT == DISABLE_UDR_INTERRUPT
		    clear_bit(UCSRB , 5);
		#endif
		
}

/**************************************************************/
/** FUNCTION TO SEND BYTE VIA UART                           **/
/** ARGUMENTS : ua_a_data                                    **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendchar(uint8_t ua_a_data)
{
	while( ! ( UCSRA & (1 <<5))); /** HOLD HERE UNTILL DATA REGISTER IS EMPTY (DATA SENT) **/
    
	UDR = ua_a_data ; /** STORE THE DATA IN THE UDR BUFFER TO BE SENT **/
	
}

/**************************************************************/
/** FUNCTION TO SEND STRING VIA UART                         **/
/** ARGUMENTS : ua_a_string                                  **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendstr(uint8_t * ua_a_string)
{
	uint8_t u8_a_lettercounter = 0 ; /** LETTERS COUNTER **/
		
	while (ua_a_string[u8_a_lettercounter] != '\0')  /** UNTILL THE STRING ISN'T NULL **/
	{
		UART_sendchar(ua_a_string[u8_a_lettercounter]); /** SEND THE LETTER USING UART_sendchar **/
		u8_a_lettercounter++; /** JUMP TO THE NEXT LETTER **/
	}
}

/********************************************************************/
/** FUNCTION TO RECEIVE BYTE VIA UART                              **/
/** ARGUMENTS : u8_recdata (POINTER TO STORE THE RECEIVED DATA)    **/
/** RETURNS   : uart_errorstatus                                   **/
/********************************************************************/
uart_errorstatus UART_receivechar(uint8_t * u8_a_recdata)
{
	while( ! (UCSRA & (1 << 7)) ) ; /** WAIT UNTILL THE DATA RECIVE FLAG RAISED **/
	
	*u8_a_recdata =  UDR ;	/** RETURN THE DATA IN UDR **/
	
	
}

/***************************************************************************/
/** FUNCTION TO RECEIVE STRING VIA UART                                   **/
/** ARGUMENTS : u8_a_recstring (POINTER TO STORE THE RECEIVED DATA)       **/
/** RETURNS   : uart_errorstatus                                          **/
/***************************************************************************/
uart_errorstatus UART_receivestr(uint8_t * u8_a_recstring)
{
	uint8_t u8_a_lettercounter = 0 ; /** COUNTER TO LETTERS **/
	 
	//UART_receivechar(u8_a_recstring[u8_a_lettercounter]) ; /** RECEIVE THE FIRST CHARACTER **/
	
	while (u8_a_recstring[u8_a_lettercounter] != '\0') /** WHILE STRING ISN'T NULL **/
	{
		
		UART_receivechar(&u8_a_recstring[u8_a_lettercounter]); /** RECEIVE CHARACTER **/
		
		u8_a_lettercounter++ ; /** JUMP TO THE NEXT INDEX **/
		
	}
	
	//u8_a_recstring[u8_a_lettercounter] = '\0';	/** SET THE LAST CHARACTER TO NULL **/
}