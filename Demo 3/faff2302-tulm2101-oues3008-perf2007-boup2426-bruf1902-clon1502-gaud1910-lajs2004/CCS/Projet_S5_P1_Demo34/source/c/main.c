
/* Fichier principal du projet CCS - Equipe P1
 *
 * Entrees
 *
 * Sorties
 *
 *
 */
int Timer1sec = 0;
//Includes***************************************************
#include <stdio.h>
#include <math.h>
#include "SPI_driver.h"
#include "C6713Helper_UdeS.h"
#include "main.h"
#include "CorrX.h"
#include "signalFFT.h"
#include "dsk6713.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"


//Definitions*************************************************

//CPLD:
#define CPLD_USER_REG (unsigned int*)0x90080000
#define LED0 0x01
#define LED1 0x02
#define LED2 0x04
#define LED3 0x08
#define SW0 0x10
#define SW1 0x20
#define SW2 0x40
#define SW3 0x80

//GPIO

//Timer 1:
#define TIMER1CTL (unsigned int*)0x01980000
#define TIMER1PRD (unsigned int*)0x01980004

//Codes AIC23:
#define NBR_SAMPLES_MAX 8192 //10 secondes a 8kHz
Uint32 fs = DSK6713_AIC23_FREQ_96KHZ;
#define DSK6713_AIC23_INPUT_LINE 0x0011      // D�finition de l'entr�e LINE IN
Uint16 inputsource = DSK6713_AIC23_INPUT_LINE;



//Programme principal*****************************************

void main(void)
{
    char CharIn = 0;

    //Initialisations:
    //configAndStartTimer1();
    //comm_intr();
    enableInterrupts();

    // init du DSK
        DSK6713_init();

    // Initialisation des DIPs.
        DSK6713_DIP_init();
        // Initialisation des LEDs.
        DSK6713_LED_init();
        // Initialisation du SPI et de l'UART :
        SPI_config();
        // On fait une pause de 100 microsecondes.
        DSK6713_waitusec(100);


    //Programme principal
    Demo_Corr();
    while(1)
    {


        // si int 4 pop
        if (interrupt4Flag == 1)
        {
          CharIn = SPI_READ_DATA();
          interrupt4Flag = 0;

          SPI_WRITE_DATA(' ');
          DSK6713_waitusec(100);
          SPI_WRITE_DATA(CharIn);
          DSK6713_waitusec(100);
          SPI_WRITE_DATA(' ');
          DSK6713_waitusec(100);

         if(CharIn == 'R')
         {
              SendDemo();
          }
        }
    }

}


void Demo_Corr()
{
    float tab1[8] = {-5, -30, 20, -2, -1, 1, 7, 8};
    //float* PT1 = &tab1[0];
    float tab2[3] = {3,-6,1};
    //float* PT2 = &tab2[0];
    int L1 = 8;
    int L2 = 3;
    float T_OUT[10];
    float* PT_OUT = &T_OUT[0];
    float T_C1[10];
    float* PTC1 = &T_C1[0];
    float T_C2[10];
    float* PTC2 = &T_C2[0];

    zero_P(L1, tab1, L2, tab2, PTC1, PTC2);
    Corrx_c(L1+L2-1, T_C1, T_C2, PT_OUT);

    return;
}

void configAndStartTimer1(void){

    *TIMER1CTL &= ~0xC0; // mettre le compteur a hold
    *TIMER1PRD = 0x125; //96KHz
    *TIMER1CTL |= 0x0301; //clksrc = 1 (internal clock) et CP (clock/pulse) =1
    *TIMER1CTL |= 0x00C0; //mettre le compteur en marche

}

interrupt void c_int11(void){


    output_sample(input_sample());

    static int SampRate = 0;
    if(Timer1sec == 0)
    {
        SampRate++;
    }


}

interrupt void c_int15(void){


    static int cmptrTimer = 0;

    if(cmptrTimer < 96000)
    {
        cmptrTimer++;
        Timer1sec = 0;
    }
    else
    {
        Timer1sec = 1;
    }

}
