/********************************************************
**  Session 5 - Projet
**  Fichier SPI_driver.h
**  Auteurs : < Projet P1 >
**  Date : < 03/04/2017 >
********************************************************/

#pragma once

#ifndef _SPI_MODULE_
#define _SPI_MODULE_

/***************************************************************************
    Include headers :
***************************************************************************/
// standard libraries 
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include "dsk6713_aic23.h" //codec-DSK support file
#include <csl_mcbsp.h>




/***************************************************************************
    Set EXTERN macro :
***************************************************************************/

#ifdef SPI_DRIVER_MODULE_IMPORT
    #define EXTERN
#else 
    #define EXTERN extern
#endif

/***************************************************************************
    Constants declaration :
***************************************************************************/

//#define something something_else

/***************************************************************************
    Types declaration here :
***************************************************************************/

// typedef, struct, enum, union, etc.

/***************************************************************************
    Global variables declaration :
***************************************************************************/

// look at example for EXTERN pattern/

EXTERN short sample16;
EXTERN char sample;
EXTERN char message;
EXTERN int message_treated;
EXTERN int UnDrapeau;
EXTERN unsigned int Record;
EXTERN int Timer_Record;
void SendDemo();

EXTERN int interrupt4Flag

#ifdef SPI_DRIVER_MODULE_IMPORT
    = 0
#endif
;

extern MCBSP_Handle DSK6713_AIC23_CONTROLHANDLE;

/***************************************************************************
    Function prototype :
***************************************************************************/

// Initialisation du module SPI
EXTERN void MCBSP_SPI_init(void);
// Écriture d'un charactère par SPI vers le MAX3111
EXTERN void SPI_WRITE_DATA(char);
// Lecture d'un charactère du MAX3111 par SPI
EXTERN char SPI_READ_DATA();
// Initialisation du port externe 4 en input pour l'interrupt ExtInt4
EXTERN void init_ext_intr();
// Configuration du module SPI
EXTERN void SPI_config();
// ajoutez vos prototype de fonction ici

//EXTERN void Treated_CHAR2INT(char bof);
//EXTERN void Audio_init(void);
//EXTERN void Treated_INT2CHAR(short sample16);

#undef SPI_DRIVER_MODULE_IMPORT
#undef EXTERN

#endif // end of #ifndef _SPI_MODULE_

// end of SPI_driver.h
