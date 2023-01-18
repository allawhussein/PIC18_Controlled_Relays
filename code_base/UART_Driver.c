/*
 * File:   UART_Driver.c
 * Author: mahmo
 *
 * Created on January 1, 2023, 12:15 PM
 */


#include "UART_Driver.h"



void USART_init(long baud_rate)
{
    float temp;
    
    SYNC = 0;
    SPEN = 1;
    
    TRISC6=1;		// Make Tx pin as output 
    TRISC7=1;  		// Make Rx pin as input

    /* Baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    temp = (((float) (F_CPU) / (64*(float) baud_rate)) - 1); 
    if (temp>255) BRGH = 1;    
    SPBRG = (unsigned char)temp;
    
    TXSTA = 0x20;  	/* Enable Transmit(TX) */ 
    RCSTA = 0x90;  	/* Enable Receive(RX) & Serial */
    
    CREN = 1;
    TXEN = 1;
}


void USART_Transmit (uint8_t out)
{
   while (!(TXIF));	/* Wait for transmit interrupt flag*/
   TXREG = out;  	/* Write char data to transmit register */    
}


uint8_t USART_Receive()
{
    
    while(!(RCIF));      /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);       /*received in RCREG register and return to main program */
}

void Active_Receiver_Interrupt()
{
    GIE=1;	/* Enable Global Interrupt */
    PEIE=1;	/* Enable Peripheral Interrupt */
    RCIE=1;	/* Enable Receive Interrupt */
}

/*
 
      (In main)

void interrupt ISR (void)
{
  if (RCIF == 1)
  {
    Destination = RCREG;  // Read The Received Data Buffer
    RCIF = 0;             // Clear The Flag
  }
}

*/

