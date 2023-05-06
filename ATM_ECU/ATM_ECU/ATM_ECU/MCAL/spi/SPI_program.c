/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 1 May , 2023                         */
/* Version : V02                                  */
/* Hint    : implementation of SPI APIs           */
/**************************************************/
 
/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE INTERFACE FILES OF LOWER DRIVERS **/
#include "../dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"


/*****************************************************************/
/** FUNCTION TO INITIALIZE SPI MODULE AS MASTER                 **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_initmaster(void)
{
	/**************** MASTER SIDE ***********************/
	/**    MOSI (OUTPUT PIN)                           **/
	/**    MISO (INPUT PIN)                            **/
	/**    CLK  (OUTPUT PIN)                           **/
	/**    SS   (OUTPUT PIN)                           **/
	/****************************************************/                                                
    
	/** SPI MASTER PINS DIRECTOINS  **/
	DIO_setpindir(SPI_PORT , SPI_SS_PIN , DIO_PIN_OUTPUT);
    DIO_setpindir(SPI_PORT , SPI_MOSI_PIN , DIO_PIN_OUTPUT);
	DIO_setpindir(SPI_PORT , SPI_MISO_PIN , DIO_PIN_INPUT);
	DIO_setpindir(SPI_PORT , SPI_CLK_PIN  , DIO_PIN_OUTPUT);
	
	/* CURRENT CONFIGURATION */
	//SPI->SPCR = 0x53;
	
	/** SET PRESCALLER VALUE **/
	#if SPI_PRESCALER_VALUE == PRESCALLER_4	
		clear_bit(SPI->SPCR , 0);
		clear_bit(SPI->SPCR , 1);
		clear_bit(SPI->SPSR , 0);
	
	#elif SPI_PRESCALER_VALUE == PRESCALLER_16
		set_bit(SPI->SPCR , 0);
		clear_bit(SPI->SPCR , 1);
		clear_bit(SPI->SPSR , 0);
	
	#elif SPI_PRESCALER_VALUE == PRESCALLER_32
		clear_bit(SPI->SPCR , 0);
		set_bit(SPI->SPCR , 1);
		set_bit(SPI->SPSR , 0);
	
	#elif SPI_PRESCALER_VALUE == PRESCALLER_128
		set_bit(SPI->SPCR , 0);
		set_bit(SPI->SPCR , 1);
		clear_bit(SPI->SPSR , 0);
	
	#elif SPI_PRESCALER_VALUE == PRESCALLER_2
		clear_bit(SPI->SPCR , 0);
		clear_bit(SPI->SPCR , 1);
		set_bit(SPI->SPSR , 0);
	
	#elif SPI_PRESCALER_VALUE == PRESCALLER_8
		set_bit(SPI->SPCR , 0);
		clear_bit(SPI->SPCR , 1);
		set_bit(SPI->SPSR  , 0);
	#endif
	
	/** SET THE DOUBLE SPEED MODE **/
	#if DOUBLE_SPEED_MODE == ENABLE_DOUBLE_SPEED_MODE
	set_bit(SPI->SPSR , 0);
	
	#elif DOUBLE_SPEED_MODE == DISABLE_DOUBLE_SPEED_MODE
	clear_bit(SPI->SPSR , 0);
	#endif
	
	/** SET THE INTERRUPT STATUS **/
	#if SPI_INTERRUPT_MODE  == ENABLE_SPI_INTERRUPT
		set_bit(SPI->SPCR , 7);
	
	#elif SPI_INTERRUPT_MODE == DISABLE_SPI_INTERRUPT
		clear_bit(SPI->SPCR , 7);
	#endif
	
	/** DATA ORDER **/
	#if SPI_DATA_ORDER == SEND_LSB_FIRST
		set_bit(SPI->SPCR , 5);
	
	#elif SPI_DATA_ORDER == SEND_MSB_FIRST
		clear_bit(SPI->SPCR , 5);
	#endif
	
	/** CLOCK POLARITY **/
	#if SPI_CLOCK_POLARITY == IDLE_HIGH_POLARITY
		set_bit(SPI->SPCR , 3);
	
	#elif SPI_CLOCK_POLARITY == IDLE_LOW_POLARITY
		clear_bit(SPI->SPCR , 3);
	#endif
	
	/** CLOCK PHASE **/
	#if SPI_CLOCK_PHASE == READ_WRITE_PHASE
		clear_bit(SPI->SPCR , 2);
	
	#elif SPI_CLOCK_PHASE == WRITE_READ_PHASE
		set_bit(SPI->SPCR , 2);
	#endif
	
	/* MASTER MODE */
	set_bit(SPI->SPCR , 4);
	
	
	/* ENABLE SPI MODULE */
	set_bit(SPI->SPCR , 6);
	
}


