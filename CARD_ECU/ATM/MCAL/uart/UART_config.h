/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : configuration file of UART           */
/**************************************************/


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*************************************************************/
/**       MACRO TO CONFIGURE THE UART OPERATING MODE        **/
/**        AVAILABLE CHOICES   1 - ASYNCRONOUS_MODE         **/
/**                            2 - SYNCRONOUS_MODE          **/
/*************************************************************/                    
#define UART_MODE  ASYNCRONOUS_MODE

/** THIS CONFIGURATION ALLOWED ONLY IN THE SYNCRONOUS MODE **/
#if UART_MODE == SYNCRONOUS_MODE

  /*************************************************************/
  /**       MACRO TO CONFIGURE THE UART POLARITY              **/
  /**        AVAILABLE CHOICES   1 - RISING_EDGE_POLARITY     **/
  /**                            2 - FALLING_EDGE_POLARITY    **/
  /*************************************************************/
  #define UART_CLOCK_POLARITY    RISING_EDGE_POLARITY 
#endif


/*************************************************************/
/**       MACRO TO CONFIGURE THE NUMBER OF STOP BITS        **/
/**        AVAILABLE CHOICES   1 - ONE_STOP_BIT             **/
/**                            2 - TWO_STOP_BITS            **/
/*************************************************************/
#define STOP_BITS   ONE_STOP_BIT

/*************************************************************/
/**       MACRO TO CONFIGURE THE PARITY BIT                 **/
/**        AVAILABLE CHOICES   1 - DISABLE_PARITY_BIT       **/
/**                            2 - ODD_PARITY_BIT           **/
/**                            3 - EVEN_PARITY_BIT          **/
/*************************************************************/
#define PARITY_BIT_MODE  DISABLE_PARITY_BIT

/*************************************************************/
/**       MACRO TO CONFIGURE THE DATA SIZE                  **/
/**        AVAILABLE CHOICES   1 - CHAR_SIZE_8BIT           **/
/**                            2 - CHAR_SIZE_9BIT           **/
/**                            3 - CHAR_SIZE_5BIT           **/
/**                            4 - CHAR_SIZE_6BIT           **/
/**                            5 - CHAR_SIZE_7BIT           **/
/*************************************************************/
#define CHARACTER_SIZE   CHAR_SIZE_8BIT

/*************************************************************/
/**       MACRO TO CONFIGURE THE BAUD RATE                  **/
/**        AVAILABLE CHOICES   1 - BAUDRATE_9600            **/
/**                            2 - BAUDRATE_4800            **/
/**                            3 - BAUDRATE_2400            **/
/**                            4 - BAUDRATE_115200          **/
/*************************************************************/
#define BAUDRATE_VALUE   BAUDRATE_9600

/*******************************************************************/
/**       MACRO TO CONFIGURE THE MULTIPROCESSOR MODE              **/
/**        AVAILABLE CHOICES   1 - ENABLE_MULTIPROCESSOR_MODE     **/
/**                            2 - DISABLE_MULTIPROCESSOR_MODE    **/
/*******************************************************************/
#define MULTI_PROCESSOR_MODE   DISABLE_MULTIPROCESSOR_MODE


/*******************************************************************/
/**       MACRO TO CONFIGURE THE DOUBLE SPEED MODE                **/
/**        AVAILABLE CHOICES   1 - ENABLE_DOUBLE_SPEED_MODE       **/
/**                            2 - DISABLE_DOUBLE_SPEED_MODE      **/
/*******************************************************************/
#define DOUBLE_SPEED_MODE   DISABLE_DOUBLE_SPEED_MODE


/************************************************************************/
/**       MACRO TO CONFIGURE THE TRANSMITTING INTERRUPT                **/
/**        AVAILABLE CHOICES   1 - ENABLE_TRANSMITTING_INTERRUPT       **/
/**                            2 - DISABLE_TRANSMITTING_INTERRUPT      **/
/************************************************************************/
#define TRANSMITTING_INTERRUPT  DISABLE_TRANSMITTING_INTERRUPT


/*********************************************************************/
/**       MACRO TO CONFIGURE THE RECEIVING INTERRUPT                **/
/**        AVAILABLE CHOICES   1 - ENABLE_RECEIVING_INTERRUPT       **/
/**                            2 - DISABLE_RECEIVING_INTERRUPT      **/
/*********************************************************************/
#define RECEIVING_INTERRUPT  DISABLE_RECEIVING_INTERRUPT


/*******************************************************************/
/**       MACRO TO CONFIGURE THE UDR INTERRUPT                    **/
/**        AVAILABLE CHOICES   1 - ENABLE_UDR_INTERRUPT           **/
/**                            2 - DISABLE_UDR_INTERRUPT          **/
/*******************************************************************/
#define UDR_INTERRUPT  DISABLE_UDR_INTERRUPT




#endif /* UART_CONFIG_H_ */