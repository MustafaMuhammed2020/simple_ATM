/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : implementation of EEPROM APIs        */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYER INTERFACE FILES **/
#include "../../MCAL/i2c/I2C_interface.h"

/** INCLUDE DRIVER FILES **/
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"


/*************************************************************/
/** FUNCTION TO INITIALIZE EEPROM WITH SPECIFIC ADDRESS     **/
/** AGGUMENTS : VOID                                        **/
/** RETURNS   : VOID                                        **/
/*************************************************************/
void EEPROM_init(void)
{
	TWI_init(); /** INITIALIZE TWI MODULE **/
}

/*************************************************************/
/** FUNCTION TO WRITE BYTE TO SPECIFIC EEPROM ADDRESS       **/
/** AGGUMENTS : u16_a_address (ADDRSS) , u8_a_data (DATA)   **/
/** RETURNS   : uint8_t (SUCCESS STATE/ FAIL STATE)         **/
/*************************************************************/
uint8_t EEPROM_writebyte(uint16_t u16_a_address , uint8_t u8_a_data , uint8_t u8_a_page_address)
{
	TWI_start(); /** SEND START CONDITION **/
	
	if (TWI_getstatus() != TW_START) /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND DEVICE ADDRESS WITH WRITE OPERATION **/
	TWI_write(0xA0 | (u8_a_page_address << 1));
	
	if (TWI_getstatus() != TW_MT_SLA_W_ACK) /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND THE FIRST ADDRESS BYTE LOCATION ADDRESS **/
	TWI_write((uint8_t)(u16_a_address >> 8));
	
	if (TWI_getstatus() != TW_MT_DATA_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND THE SECOND ADDRESS BYTE LOCATION ADDRESS **/
	TWI_write((uint8_t)(u16_a_address));
	
	if (TWI_getstatus() != TW_MT_DATA_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** WRITE THE DATA BYTE **/
	TWI_write(u8_a_data);
	
	if (TWI_getstatus() != TW_MT_DATA_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	TWI_stop();
	
	return SUCCESS;
}


/*************************************************************/
/** FUNCTION TO READ BYTE FROM SPECIFIC EEPROM ADDRESS      **/
/** AGGUMENTS : u16_a_address (ADDRSS) , u8_a_data (DATA)   **/
/** RETURNS   : uint8_t (SUCCESS STATE/ FAIL STATE)         **/
/*************************************************************/
uint8_t EEPROM_readbyte(uint16_t u16_a_address , uint8_t *u8_a_data , uint8_t u8_a_page_address)
{
	TWI_start(); /** SEND START CONDITION **/
	
	if (TWI_getstatus() != TW_START)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND DEVICE ADDRESS WITH WRITE OPERATION **/
	TWI_write(0xA0 | (u8_a_page_address << 1));
	
	if (TWI_getstatus() != TW_MT_SLA_W_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND THE FIRST ADDRESS BYTE LOCATION ADDRESS **/
	TWI_write((uint8_t)(u16_a_address >> 8));
	
	if (TWI_getstatus() != TW_MT_DATA_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND THE SECOND ADDRESS BYTE LOCATION ADDRESS **/
	TWI_write((uint8_t)(u16_a_address));
	
	if (TWI_getstatus() != TW_MT_DATA_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND REPEATED START **/
	TWI_start();
	
	if (TWI_getstatus() != TW_REP_START)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	/** SEND DEVICE ADDRESS WITH READ OPERATION **/
	TWI_write(0xA0 | ((u8_a_page_address << 1) | 0x01));
	
	if (TWI_getstatus() != TW_MT_SLA_R_ACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	*u8_a_data = TWI_readwithnack(); /** READ THE DATA WITH ACK BIT **/
	
	if (TWI_getstatus() != TW_MR_DATA_NACK)  /** CHECK THE STATUS CODE **/
	return ERROR;
	
	TWI_stop(); /** SEND STOP CONDITION **/
	
	return SUCCESS; /** RETURN SUCCESS IF THE FRAME SENT CORRECTLY **/
}
