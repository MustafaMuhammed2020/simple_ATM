/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 May, 2023                          */
/* Version : V01                                  */
/* Hint    : private file of I2C                  */
/**************************************************/
 
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/** DEFINITION OF I2C REGISTERS **/
#define TWBR  (* (volatile uint8_t * ) (0x20))
#define TWSR  (* (volatile uint8_t * ) (0x21))
#define TWAR  (* (volatile uint8_t * ) (0x22))
#define TWDR  (* (volatile uint8_t * ) (0x23))
#define TWCR  (* (volatile uint8_t * ) (0x56))


/** TWI CONTROL REGISTER BITS DEFINITION **/
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7


#endif /* I2C_PRIVATE_H_ */