/********************************************************
**  Session 5 - Projet
**  Fichier Config.c
**  Auteurs : < Projet P1 >
**  Date : < 04/04/2017 >
********************************************************/

// Include-----------------------------------------------
#include "dsk6713.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"

// Define -----------------------------------------------
//Timer 1
#define TIMER1CTL (unsigned int*)0x01980000
#define TIMER1PRD (unsigned int*)0x01980004

// Handles-----------------------------------------------
DSK6713_AIC23_CodecHandle hCodec;


void DSK6713_Config(void)
{
    // initialisation du DSK
    DSK6713_init();
    // Initialisation des DIPs.
    DSK6713_DIP_init();
    // Initialisation des LEDs.
    DSK6713_LED_init();

    return;
}

void AIC23_Config(void)
{

    // Ajuster gain de sortie de l'AIC
    DSK6713_AIC23_outGain(hCodec, 0x7F); // MAX 0x7F

    return;
}

void Timer1_ConfigStart(void)
{
    *TIMER1CTL &= ~0xC0; // mettre le compteur a hold
    *TIMER1PRD = 0x125; //96kHz
    *TIMER1CTL |= 0x0301; //clksrc = 1 (internal clock) et CP (clock/pulse) =1
    *TIMER1CTL |= 0x00C0; //mettre le compteur en marche
}
