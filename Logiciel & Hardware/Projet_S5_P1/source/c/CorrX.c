/*
 * CorrX.c
 *
 *  Created on: 15 mars 2017
 *      Author: faff2302
 */

#include "CorrX.h"

void zero_P(int L_t1, float t1[],int L_t2, float t2[],float* Pt_out1, float* Pt_out2)
{
    int L = L_t1+L_t2-1;
    int i = 0;

    for(i = 0; i<L; i++)
    {
        Pt_out1[i] = 0;
        Pt_out2[i] = 0;
    }

    for(i = 0; i<L; i++)
    {

        if(i<(L_t1-1))
        {
            Pt_out1[i] = t1[i];
            Pt_out2[i] = 0;
        }
        else if(i == (L_t1-1))
        {
            Pt_out1[i] = t1[i];
            Pt_out2[i] = t2[i-L_t1+1];
        }
        else
        {
            Pt_out1[i] = 0;
            Pt_out2[i] = t2[i-L_t1+1];
        }

    }

}

void Corrx_c(int L, float t1[], float t2[], float* Pt_out)
{
    int i = 0;
    int j = 0;


    for(i = 0; i<L; i++)
    {
        Pt_out[i] = 0;
    }

    for(i = 0; i<L; i++)
    {
        for(j = 0; j < (i+1); j++)
        {
            Pt_out[i] = Pt_out[i] + (t1[j] * t2[L+j-i-1]);
        }
    }

}
