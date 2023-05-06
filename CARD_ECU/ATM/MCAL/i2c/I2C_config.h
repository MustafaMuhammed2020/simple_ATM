/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : configuration file of I2C            */
/**************************************************/
 
#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

/*****************************************************************/
/** MACRO TO CONFIGURE THE PRESCALLER VALUE                     **/
/**          CHOICES : 1 - PRESCALLER_1                         **/
/**                    2 - PRESCALLER_4                         **/
/**                    3 - PRESCALLER_16                        **/
/**                    4 - PRESCALLER_64                        **/
/*****************************************************************/
#define I2C_PRESCALLER_VALUE PRESCALLER_1

/*****************************************************************/
/** MACRO TO CONFIGURE THE TWI SPEED MODE                       **/
/**          CHOICES : 1 - I2C_400KHZ_SPEED                     **/
/**                    2 - I2C_200KHZ_SPEED                     **/
/*****************************************************************/
#define  I2C_SPEED_MODE   I2C_400KHZ_SPEED

/*****************************************************************/
/** MACRO TO CONFIGURE THE GENERAL CALL MODE                    **/
/**          CHOICES : 1 - DISABLE_General_Call_Recognition     **/
/**                    2 - ENABLE_General_Call_Recognition      **/
/*****************************************************************/
#define General_Call_Recognition_MODE   DISABLE_General_Call_Recognition





#endif /* I2C_CONFIG_H_ */