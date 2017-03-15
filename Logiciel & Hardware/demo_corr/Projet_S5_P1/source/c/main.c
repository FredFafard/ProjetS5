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
    float tab1[8] = {-5,-30,20,-2,-1,1,7,8};
    float* PT1 = &tab1[0];
    float tab2[3] = {3,-6,1};
    float* PT2 = &tab2[0];
    int L1 = 8;
    int L2 = 3;
    float T_OUT[10];
    float* PT_OUT = &T_OUT[0];
    float T_C1[10];
    float* PTC1 = &T_C1[0];
    float T_C2[10];
    float* PTC2 = &T_C2[0];



    zero_P(L1, tab1, L2, tab2, PTC1, PTC2);
    Corrx_asm(L1+L2-1, T_C1, T_C2, PT_OUT);
    return;
}
