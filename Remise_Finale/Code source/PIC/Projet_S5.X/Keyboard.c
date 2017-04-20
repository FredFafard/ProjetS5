/* 
 * File:   Keyboard.c
 * Author: François Brunet
 *
 * Created on April 16, 2017, 3:21 PM
 */

#include "Keyboard.h"
#include <xc.h>

bool Keyboard_Ready = false;
int debounce = 0;

void Keyboard_init()
{
    TRISEbits.TRISE0 = 0; //Column 1 output
    TRISEbits.TRISE1 = 0; //Column 2 output
    TRISEbits.TRISE2 = 0; //Column 3 output
    TRISEbits.TRISE3 = 0; //Column 4 output
    TRISEbits.TRISE4 = 1; //Line 1 input
    TRISEbits.TRISE5 = 1; //Line 2 input
    TRISEbits.TRISE6 = 1; //Line 3 input
    TRISEbits.TRISE7 = 1; //Line 4 input
}

void Keyboard_Read()
{
    int i;
    
    PORTE = 0x00;
    
    //Check if no key are pressed
    if(PORTE == 0xF0)
    {
        if(debounce > 10000)
        {
            Keyboard_Ready = true;
            debounce = 0;
        }
        else
        {
            debounce++;
        }
            
    }
    else
    {
        debounce = 0;
    }
    
    //New key pressed
    if(PORTE != 0xF0 && Keyboard_Ready)
    {
        Keyboard_Ready = false;
        Keyboard_NewData = true;
        
        PORTE = 0x0E;                //Column 1
        for(i=0;i<1000;i++); //delay
        if (PORTEbits.RE4 == 0)      //Line 1
        {
            Keyboard_Data = '1';
        }
        else if (PORTEbits.RE5 == 0) //Line 2
        {
            Keyboard_Data = '4';
        }
        else if (PORTEbits.RE6 == 0) //Line 3
        {
            Keyboard_Data = '7';
        }
        else if (PORTEbits.RE7 == 0) //Line 4
        {
            Keyboard_Data = 'F';
        }
        
        PORTE = 0x0D;                //Column 2
        for(i=0;i<1000;i++); //delay
        if (PORTEbits.RE4 == 0)      //Line 1
        {
            Keyboard_Data = '2';
        }
        else if (PORTEbits.RE5 == 0) //Line 2
        {
            Keyboard_Data = '5';
        }
        else if (PORTEbits.RE6 == 0) //Line 3
        {
            Keyboard_Data = '8';
        }
        else if (PORTEbits.RE7 == 0) //Line 4
        {
            Keyboard_Data = '0';
        }
        
        PORTE = 0x0B;                //Column 3
        for(i=0;i<1000;i++); //delay
        if (PORTEbits.RE4 == 0)      //Line 1
        {
            Keyboard_Data = '3';
        }
        else if (PORTEbits.RE5 == 0) //Line 2
        {
            Keyboard_Data = '6';
        }
        else if (PORTEbits.RE6 == 0) //Line 3
        {
            Keyboard_Data = '9';
        }
        else if (PORTEbits.RE7 == 0) //Line 4
        {
            Keyboard_Data = 'E';
        }
        
        PORTE = 0x07;                //Column 4
        for(i=0;i<1000;i++); //delay
        if (PORTEbits.RE4 == 0)      //Line 1
        {
            Keyboard_Data = 'A';
        }
        else if (PORTEbits.RE5 == 0) //Line 2
        {
            Keyboard_Data = 'B';
        }
        else if (PORTEbits.RE6 == 0) //Line 3
        {
            Keyboard_Data = 'C';
        }
        else if (PORTEbits.RE7 == 0) //Line 4
        {
            Keyboard_Data = 'D';
        }
    }
}
