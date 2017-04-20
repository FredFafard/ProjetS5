/*
 * File:   main.c
 * Author: François Brunet
 *
 * Created on 11 avril 2017, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "config_bits.h"
#include "LCD.h"
#include "UART.h"
#include "Keyboard.h"

#define _XTAL_FREQ 8000000 //The speed of your internal(or)external oscillator
#define USE_AND_MASKS

//Global variable
volatile bool UART_NewData = false;
volatile char UART_Data;

//Function prototype
void Interrupt_init(void);
void interrupt Interrupt(void);

void main()
{
    LCD_init();
    UART_init();
    Interrupt_init();
    Keyboard_init();
    
    LCD_WriteString((char*)"P1 - Hiver 2017");
    
    UART_Write('C');
    
    LCD_WriteString((char*)"\nSyst");
    LCD_WriteChar(0xA4);
    LCD_WriteString((char*)"me Initialis");
    LCD_WriteChar(0xA5);
    
    while(1)
    {
        Keyboard_Read();
        
        if(Keyboard_NewData)
        { 
            Keyboard_NewData = false;
            
            UART_Write(Keyboard_Data);
            
            if (Keyboard_Data == 'C')
            {
                LCD_Clear();
                LCD_WriteString((char*)"\nSyst");
                LCD_WriteChar(0xA4);
                LCD_WriteString((char*)"me Initialis");
                LCD_WriteChar(0xA5);
            }
            else if (Keyboard_Data == '1')
            {
                LCD_WriteString((char*)"\nSauvegarde 1 (Lum)");
            }
            else if (Keyboard_Data == '2')
            {
                LCD_WriteString((char*)"\nSauvegarde 2 (Eau)");
            }
            else if (Keyboard_Data == '3')
            {
                LCD_WriteString((char*)"\nSauvegarde 3 (Fan)");
            }
            else if (Keyboard_Data == '4')            
            {
                LCD_WriteString((char*)"\nSauvegarde 4 (Mus)");
            }
            else if (Keyboard_Data == '5')
            {
                LCD_WriteString((char*)"\nSauvegarde 5");
            }
            else if (Keyboard_Data == '6')
            {
                LCD_WriteString((char*)"\nSauvegarde 6");
            }
        }
        
        if(UART_NewData)
        { 
            UART_NewData = false;
            
            if (UART_Data == 'N')
            {
                LCD_WriteString((char*)"\nErreur");
            }
            else if (UART_Data == '0')
            {
                LCD_WriteString((char*)"\nEn attente");
            }
            else if (UART_Data == '1')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 1 (Lum)");
            }
            else if (UART_Data == '2')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 2 (Eau)");
            }
            else if (UART_Data == '3')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 3 (Fan)");
            }
            else if (UART_Data == '4')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 4 (Mus)");
            }
            else if (UART_Data == '5')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 5");
            }
            else if (UART_Data == '6')
            {
                LCD_WriteString((char*)"\nCorr");
                LCD_WriteChar(0xA5);
                LCD_WriteString((char*)"lation 6");
            }
        }
    }
}

void Interrupt_init()
{
    PIR1bits.RC1IF = 0;     //Reset RX flag
    PIE1bits.RC1IE = 1;     //Enable RX interrupt
    
    INTCONbits.PEIE = 1;    //Enable pheripheral interrupt (serial port is a pheripheral)
    INTCONbits.GIE = 1;     //Enable interrupt
}

void interrupt Interrupt()
{
    //check if the interrupt is caused by RX pin
    if(PIR1bits.RC1IF == 1)
    {
        UART_Data = RCREG;     //Read data
        UART_NewData = true;     //New data available
        PIR1bits.RC1IF = 0; //Clear RX flag
    }
}