/*****************************************************************/
/** FUNCTION TO INITIALIZE SPI MODULE AS SLAVE                  **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_initslave(void)
{
	/**************** SLAVE SIDE **********************/
	/**          MOSI ->  INPUT_PIN                  **/
	/**          SS   ->  INPUT_PIN                  **/
	/**          MISO ->  OUTPUT_PIN                 **/
	/**          SCK  ->  INPUT_PIN                  **/
	/**************************************************/ 
	
	/** SPI SLAVE PINS DIRECTOINS  **/
	DIO_setpindir(SPI_PORT , SPI_SS_PIN , DIO_PIN_INPUT);
	DIO_setpindir(SPI_PORT , SPI_MOSI_PIN , DIO_PIN_INPUT);
	DIO_setpindir(SPI_PORT , SPI_MISO_PIN , DIO_PIN_OUTPUT);
	DIO_setpindir(SPI_PORT , SPI_CLK_PIN  , DIO_PIN_INPUT);
	
	/* ENABLE SPI MODULE */
	set_bit(SPI->SPCR , 6);
	
	/* CHOOSE SLAVE MODE */
	clear_bit(SPI->SPCR , 4);
	
	/**************************************************/
	/** CLOCK POLARITY AND CLOCK PHASE ARE           **/
	/** THE SAME IN MASTER SIDE AND SLAVE SIDE       **
	/**************************************************/
	
	/** CLOCK POLARITY **/
	#if SPI_CLOCK_POLARITY == IDLE_HIGH_POLARITY
		set_bit(SPI->SPCR , 3);
	
	#elif SPI_CLOCK_POLARITY == IDLE_LOW_POLARITY
		clear_bit(SPI->SPCR , 3);
	#endif
	
	/** LOCK PHASE **/
	#if SPI_CLOCK_PHASE == READ_WRITE_PHASE
		clear_bit(SPI->SPCR , 2);
	
	#elif SPI_CLOCK_PHASE == WRITE_READ_PHASE
		set_bit(SPI->SPCR , 2);
	#endif
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO INITIALIZE TRANSMISSION              **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_masterinittransmit(void)
{
	/* DRIVE THE SS PIN LOW */
	DIO_setpinvalue(SPI_PORT , SPI_SS_PIN , DIO_PIN_LOW);
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO END TRANSMISSION                     **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_masterendtransmit(void)
{
		/* MAKE THE SS PIN HIGH */
		DIO_setpinvalue(SPI_PORT , SPI_SS_PIN , DIO_PIN_HIGH);
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND BYTE (character)                **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_sendbyte(uint8_t u8_a_data)
{
// 	uint8_t u8_L_bufferflush = 0 ;  /** LOCAL VARIABLE (ANY DATA) TO FLUSH DATA (SPDR) **/
// 	
	SPI->SPDR = u8_a_data ; /** STORE DATA IN SPI DATA REGISTER **/
	
	while( (SPI->SPSR &  (1 << 7)) == 0); /** WAIT UNTILL THE TRANSMISSION FLAG RAISED **/
	
	/************************************************************************************/
	/** ACCORDING TO SPI THE FLAG WILL CLEARED ONLY IF TWO READING OPERATIONS DONE ;   **/
	/** FIRST READ IS TO SPCR AND IT'S DONE WHEN WE READ THE FLAG ITSELF , SO WE NEAD  **/
	/** TO READ THE SPDR (THE SECOND READ OPERATION) BY SOFTWARE SO THAT THE FLAG WILL **/
	/** BE CLEARED AND READY TO TRANSMIT AND RECEIVE AGAIN                             **/
	/************************************************************************************/
	
	//u8_L_bufferflush = SPI->SPDR ; /** SECOND READ OF DATA REGISTER **/
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO INITIALIZE TRANSMISSION              **/
/** ARGUMENTS  : VOID                                           **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_receivebyte(uint8_t * u8_a_recdata)
{
// 	uint8_t u8_L_bufferflush = 0 ;  /** LOCAL VARIABLE (ANY DATA) TO FLUSH DATA (SPDR) **/
//     
// 	SPI->SPDR = 0xFF ; /** SECOND READ OF DATA REGISTER **/
//  	
	while( (SPI->SPSR &  (1 << 7)) == 0); /** WAIT UNTILL THE RECEIPTION FLAG RAISED **/
	
	//u8_L_bufferflush = SPI->SPDR ;
	
	*u8_a_recdata = SPI->SPDR ; /** SAVE THE DATA FROM SPDR **/
	
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND STRING                          **/
/** ARGUMENTS  : u8_a_str (string)                              **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_sendstring(const uint8_t * u8_a_str)
{
	uint8_t u8_L_counter = 0 ; /** COUNTER FOR STRING LETTERS **/
	
	while (u8_a_str[u8_L_counter] != '\0')
	{
		SPI_sendbyte(u8_a_str[u8_L_counter]); /** SEND CHARACTER **/
		
		u8_L_counter++; /* MOVE TO THE SECOND LETTER */
	}
}

/*****************************************************************/
/** FUNCTION FOR MASTER TO SEND STRING                          **/
/** ARGUMENTS  : u8_a_str (string)                              **/
/** RETURNS    : en_a_spierrstatus                              **/
/*****************************************************************/
en_a_spierrstatus SPI_receivestring(uint8_t * u8_a_str)
{
	uint8_t u8_L_counter = 0 ; /** COUNTER FOR STRING LETTERS **/
	
	//str[counter] = SPI_RECEIVE_BYTE();
	
	while (u8_a_str[u8_L_counter] != '\0')
	{
		SPI_receivebyte(&u8_a_str[u8_L_counter]); /** RECEIVE CHARACTER **/
		
		u8_L_counter++ ; /* MOVE TO THE SECOND LETTER */
	}
	
	
	u8_a_str[u8_L_counter] = '\0' ; /* TERMINATOR OF STRING */
}

