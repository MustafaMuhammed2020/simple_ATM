/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : interface file of I2C                */
/**************************************************/


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define F_CPU 8000000


/** MACROS FOR OPERATING SPEEDS OF I2C **/
#define I2C_400KHZ_SPEED                  0
#define I2C_200KHZ_SPEED                  1


/** MACROS TO CONFIGURE THE GENERAL CALL RECOGNITION **/
#define ENABLE_General_Call_Recognition   0
#define DISABLE_General_Call_Recognition  1
 
/** MACROS FOR THE I2C PRESCALLER VALUE **/
#define PRESCALLER_1                      0
#define PRESCALLER_4                      1
#define PRESCALLER_16                     3
#define PRESCALLER_64                     4


/** I2C Status Bits in the TWSR Register **/
#define TW_START         0x08  // start has been sent
#define TW_REP_START     0x10  // repeated start
#define TW_MT_SLA_W_ACK  0x18  // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40  // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28  // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50  // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58  // Master received data but doesn't send ACK to slave

/******************************************************/
/** FUNCTION TO INITIALIZE I2C MODULE                **/
/** ARGUMENTS : VOID                                 **/
/** RETURNS   : VOID                                 **/
/******************************************************/
void TWI_init(void);

/*********************************************************/
/** FUNCTION TO SET THE NODE ADDRESS                    **/
/** ARGUMENTS : u8_a_address                            **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_setaddress(uint8_t u8_a_address);

/*********************************************************/
/** FUNCTION TO SET START CONDITION                     **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_start(void);

/*********************************************************/
/** FUNCTION TO SET REPEATED START CONDITION            **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
 void TWI_repeatedstart(void);
  
/*********************************************************/
/** FUNCTION TO READ DATA WITH ACK                      **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (RECEIVED DATA)                 **/
/*********************************************************/
uint8_t TWI_readwithack(void);

/*********************************************************/
/** FUNCTION TO READ DATA WITHOUT ACK                   **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (RECEIVED DATA)                 **/
/*********************************************************/
uint8_t TWI_readwithnack(void);

/*********************************************************/
/** FUNCTION TO WRITE DATA OVER THE SDA LINE            **/
/** ARGUMENTS : u8_a_data                               **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_write(uint8_t u8_a_data);
 
/*********************************************************/
/** FUNCTION TO SET STOP CONDITION                      **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : VOID                                    **/
/*********************************************************/
void TWI_stop(void);
 
/*********************************************************/
/** FUNCTION TO GET THE STATUS BITS VALUE               **/
/** ARGUMENTS : VOID                                    **/
/** RETURNS   : uint8_t (CODE BITS VALUE)               **/
/*********************************************************/
uint8_t TWI_getstatus(void);
 
#endif /* I2C_INTERFACE_H_ */



