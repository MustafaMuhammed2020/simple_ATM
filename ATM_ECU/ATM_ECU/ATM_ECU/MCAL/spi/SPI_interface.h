/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 1 May , 2023                         */
/* Version : V02                                  */
/* Hint    : interface file of SPI                */
/**************************************************/

#include "SPI_private.h"

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define F_CPU 8000000

/** MACROS TO CONFIGURE THE SPI INTERRUPT STATUS **/
#define ENABLE_SPI_INTERRUPT      0
#define DISABLE_SPI_INTERRUPT     1

/** MACROS TO CONFIGURE THE DATA TRANSMISSION IN SPI SHIFT REGISTERS **/ 
#define SEND_LSB_FIRST            0
#define SEND_MSB_FIRST            1

/** MACROS TO CONFIGURE THE CLOCK POLARITY **/
#define IDLE_HIGH_POLARITY        0
#define IDLE_LOW_POLARITY         1

/** MACROS TO CONFIGURE THE CLOCK PHASE **/
#define READ_WRITE_PHASE          0
#define WRITE_READ_PHASE          1

/** MACROS TO CONFIGURE THE DOUBLE SPEED MODE **/
#define ENABLE_DOUBLE_SPEED_MODE  0
#define DISABLE_DOUBLE_SPEED_MODE 1

/** MACROS TO CONFIGURE THE PRESCALLER VALUE **/
#define PRESCALLER_2              0
#define PRESCALLER_4              1
#define PRESCALLER_8              2
#define PRESCALLER_16             3
#define PRESCALLER_32             4
#define PRESCALLER_64             5
#define PRESCALLER_128            6


/*****************************************************************/
/** FUNCTION TO INITIALIZE SPI MODULE AS MASTER                 **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_initmaster(void);


/*****************************************************************/
/** FUNCTION TO INITIALIZE SPI MODULE AS SLAVE                  **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_initslave(void);

/*****************************************************************/
/** FUNCTION FOR MASTER TO INITIALIZE TRANSMISSION              **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_masterinittransmit(void);

/*****************************************************************/
/** FUNCTION FOR MASTER TO END TRANSMISSION                     **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_masterendtransmit(void);

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND BYTE (character)                **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_sendbyte(uint8_t u8_a_data);

/*****************************************************************/
/** FUNCTION FOR MASTER TO INITIALIZE TRANSMISSION              **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_receivebyte(uint8_t * u8_a_recdata);

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND STRING                          **/
/** ARGUMENTS  : u8_a_str (string)                              **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_sendstring(const uint8_t * u8_a_str);

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND STRING                          **/
/** ARGUMENTS  : u8_a_str (string)                              **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_receivestring(uint8_t * u8_a_str);


#endif /* SPI_INTERFACE_H_ */