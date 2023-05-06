/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : private file of UART                 */
/**************************************************/

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

// /** PORT OF UART PINS **/
// #define UART_PORT  DIO_PORTD
// 
// /** TX , RX PINS  **/
// #define TX_PIN   DIO_PIN1  
// #define RX_PIN   DIO_PIN0
// 

/*** UART MODULE REGISTERS DEFINITION  ***/

#define UDR     (* (volatile uint8_t * ) (0x2C))
#define UCSRA   (* (volatile uint8_t * ) (0x2B))
#define UCSRB   (* (volatile uint8_t * ) (0x2A))
#define UCSRC   (* (volatile uint8_t * ) (0x40))
#define UBRRH   (* (volatile uint8_t * ) (0x40))
#define UBRRL   (* (volatile uint8_t * ) (0x29))


#endif /* UART_PRIVATE_H_ */