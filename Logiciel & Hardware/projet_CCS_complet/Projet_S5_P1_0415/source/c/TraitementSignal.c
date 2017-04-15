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

float SeuilDetect = 0.9980;
float ResCorr = 0;

float TabAcq[NbECH_Tot*2]; // Pour stocker les echantillons avec valeurs imaginaires intercalees

float TabMoyenne[NbECH_Tot/2]; //Pour stocker les amplitudes moyennes des demi-fft (frequences positives)
float TabSmooth[NbECH_Tot/2]; //Pour l'execution de la fonction smooth

float TabCorr0[(NbECH_Tot/2)/DECIMATION];
float TabCorr1[(NbECH_Tot/2)/DECIMATION];
float TabCorr2[(NbECH_Tot/2)/DECIMATION];
float TabCorr3[(NbECH_Tot/2)/DECIMATION];
float TabCorr4[(NbECH_Tot/2)/DECIMATION];
float TabCorr5[(NbECH_Tot/2)/DECIMATION];
float TabCorr6[(NbECH_Tot/2)/DECIMATION];
float TabCorr7[(NbECH_Tot/2)/DECIMATION];
float TabCorr8[(NbECH_Tot/2)/DECIMATION];
float TabCorr9[(NbECH_Tot/2)/DECIMATION];
float TabCorr10[(NbECH_Tot/2)/DECIMATION];
float TabCorr11[(NbECH_Tot/2)/DECIMATION];
float TabCorr12[(NbECH_Tot/2)/DECIMATION];
float TabCorr13[(NbECH_Tot/2)/DECIMATION];
float TabCorr14[(NbECH_Tot/2)/DECIMATION];
float TabCorr15[(NbECH_Tot/2)/DECIMATION];



short index[NbECH_Tot*2];
static short Moy_courante = 0;
int NoEch = 0;

extern char CharIn;
extern int AcquisitionEnCours;

//Fonctions*************************************************

void Acquisition()
{
    TabAcq[2*NoEch] = input_right_sample();
    TabAcq[2*NoEch+1] = 0;

    if(NoEch >= NbECH_Tot - 1)
    {
        AcquisitionEnCours = 0;
        NoEch = 0;

        Traitement1();
        AcquisitionEnCours = 1;
    }
    else
    {
        NoEch++;
    }
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

    int i = 0;
    Smooth();

    switch(CharIn) {

    case '0':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr0[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '1':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr1[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '2':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr2[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '3':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr3[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '4':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr4[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '5':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr5[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '6':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr6[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '7':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr7[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '8':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr8[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case '9':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr9[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'A':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr10[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'B':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr11[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'C':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr12[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'D':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr13[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'E':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr14[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    case 'F':
        //Decimer en meme temps d'enregistrer dans le tableau
        for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
        {
            TabCorr15[i] = TabSmooth[i * DECIMATION];
        }
        CharIn = 0xFF;
        break;
    default :
        ResCorr = faireCorrelation();
        break;

    }

    AcquisitionEnCours = 1;
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


        for(k = 0 ; k < (NbECH_Tot/2)/DECIMATION ; k++)
        {
            TabCorr0[k] = 0;
            TabCorr1[k] = 0;
            TabCorr2[k] = 0;
            TabCorr3[k] = 0;
            TabCorr4[k] = 0;
            TabCorr5[k] = 0;
            TabCorr6[k] = 0;
            TabCorr7[k] = 0;
            TabCorr8[k] = 0;
            TabCorr9[k] = 0;
            TabCorr10[k] = 0;
            TabCorr11[k] = 0;
            TabCorr12[k] = 0;
            TabCorr13[k] = 0;
            TabCorr14[k] = 0;
            TabCorr15[k] = 0;
        }



}

int faireCorrelation()
{
    int returnVal = 16;
    int Results[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float TabDecime[(NbECH_Tot/2)/DECIMATION];
    int i;

    for(i = 0; i < (NbECH_Tot/2)/DECIMATION ; i++)
    {
        TabDecime[i] = TabSmooth[i * DECIMATION];
    }

    Results[0] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr0);
    Results[1] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr1);
    Results[2] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr2);
    Results[3] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr3);
    Results[4] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr4);
    Results[5] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr5);
    Results[6] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr6);
    Results[7] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr7);
    Results[8] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr8);
    Results[9] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr9);
    Results[10] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr10);
    Results[11] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr11);
    Results[12] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr12);
    Results[13] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr13);
    Results[14] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr14);
    Results[15] = Corr_asm(NbECH_Tot/8, TabDecime, TabCorr15);

    for(i = 0 ; i<16 ; i++)
    {
        if(Results[i] > SeuilDetect && Results[i] > Results[returnVal])
        {
            returnVal = i;
        }

    }

    return returnVal;
}
