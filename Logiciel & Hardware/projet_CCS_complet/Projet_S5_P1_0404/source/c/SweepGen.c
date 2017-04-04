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






//Fonctions*************************************************
void SweepGeneration(void)
{
    static int cmptrSS = 0;
    static int increment = 1;
    static int Sample;

    Sample = 1.5*SweepSamples[cmptrSS];
    output_sample(Sample);

    cmptrSS = cmptrSS + increment;

    if (cmptrSS >= 959 || cmptrSS <= 0)
    {
        increment = increment * -1;
    }

    return;
}



