
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
#include "csl_gpio.h"
#include "csl_irq.h"


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
int echActuel = 0;

int NoSignalEnr = 0;
int AcquisitionEnCours = 1;
char CharIn = 0xFF;

extern GPIO_Handle My_GPIO;

//Programme principal*****************************************

void main(void)
{
//------------------- Configurations et initialisation -------------------//
    //Timer1_ConfigStart();

    comm_intr();
    enableInterrupts();
    DSK6713_Config();
    AIC23_Config();
    initTraitementSignal();
    SPI_config(); // Initialisation du SPI et de l'UART
    initGPIO();
    DSK6713_waitusec(100);          // On fait une pause de 100 microsecondes.
//--------------------------------------------------------------------------

    //Programme principal
    //Demo_Corr();

    while(1)
    {
//-------------------- Interruption 11 (Codec 96 kHz) --------------------//
        if(interrupt11Flag == 1)
        {


            interrupt11Flag = 0;

            if(AcquisitionEnCours == 1)
            {
                SweepGeneration();
                Acquisition();
            }
            else
            {
                Traitement();
            }
        }
//--------------------------------------------------------------------------

//------------------- Interruption 4 (GPIO4_dataReady) -------------------//
        if (interrupt4Flag == 1)
        {
            CharIn = SPI_READ_DATA();
            CharIn = SPI_READ_DATA();
            interrupt4Flag = 0;

        }
//--------------------------------------------------------------------------
    }
}

interrupt void c_int11(void)
{

    interrupt11Flag = 1;

    output_sample(echActuel);
    //SweepGeneration();
//    static int SampRate = 0;
//    if(Timer1sec == 0)
//    {
//        SampRate++;
//    }
}

interrupt void c_int15(void)
{
    static int cmptrTimer = 0;

    if(cmptrTimer < 10000)
    {
        cmptrTimer++;
        Timer1sec = 0;
    }
    else
    {
        Timer1sec = 1;
    }
}

//Initialisation des sorties de contrôle des relais et activation des buffers sur le PCB de projet
void initGPIO(void){

    //Activation de la sortie GPO0 - Controle du buffer de protection U2A sur le PCB de projet
    GPIO_pinEnable(My_GPIO, GPIO_PIN0);
    GPIO_pinDirection(My_GPIO,GPIO_PIN0, GPIO_OUTPUT);

    //Activation de la sortie GPO3 - Controle du buffer de protection U2D sur le PCB de projet
    GPIO_pinEnable(My_GPIO, GPIO_PIN3);
    GPIO_pinDirection(My_GPIO,GPIO_PIN3, GPIO_OUTPUT);


    //Activation des 4 GPIOs pour le controle des relais
    GPIO_pinEnable(My_GPIO, GPIO_PIN8);
    GPIO_pinDirection(My_GPIO,GPIO_PIN8, GPIO_OUTPUT); //Ventilateur
    GPIO_pinWrite(My_GPIO,GPIO_PIN8,1); //init a OFF

    GPIO_pinEnable(My_GPIO, GPIO_PIN9);
    GPIO_pinDirection(My_GPIO,GPIO_PIN9, GPIO_OUTPUT); //Lumiere
    GPIO_pinWrite(My_GPIO,GPIO_PIN9,1); //init a OFF

    GPIO_pinEnable(My_GPIO, GPIO_PIN10);
    GPIO_pinDirection(My_GPIO,GPIO_PIN10, GPIO_OUTPUT); //Eau
    GPIO_pinWrite(My_GPIO,GPIO_PIN10,1); //init a OFF

    GPIO_pinEnable(My_GPIO, GPIO_PIN11);
    GPIO_pinDirection(My_GPIO,GPIO_PIN11, GPIO_OUTPUT); //Musique
    GPIO_pinWrite(My_GPIO,GPIO_PIN11,1); //init a OFF




    //Met la sortie a 0 pour activer le buffer U2A sur le PCB de projet
    GPIO_pinWrite(My_GPIO,GPIO_PIN0,0);

    //Met la sortie a 0 pour activer le buffer U2D sur le PCB de projet
    GPIO_pinWrite(My_GPIO,GPIO_PIN3,0);



}


void toggleGPIO(int noGPIO){

    if(GPIO_pinRead(My_GPIO,noGPIO)){
        GPIO_pinWrite(My_GPIO,noGPIO,0);
    }
    else{
        GPIO_pinWrite(My_GPIO,noGPIO,1);
    }

}
