
/*
 * CorrX.h
 *
 *  Created on: 15 mars 2017
 *      Author: faff2302
 */

#ifndef SOURCE_C_CORRX_H_
#define SOURCE_C_CORRX_H_


void Corrx_c(int L, float t1[], float t2[], float* Pt_out);
void Corrx_asm(int L, float t1[], float t2[], float* Pt_out);
float Corr_asm(int L, float t1[], float t2[]);

void zero_P(int L_t1, float t1[],int L_t2, float t2[],float* Pt_out1, float* Pt_out2);

#endif /* SOURCE_C_CORRX_H_ */
