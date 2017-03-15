/* main.c */

#include <stdio.h>
#include <math.h>
extern float w[2*4096];
#include "twiddle.h"

float a[8192*2];
short c=4096;
#pragma DATA_ALIGN(a,32)

void main(void)
{

    //Generation d'un vecteur contenant un sinus, formatté avec partie imaginaire (voir spru657c)
    int i;
    for(i=0;i<(8192);i++)
    {
        int index = 2*i;
            a[index++] = sin(1000*2*(float)3.14159265358979*(float)i/(float)96000);
            a[index] = 0;
    }
    //Execution de la FFT avec la librairie TI

    DSPF_sp_cfftr2_dit(a,w,c);
    i = i+1;
    //DSPF_sp_bitrev_cplx(w);
}
