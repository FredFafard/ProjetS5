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
#include "TraitementSignal.h"
#include "tw2048.h"


//Definitions*************************************************
#define NbECH_Tot 2048
#define NbSamples 960 //Nombre dechantillons pour le sweep
#define DECIMATION 4
#define NB_MOYENNE 4

// Variables**************************************************
#pragma DATA_ALIGN(TabAcq, 8)
#pragma DATA_ALIGN(TabMoyenne, 8)
#pragma DATA_ALIGN(TabCorr, 8)
#pragma DATA_ALIGN(TabSmooth, 8)

float TabAcq[NbECH_Tot*2]; // Pour stocker les echantillons avec valeurs imaginaires intercalees

float TabMoyenne[NbECH_Tot/2]; //Pour stocker les amplitudes moyennes des demi-fft (frequences positives)
float TabSmooth[NbECH_Tot/2]; //Pour l'execution de la fonction smooth

float TabCorr[(NbECH_Tot/2)/DECIMATION][16];
//float TabCorr2[(NbECH_Tot/2)/DECIMATION];
//float TabCorr3[(NbECH_Tot/2)/DECIMATION];
//float TabCorr4[(NbECH_Tot/2)/DECIMATION];

short index[NbECH_Tot*2];
static short Moy_courante = 0;
int NoEch = 0;

extern char CharIn;

//Fonctions*************************************************

int Acquisition()
{
    static int AcquisitionEnCours = 0;
    AcquisitionEnCours = 1;

    TabAcq[2*NoEch] = input_right_sample();
    TabAcq[2*NoEch+1] = 0;

    if(NoEch >= NbECH_Tot - 1)
    {
        AcquisitionEnCours = 0;
        NoEch = 0;

        Traitement1();
    }
    else
    {
        NoEch++;
    }

    return AcquisitionEnCours;
}


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

void Traitement1()
{
    faireFFT();
    faireMoyenne();

    if (Moy_courante >= NB_MOYENNE-1)
    {
        Moy_courante = 0;
        Traitement2();
    }
    else
    {
        Moy_courante++;
    }
    return;
}


void Traitement2(){

    Smooth();

    switch(CharIn) {

        case '0':
           //Decimer en meme temps d'enregistrer dans le tableau
           faireDecimation(0);
           CharIn = 0xFF;
           break;
       case '1':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(1);
          CharIn = 0xFF;
          break;
       case '2':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(2);
          CharIn = 0xFF;
          break;
       case '3':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(3);
          CharIn = 0xFF;
          break;
       case '4':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(4);
          CharIn = 0xFF;
          break;
       case '5':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(5);
          CharIn = 0xFF;
          break;
       case '6':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(6);
          CharIn = 0xFF;
          break;
       case '7':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(7);
          CharIn = 0xFF;
          break;
       case '8':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(8);
          CharIn = 0xFF;
          break;
       case '9':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(9);
          CharIn = 0xFF;
          break;
       case 'A':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(10);
          CharIn = 0xFF;
          break;
       case 'B':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(11);
          CharIn = 0xFF;
          break;
       case 'C':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(12);
          CharIn = 0xFF;
          break;
       case 'D':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(13);
          CharIn = 0xFF;
          break;
       case 'E':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(14);
          CharIn = 0xFF;
          break;
       case 'F':
          //Decimer en meme temps d'enregistrer dans le tableau
          faireDecimation(15);
          CharIn = 0xFF;
          break;
       default :
           faireCorrelation();
           break;

    }

}


void faireDecimation(int pos)
{
    int i = 0;

    for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
    {
        TabCorr[i][pos] = TabSmooth[i * DECIMATION];
    }

}


void faireFFT(){

    DSPF_sp_cfftr2_dit(TabAcq,twiddly,NbECH_Tot);
    DSPF_sp_bitrev_cplx((double*)TabAcq, index, NbECH_Tot);


    //Calculer les amplitudes au carre, puis les mettre dans la premiere moitie du vecteur dans NbECH_Tot/2 cases contigues
    int i;
    for(i = 0;i<NbECH_Tot/2;i++){

        TabAcq[i] = TabAcq[2*i]*TabAcq[2*i] + TabAcq[2*i+1]*TabAcq[2*i+1];
    }


}
void faireMoyenne()
{
    int i;
    if(Moy_courante==0)
    {
        for(i=0;i<NbECH_Tot/2;i++)
        {
            TabMoyenne[i] = TabAcq[i];
        }
    }
    else
    {
        for(i=0;i<NbECH_Tot/2;i++)
        {
            TabMoyenne[i] = TabMoyenne[i]+TabAcq[i];
        }
    }
}


void Smooth()
{
    float gain = 1/(float)DECIMATION;
    int i;
    int k;
    for(i=0;i<DECIMATION;i++)
    {
        TabSmooth[i] = 0;
        for(k=0;k<=i;k++)
        {
            TabSmooth[i] = TabSmooth[i]+TabMoyenne[i-k];
        }
        TabSmooth[i] = TabSmooth[i]*gain;
    }
    for(i=DECIMATION;i<(NbECH_Tot/2);i++)
    {
        TabSmooth[i] = gain*(TabMoyenne[i]+TabMoyenne[i-1]+TabMoyenne[i-2]+TabMoyenne[i-3]);
    }
}


void initTraitementSignal(){
    int i = 0;
    int k = 0;
    // Génération du tableau d'index pour bitrev
    bitrev_index(index, NbECH_Tot);

    for(i = 0 ; i<16 ; i++)
    {
        for(k = 0 ; k < (NbECH_Tot/2)/DECIMATION ; k++)
        {
            TabCorr[k][i] = 0;
        }
    }


}

void faireCorrelation()
{

}
