/*
 * test_fft.c
 *
 *  Created on: 15 mars 2017
 *      Author: faff2302
 */

#include "signalFFT.h"
#include "math.h"

#define L_SIGNAL 8192           // Nombre d'échantillon
#define PI 3.14159265358979     // PI
#define FE 96000                // Fréquence d'échantillonnage
#define FSIN 1000               // Fréquence Sine par génération

#pragma DATA_ALIGN(signal2, 8);
float signal2[2*L_SIGNAL];      // Données du signal avec intercalage de 0
short index[128];               // Longueur = 128 pour sqrt(2*L_SIGNAL)

void signalFFT(float signal[], float fft_signal[])
{
    int n = 0;
    short genSin = 1;

    //Generation d'un vecteur contenant un sinus, formatté avec partie imaginaire (voir spru657c)
    if(genSin == 1)
    {
        for(n = 0; n<2*L_SIGNAL; n+=2)
        {
            signal2[n] = sin(FSIN*2*PI*(float)n/FE); // transformer n en float pour précision
            signal2[n+1] = 0;
        }
    }
    else // Faire FFT avec le signal d'entrée
    {
        for(n=0; n<2*L_SIGNAL; n+=2)
        {
            signal2[n] = signal[n/2];
            signal2[n+1] = 0;
        }
    }

    //Execution de la FFT------------------------------------
    // Génération du tableau d'index pour bitrev
    birev_index(index, L_SIGNAL);

    // FFT radical 2
    DSPF_sp_cfftr2_dit(signal2, w, L_SIGNAL);

    // Remettre le tableau signal2 dans l'ordre
    DSPF_sp_bitrev_cplx(signal2, index, 2*L_SIGNAL);
    // ------------------------------------------------------

    // Amplitude du signal
    for (n = 0; n<L_SIGNAL; n++)
    {
        fft_signal[n] = pow(signal[2*n],2) + pow(signal[2*n+1],2);
    }
}
