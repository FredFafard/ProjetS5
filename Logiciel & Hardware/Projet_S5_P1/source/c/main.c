/* main.c */

#include <stdio.h>
#include <math.h>
#include "twiddle.h"
#include "main.h"
#include "CorrX.h"
#include "test_fft.h"



void main(void)
{

    Demo_Corr();

}


void Demo_Corr()
{
    float tab1[5] = {1,2,3,4,5};
    float* PT1 = &tab1[0];
    float tab2[7] = {7,6,5,4,3,2,1};
    float* PT2 = &tab2[0];
    int L1 = 5;
    int L2 = 7;
    float T_OUT[11];
    float* PT_OUT = &T_OUT[0];
    float T_C1[11];
    float* PTC1 = &T_C1[0];
    float T_C2[11];
    float* PTC2 = &T_C2[0];



    zero_P(L1, tab1, L2, tab2, PTC1, PTC2);
    Corrx_c(L1+L2-1, T_C1, T_C2, PT_OUT);
    return;
}
