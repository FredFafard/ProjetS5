
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
#include "TraitementSignal.h"
#include "Config.h"


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

//Codes AIC23:
#define NBR_SAMPLES_MAX 8192 //10 secondes a 8kHz
Uint32 fs = DSK6713_AIC23_FREQ_96KHZ;
#define DSK6713_AIC23_INPUT_LINE 0x0011      // Définition de l'entrée LINE IN
Uint16 inputsource = DSK6713_AIC23_INPUT_LINE;


int interrupt11Flag = 0;
int interrupt15Flag = 0;

int NoSignalEnr = 0;
int AcquisitionEnCours = 0;
char CharIn = 0xFF;

//Programme principal*****************************************

void main(void)
{


//------------------- Configurations et initialisation -------------------//
    Timer1_ConfigStart();
    comm_intr();
    enableInterrupts();
    DSK6713_Config();
    AIC23_Config();
    initTraitementSignal();
    SPI_config();                   // Initialisation du SPI et de l'UART
    DSK6713_waitusec(100);          // On fait une pause de 100 microsecondes.
//--------------------------------------------------------------------------

    //Programme principal
    Demo_Corr();

    while(1)
    {
//-------------------- Interruption 11 (Codec 96 kHz) --------------------//
        if(interrupt11Flag == 1)
        {
            SweepGeneration();
            interrupt11Flag = 0;

            if(AcquisitionEnCours == 1)
            {
                AcquisitionEnCours = Acquisition();
            }
        }
//--------------------------------------------------------------------------

//------------------- Interruption 4 (GPIO4_dataReady) -------------------//
        if (interrupt4Flag == 1)
        {
            CharIn = SPI_READ_DATA();
            interrupt4Flag = 0;

        }
//--------------------------------------------------------------------------
    }
}


void Demo_Corr()
{
    float tab1[8] = {-5, -30, 20, -2, -1, 1, 7, 8};
    //float* PT1 = &tab1[0];
    float tab2[8] = {3, -6, 1, 2, 3, 4, 5, 6};
    //float* PT2 = &tab2[0];
    int L1 = 8;
    int L2 = 8;
    float T_OUT[15];
    float* PT_OUT = &T_OUT[0];
    float T_C1[15];
    float* PTC1 = &T_C1[0];
    float T_C2[15];
    float* PTC2 = &T_C2[0];

    zero_P(L1, tab1, L2, tab2, PTC1, PTC2);
    Corrx_asm(L1+L2-1, T_C1, T_C2, PT_OUT);

    return;
}





interrupt void c_int11(void){

    static int int11cmptr = 0;
    int11cmptr++;

    interrupt11Flag = 1;


    static int SampRate = 0;
    if(Timer1sec == 0)
    {
        SampRate++;
    }


}

interrupt void c_int15(void)
{
    interrupt15Flag = 1;
}
