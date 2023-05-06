/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 1 May , 2023                         */
/* Version : V02                                  */
/* Hint    : configuration file of SPI            */
/**************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/********************************************************************/
/**       MACRO TO CONFIGURE SPI INTERRUPT                         **/
/**        AVAILABLE CHOICES   1 - DISABLE_SPI_INTERRUPT           **/
/**                            2 - ENABLE_SPI_INTERRUPT            **/
/********************************************************************/
#define SPI_INTERRUPT_MODE    DISABLE_SPI_INTERRUPT

/********************************************************************/
/**       MACRO TO CONFIGURE DATA TRANSMISSION ORDER               **/
/**        AVAILABLE CHOICES   1 - SEND_LSB_FIRST			       **/
/**                            2 - SEND_MSB_FIRST                  **/
/********************************************************************/
#define SPI_DATA_ORDER        SEND_MSB_FIRST

/*********************************************************************/
/**       MACRO TO CONFIGURE CLOCK POLARITY                         **/
/**        AVAILABLE CHOICES   1 - IDLE_LOW_POLARITY	 		    **/
/**                            2 - IDLE_HIGH_POLARITY               **/
/*********************************************************************/
#define SPI_CLOCK_POLARITY    IDLE_LOW_POLARITY

/*********************************************************************/
/**       MACRO TO CONFIGURE CLOCK PHASE                            **/
/**        AVAILABLE CHOICES   1 - READ_WRITE_PHASE	     		    **/
/**                            2 - WRITE_READ_PHASE                 **/
/*********************************************************************/
#define SPI_CLOCK_PHASE       READ_WRITE_PHASE

/*********************************************************************/
/**       MACRO TO CONFIGURE DOUBLE SPEED MODE                      **/
/**        AVAILABLE CHOICES   1 - ENABLE_DOUBLE_SPEED_MODE	     	**/
/**                            2 - DISABLE_DOUBLE_SPEED_MODE        **/
/*********************************************************************/
#define DOUBLE_SPEED_MODE     DISABLE_DOUBLE_SPEED_MODE

/*************************************************************/
/**       MACRO TO CONFIGURE THE PRESCALLER                 **/
/**        AVAILABLE CHOICES   1 - PRESCALLER_2             **/
/**                            2 - PRESCALLER_4             **/
/**                            3 - PRESCALLER_8             **/
/**                            4 - PRESCALLER_16            **/
/**                            5 - PRESCALLER_32            **/
/**                            5 - PRESCALLER_64            **/
/**                            6 - PRESCALLER_128           **/
/*************************************************************/
#define SPI_PRESCALER_VALUE   PRESCALLER_128


#endif /* SPI_CONFIG_H_ */