/* 
 * File:   LCD.c
 * Author: François Brunet
 *
 * Created on 14 avril 2017, 17:07
 */

#include "LCD.h"

//Private function prototype
void SPI2_init(void);
void WriteLCD(char RS, char data);

//Private variable
char DataPosition = 0;
char DataLine1[21];
char DataLine2[21];
char DataLine3[21];
char DataLine4[21];

void SPI2_init()
{
    TRISDbits.TRISD1 = 1;   //SCL TO INPUT
    TRISDbits.TRISD2 = 0;   //SCL TO OUTPUT
    TRISDbits.TRISD3 = 0;   //SS TO OUTPUT
    TRISDbits.TRISD4 = 0;   //SDO TO OUTPUT
    
    OSCCON2bits.IOLOCK = 0;
    RPINR12_13 |= 0x05;     //RP21 --> SDI2
    RPOR22_23 |= 0x05;      //RP22 --> SCK2
    RPOR24_25 |= 0x04;      //RP24 --> SDO2
    OSCCON2bits.IOLOCK = 1;
    
    //Enable and configure the PPS SPI2
    SSP2CON1bits.SSPEN2 = 1; //SPI SERIAL START
    SSP2STATbits.CKE2   = 0; //ClockMode 
    SSP2CON1bits.CKP2   = 1; //ClockMode 
    
    SSP2CON1 = 0b00110010;
}

void WriteLCD(char RS, char data)
{
    //StartByte = 1 1 1 1 1 0 RS 0
    char StartByte;
    if (RS == 0)
        StartByte = 0xF8;
    else
        StartByte = 0xFA;
    
    //Reverse data
    data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
    data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
    data = (data & 0xAA) >> 1 | (data & 0x55) << 1;
    
    //LowerData = D0 D1 D2 D3 0 0 0 0
    char LowerData = data & 0xF0;
    
    //UpperData = D4 D5 D6 D7 0 0 0 0
    char UpperData = (data<<4) & 0xF0;
    
    PORTDbits.RD3 = 0; //LCD Enable
    WriteSPI2(StartByte);
    WriteSPI2(LowerData);
    WriteSPI2(UpperData);
    PORTDbits.RD3 = 1;
}

void LCD_init()
{
    SPI2_init();
             
    WriteLCD(0,0x3C);   //Function set RE(1)  
    WriteLCD(0,0x09);   //Ext Func set 
    WriteLCD(0,0x38);   //Function set RE(0)
    WriteLCD(0,0x0C);   //Display ON/OFF
    WriteLCD(0,0x01);   //Clear
}

void LCD_Clear(void)
{
    WriteLCD(0,0x01);
    
    DataPosition = 0;
    
    int i;
    for(i=0;i<20;i++)
    {
        DataLine1[i] = '\0';
        DataLine2[i] = '\0';
        DataLine3[i] = '\0';
        DataLine4[i] = '\0';
    }
}

void LCD_WriteChar(char data)
{
    int i = 0;
    
    //Save data and line feed
    if(DataPosition < 20)
    {
        if(data == '\n')
        {
            //Line feed
            LCD_SelectLine(2);
            DataPosition = 20;
        }
        else
        {
            //Save line 1 new data
            DataLine1[DataPosition] = data;
        }
    }
    else if(DataPosition < 40)
    {
        if(data == '\n')
        {
            //Line feed
            LCD_SelectLine(3);
            DataPosition = 40;
        }
        else
        {
            //Save line 2 new data
            DataLine2[DataPosition-20] = data;
        }
    }
    else if(DataPosition < 60)
    {
        if(data == '\n')
        {
            //Line feed
            LCD_SelectLine(4);
            DataPosition = 60;
        }
        else
        {
            //Save line 3 new data
            DataLine3[DataPosition-40] = data;
        }
    }
    else if(DataPosition < 80)
    {
        if(data == '\n')
        {
            //Line feed (scroll)
            DataPosition = 80;
        }
        else
        {
            //Save line 4 new data
            DataLine4[DataPosition-60] = data;
        }
    }
    
    //Scroll
    if (DataPosition >= 80)
    {
        //Clear LCD
        WriteLCD(0,0x01);
        
        //Scroll lines
        for(i=0;i<20;i++)
        {
            DataLine1[i] = DataLine2[i];
        }
        for(i=0;i<20;i++)
        {
            DataLine2[i] = DataLine3[i];
        }
        for(i=0;i<20;i++)
        {
            DataLine3[i] = DataLine4[i];
        }
        
        //Rewrite lines
        LCD_SelectLine(1);
        i = 0;
        while(DataLine1[i] != '\0')
        {
            WriteLCD(1,DataLine1[i]);
            i++;
        }
        LCD_SelectLine(2);
        i = 0;
        while(DataLine2[i] != '\0')
        {
            WriteLCD(1,DataLine2[i]);
            i++;
        }
        LCD_SelectLine(3);
        i = 0;
        while(DataLine3[i] != '\0')
        {
            WriteLCD(1,DataLine3[i]);
            i++;
        }
        LCD_SelectLine(4);
        
        //Clear line 4 saved data
        for(i=0;i<20;i++)
        {
            DataLine4[i] = '\0';
        }
        
        //Save line 4 new data
        if(data != '\n')
        {
            DataLine4[0] = data;
        }
        DataPosition = 60;
    }
    
    //Write new data on LCD
    if(data != '\n')
    {
        WriteLCD(1,data);
        DataPosition++;
    }
}

void LCD_WriteString(char* data)
{
    int i = 0;
    while (data[i] != '\0' && i < 80)
    {
        LCD_WriteChar(data[i]);
        i++;
    }
}

void LCD_SelectLine(char line)
{
    char data;
    
    switch (line)
    {
        case 1:
            data = 0x80;
            break;
        case 2:
            data = 0xA0;
            break;
        case 3:
            data = 0xC0;
            break;
        case 4:
            data = 0xE0;
            break;
        default:
            return;
    }
    
    WriteLCD(0,data);
}
