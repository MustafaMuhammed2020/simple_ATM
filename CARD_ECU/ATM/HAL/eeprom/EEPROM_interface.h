/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : interface file of eeprom             */
/**************************************************/
 
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/** MACROS TO SET THE RETURN STATUS OF FUNCTIONS **/
#define ERROR    0
#define SUCCESS  1

/*************************************************************/
/** FUNCTION TO INITIALIZE EEPROM WITH SPECIFIC ADDRESS     **/
/** AGGUMENTS : VOID                                        **/
/** RETURNS   : VOID                                        **/
/*************************************************************/ 
void EEPROM_init(void);

/*************************************************************/
/** FUNCTION TO WRITE BYTE TO SPECIFIC EEPROM ADDRESS       **/
/** AGGUMENTS : u16_a_address (ADDRSS) , u8_a_data (DATA)   **/
/** RETURNS   : uint8_t (SUCCESS STATE/ FAIL STATE)         **/
/*************************************************************/
uint8_t EEPROM_writebyte(uint16_t u16_a_address , uint8_t u8_a_data , uint8_t u8_a_page_address);


/*************************************************************/
/** FUNCTION TO READ BYTE FROM SPECIFIC EEPROM ADDRESS      **/
/** AGGUMENTS : u16_a_address (ADDRSS) , u8_a_data (DATA)   **/
/** RETURNS   : uint8_t (SUCCESS STATE/ FAIL STATE)         **/
/*************************************************************/
uint8_t EEPROM_readbyte(uint16_t u16_a_address , uint8_t *u8_a_data , uint8_t u8_a_page_address);


#endif /* EEPROM_INTERFACE_H_ */
