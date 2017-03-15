/*
*       TEST DE CORRELATION PROJET S5
*       15 mars 2017 -SL
*/
#include <stdio.h>
#include <math.h>
#include "dsk6713_aic23.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
//#include "getNewCommand.h"        //pas sur -sl
#include "C6713Helper_UdeS.h"
//#include "P1_correlation.asm"       // notre fonction de correlation

extern void P1_correlation();

// VARIABLES GLOBALES


// VARIABLES GLOBALES POUR DSK
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 			 // Fréquence d'échantillonnage
#define DSK6713_AIC23_INPUT_LINE 0x0011		 // Définition de l'entrée LINE IN
Uint16 inputsource=DSK6713_AIC23_INPUT_LINE; // Selection de l'entrée LINE IN

#define GAUCHE 0 // Définition du haut-parleur gauche
#define DROIT  1 // Définition du haut-parleur droit
union {Uint32 uint; short channel[2];} AIC23_data; // Pour contenir les deux signaux

#define TAMPON_L  64
#pragma DATA_ALIGN(tampon, TAMPON_L*2); // Requis pour l'adressage circulaire en assembleur
short tampon[TAMPON_L]={0};         // Tampon d'échantillons
short *pTampon=&tampon[TAMPON_L-1]; // Pointeur sur l'échantillon courant

// NE PAS METTRE DE CODE BLOQUANT
void main() 
{

		while (1)
		{

		}

}

// fonction de l'APP5
// Attente en sec. (approximatif)
/*
void attendre(float seconds)
{
	int cnt=0;
	int fin = (int)NB_CYCLES_PAR_SEC*seconds;
	while (cnt++<fin) {}
}
*/

// FONCTION DE L'APP5 - JE NE SAIS PAS SI CEST UTILE OU NON -SL
/********************************************************************************************
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        2 septembre 2009
  Revisions:   
    DESCRIPTION : 
	 Code executé à toutes les interruptions
********************************************************************************************/
/*
interrupt void c_int11() 
{
	float echOut; 		 // Amplitude de l'échantillon générée pour l'écoute d'une note
	short echLineIn;	 // Ampliutde de l'échantillon provenant de l'entrée LINE IN
	short echLineInFilt; // Ampliutde de l'échantillon filtré
	short pwm[10] = {0,0,0,0,0,0,0,0,25,25}; // Pulse width modulation
	int debugFiltres = 0;
	short xFIR;
	static int n=1;

	// Capture de l'échantillon provenant de l'entrée "IN"
	echLineIn = (short) input_sample();

	//
	// VOTRE **SOLUTION** DE FILTRAGE FIR + IIR REMPLACE LA PROCHAINE LIGNE!!!
	//echLineInFilt = echLineIn;
	static int FIR_ASM = 0, FLT_IIR = 0;

	    // Filtrage FIR passe-haut en assembleur ou en C
	    if (FIR_ASM)
	        // Dans le code fourni, cette fonction fait simplement incrémenter le
	        // pointeur pTampon et retourner l'échantillon d'entrée, x,
	        // dans la valeur de sortie, xFIR - i.e. c'est un simple "pass-through"
	        // qui ne fait pas de filtrage.
	        pTampon = direct1FIR_ASM(pTampon, echLineIn, CoeffsFIR, &xFIR);
	    else
	        pTampon = direct1FIR(pTampon, echLineIn, CoeffsFIR, FIRNbCOEFFS, tampon, TAMPON_L, &xFIR);

	    // Filtrage IIR biquad, ou pas
	    if (FLT_IIR)
	        echLineInFilt = filtrerCascadeIIR(Commandes.noCorde, xFIR);
	    else
	        echLineInFilt = xFIR;
	//
	//

	// Si le tampon d'échantillons filtrés pour l'autocorrélation n'est pas plein,
	// y ajouter l'échantillon courant filtré
	if (noEchFilt < L_TAMPON) {
		// Enregistrement de l'échantillon dans le tampon
		tamponEchFilt[noEchFilt++] = (float) echLineInFilt;
	}

	// Si une écoute est demandée, sortir l'amplitude sur le canal droit
	if (Commandes.isPlay) {
		// Générer l'échantillon audio pour écouter la tonalité de la corde
//		echOut = genFrqCos(Commandes.noCorde, Commandes.isPlay);

		// VOTRE **SOLUTION**, À VOUS DE CODER CETTE FONCTION
		echOut = genFrq_methode2(Commandes.noCorde, Commandes.isPlay);

		// Assigner l'échantillon au canal droit de la sortie HEADPHONE
		AIC23_data.channel[DROIT] =  (short)(1000*echOut);
	}
	// Autrement, sortir l'échantillon d'entrée non-filtrée sur le canal droit
	// pour fins de débuggage de vos filtres
	else
		AIC23_data.channel[DROIT] = echLineIn;

	// Assigner l'erreur d'accordement au canal gauche de la sortie HEADPHONE
	// NOTE : Branchez le canal gauche à un oscilloscope pour observer l'erreur
	if (debugFiltres == 0)
		AIC23_data.channel[GAUCHE] = (short)errAccordement*pwm[n++%10];
	// Autrement, sortir l'échantillon filtré sur le canal gauche,
	// pour fins de débuggage de vos filtres
	else
		AIC23_data.channel[GAUCHE] = echLineInFilt;

	// Sortir les deux signaux sur "HP/OUT"
	output_sample(AIC23_data.uint);			

	// Capturer des commandes usager provenant des DIP switchs
	getCommandes(&Commandes); 

	// Afficher les commandes entrées par l'utilisateur sur les LEDs
	ajusterLED(Commandes.noCorde);

	return;
}

*/
