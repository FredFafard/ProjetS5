/********************************************************
**  Session 5 - Projet
**  Fichier SweepGen.c
**  Auteurs : < Projet P1 >
**  Date : < 04/04/2017 >
********************************************************/

//Includes***************************************************
#include <stdio.h>
#include <math.h>
#include <Sweep2040kHz.dat>//-------------------------
#include "C6713Helper_UdeS.h"
#include "dsk6713.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"

//Definitions*************************************************
#define NbECH_Tot 8192
#define NbSamples 960

// Variables**************************************************
#pragma DATA_ALIGN(SignalEnr1, 8)
//#pragma DATA_ALIGN(SignalEnr2, 8)
//#pragma DATA_ALIGN(SignalEnr3, 8)
short SignalEnr1[NbECH_Tot];
short SignalEnr2[NbECH_Tot];
//short SignalEnr3[NbECH_Tot];
int NoEch = 0;

//Fonctions*************************************************
void SweepGeneration(void)
{
    static int cmptrSS = 0;
    static int increment = 1;
    static short Sample;

    Sample = 1.5*SweepSamples[cmptrSS];
    output_sample(Sample);

    cmptrSS = cmptrSS + increment;

    if (cmptrSS >= NbSamples-1 || cmptrSS <= 0)
    {
        increment = increment * -1;
    }

    return;
}

int Acquisition(char CharIn)
{
    static int AcquisitionEnCours = 0;
    AcquisitionEnCours = 1;

    switch(CharIn)
    {
       case 'Q'  :
          SignalEnr1[NoEch] = input_right_sample();
          break;

       case 'W'  :
          SignalEnr2[NoEch] = input_right_sample();
          break;

       case 'E'  :
          //SignalEnr3[NoEch] = input_right_sample();
          break;

       default:
       break;
    }

    if(NoEch >= NbECH_Tot - 1)
    {
        AcquisitionEnCours = 0;
        NoEch = 0;
    }
    else
    {
        NoEch++;
    }

    return AcquisitionEnCours;
}



