/********************************************************
**  Session 5 - Projet
**  Fichier TraitementSignal.h
**  Auteurs : < Projet P1 >
**  Date : < 04/04/2017 >
********************************************************/

#ifndef SOURCE_C_TRAITEMENT_H_
#define SOURCE_C_TRAITEMENT_H_

#include "DSPF_sp_cfftr2_dit.h"
#include "DSPF_sp_bitrev_cplx.h"
#include "bitrev_index.h"
#include <stdio.h>
#include <math.h>

void Acquisition();
void Traitement1();
void Traitement2();
void faireFFT();
void faireMoyenne();
void Smooth();
void initTraitementSignal();
int faireCorrelation();


#endif /* SOURCE_C_TRAITEMENT_H_ */
