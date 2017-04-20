/* 
 * File:   UART.c
 * Author: François Brunet
 *
 * Created on April 16, 2017, 3:04 PM
 */

#include "UART.h"
#include <xc.h>

void UART_init()
{
    TRISDbits.TRISD6 = 0;   //TX TO OUTPUT
    TRISDbits.TRISD7 = 1;   //RX TO INPUT

    OSCCON2bits.IOLOCK = 0;
    RPOR26_27 = 0x11;       //RP26 --> TX
    RPINR0_1 = 0x66;        //RP27 --> RX
    OSCCON2bits.IOLOCK = 1;
    
    //Initialise baud rate
    SPBRG1 = 34;            //Fosc/Baud_Rate/16-1
    TXSTAbits.BRGH = 1;     //Async baud rate
    BAUDCONbits.BRG16 = 0;  //8 bits Baud Rate
    TXSTAbits.SYNC = 0;     //Async
    RCSTAbits.SPEN = 1;     //Serial port enable
    
    TXSTAbits.TX9 = 0;      //8 bit
    TXSTAbits.TXEN = 1;     //Transmission Enable
    
    RCSTAbits.RX9 = 0;      //8 bit
    RCSTAbits.CREN = 1;     //Reception Enable
}

void UART_Write(char data)
{
    while(PIR1bits.TX1IF != 1); //TX busy
    TXREG = data;               //Write data
}
