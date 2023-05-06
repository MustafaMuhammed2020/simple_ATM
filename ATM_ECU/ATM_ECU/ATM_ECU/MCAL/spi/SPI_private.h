/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 1 May , 2023                         */
/* Version : V02                                  */
/* Hint    : private file of SPI                  */
/**************************************************/


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPI_PORT      DIO_PORTB  /** SPI PORT **/

/** SPI PINS  **/
#define SPI_SS_PIN      DIO_PIN4
#define SPI_MOSI_PIN    DIO_PIN5
#define SPI_MISO_PIN    DIO_PIN6
#define SPI_CLK_PIN     DIO_PIN7


/** ENUM TO RETURN THE SPI FUNCTIONS' STATUS **/
typedef enum {SPI_VALID , SPI_NOT_VALID} en_a_spierrstatus ;


/********************************************************************************/
/**		   SPI REGISTERS' DEFINITION USING STRUCT METHOD                       **/
/**            1 - DEFINE STRUCT TYPE CONTAIN SPI REGISTERS NAMES              **/
/**            2 - CREATE VARIABLE FROM THIS TYPE POINTS TO THE FIRST ADDRESS  **/
/**            3 - ACCESS THE REGISTERS USING ARROW (->)                       **/
/********************************************************************************/
typedef struct  
{
	/** SPI REGISTERS WITH THEIR ORDER IN DATA SHEET  **/
	volatile uint8_t SPCR ;
	volatile uint8_t SPSR ;
	volatile uint8_t SPDR ;
	 
}SPI_t; /** SPI TYPE DEFINITION **/


#define SPI   ( (SPI_t * ) (0x2D) )  /** POINTER TO TYPE OF SPI_t POINTS TO THE FIRST SPI ADDRESS (SPCR) **/ 

#endif /* SPI_PRIVATE_H_ */