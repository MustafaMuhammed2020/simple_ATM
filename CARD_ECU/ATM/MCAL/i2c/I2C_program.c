/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : implementation of I2C APIs           */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** ADD LOWER LAYER DRIVERS **/
#include "../dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"
 
/******************************************************/
/** FUNCTION TO INITIALIZE I2C MODULE                **/
/** ARGUMENTS : VOID                                 **/
/** RETURNS   : VOID                                 **/
/******************************************************/
void TWI_init(void)
{ 
	/** SET THE SPEED VALUE IN TWBR **/
	/** THESE CALCULATIONS USING 8M F_CPU **/
	#if I2C_SPEED_MODE   == I2C_400KHZ_SPEED
		TWBR = 0x02;
	#elif I2C_SPEED_MODE ==  I2C_200KHZ_SPEED
		TWBR = 0x0C;
	#endif
	
	/** SET THE PRESCALLER VALUE **/
	#if I2C_PRESCALLER_VALUE ==  PRESCALLER_1
		TWSR = 0x00;
		
	#elif I2C_PRESCALLER_VALUE ==  PRESCALLER_4
		TWSR = 0x01;
		
	#elif I2C_PRESCALLER_VALUE == PRESCALLER_16
		TWSR = 0x02;
		
	#elif I2C_PRESCALLER_VALUE == PRESCALLER_64
		TWSR = 0x03;
	#endif
	
    TWCR = (1<<TWEN); /** ENABLE TWI **/
}

/*********************************************************/
/** FUNCTION TO SET THE NODE ADDRESS                    **/
/** ARGUMENTS : u8_a_address                            **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_setaddress(uint8_t u8_a_address)
{
	/** SET THE NODE ADDRESS IN TWAR (BIT1 : bit7) + GENERAL CALL (bit 8)**/
	#if General_Call_Recognition_MODE ==  ENABLE_General_Call_Recognition
		TWAR = (u8_a_address << 1) | (0x01) ;
		
	#elif General_Call_Recognition_MODE ==  DISABLE_General_Call_Recognition
		TWAR = (u8_a_address << 1);
	#endif
	
}

/*********************************************************/
/** FUNCTION TO SET START CONDITION                     **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_start(void)
{
	/****************************************************************/
	/** CLEAR THE TWINT FLAG                                       **/
	/** SEND START CONDITION                                       **/
	/** WAIT UNTILL THE FLAG STATUS CHANGED ( THE EVENT DONE)      **/
	/****************************************************************/
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /** Wait for TWINT flag set in TWCR Register (start bit is send successfully) **/
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*********************************************************/
/** FUNCTION TO SET REPEATED START CONDITION            **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_repeatedstart(void)
{
	/** THE SAME AS START CONDITION BUT THE STATE CODE IS DIFFERENT **/
	
	/****************************************************************/
	/** CLEAR THE TWINT FLAG                                       **/
	/** SEND START CONDITION                                       **/
	/** WAIT UNTILL THE FLAG STATUS CHANGED ( THE EVENT DONE)      **/
	/****************************************************************/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	/** Wait for TWINT flag set in TWCR Register (start bit is send successfully) **/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*********************************************************/
/** FUNCTION TO READ DATA WITH ACK                      **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (RECEIVED DATA)                 **/
/*********************************************************/
uint8_t TWI_readwithack(void)
{
	/************************************************/
	/* CLEAR THE TWINT FLAG                        **/
	/* ENABLE ACK BIT AFTER READING THE DATA       **/
	/* ENABLE TWI MODULE                           **/
	/************************************************/ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
    /** Wait for TWINT flag set in TWCR Register (start bit is send successfully) **/
    while(BIT_IS_CLEAR(TWCR,TWINT));
	
    /** READ DATA **/
    return TWDR;
}

/*********************************************************/
/** FUNCTION TO READ DATA WITHOUT ACK                   **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (RECEIVED DATA)                 **/
/*********************************************************/
uint8_t TWI_readwithnack(void)
{
	/************************************************/
	/* CLEAR THE TWINT FLAG                        **/
	/* DISABLE ACK BIT AFTER READING THE DATA      **/
	/* ENABLE TWI MODULE                           **/
	/************************************************/
	TWCR = (1 << TWINT) | (1 << TWEN) ;
	
	/** Wait for TWINT flag set in TWCR Register (start bit is send successfully) **/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	
	/** READ DATA **/
	return TWDR;
}

/*********************************************************/
/** FUNCTION TO WRITE DATA OVER THE SDA LINE            **/
/** ARGUMENTS : u8_a_data                               **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_write(uint8_t u8_a_data)
{
	/** PREPARE DATA FOR SENDING **/
    TWDR = u8_a_data;
    
	/***************************************/ 
	/** CLEAR THE TWINT FLAG              **/
	/** ENABLE TWI MODULE                 **/
	/***************************************/ 
    TWCR = (1 << TWINT) | (1 << TWEN);
	
    /** Wait for TWINT flag set in TWCR Register (start bit is send successfully) **/
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*********************************************************/
/** FUNCTION TO SET STOP CONDITION                      **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_stop(void)
{
	/****************************************/ 
	/** CLEAR THE TWINT FLAG               **/
	/** SEND STIOP BIT EVENT               **/
	/** ENABLE TWI MODULE                  **/
	/****************************************/
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*********************************************************/
/** FUNCTION TO GET THE STATUS BITS VALUE               **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (CODE BITS VALUE)               **/
/*********************************************************/
uint8_t TWI_getstatus(void)
{
	uint8_t u8_a_status ; /** VARIABLE TO HOLD THE STATUS CODE VALUE **/
	
	/** MASKING THE FIRST THREE BITS TO GET THE LAST 5 BITS ONLY **/
	u8_a_status = TWSR & 0xF8;
	
	return u8_a_status;
}