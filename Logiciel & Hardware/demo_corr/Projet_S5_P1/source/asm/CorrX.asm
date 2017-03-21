
	.def _Corrx_asm

_Corrx_asm:

;void Corrx_asm(int L, float t1[], float t2[], float* Pt_out);
	;A4 -> L
	;B1 -> CMPTEUR L DECREMENT
	;A1 -> CONDITION SOMMATION
	;A3 -> INCREMENT SOMMATION
	;A7 -> SORTIE TEMPORAIRE
	;A8 -> ECH1
	;A9 -> ECH2
	;A2 -> NOUVEAU POINTEUR DE B4


	MV A4,B1

; INITIALISATION DU TABLEAU DE SORTIE
Init:
	SUB B1,1,B1
	MVK 0,B2
	STW B2,*B6[B1]
	[B1] B Init
	NOP 5

	MV A4,B1
	MV B4,A2

; BOUCLER SUR LA SORTIE
BoucleSortie:
	SUB B1,1,B1
	MVK 0,A3
; BOUCLER SUR LES ECHANTILLONS
BoucleSommation:

	SUB A4,1,A5
	SUB A5,B1,A5
	ADD A5,A3,A5

	LDW *B6[B1],A7
	NOP 4
	LDW *A2[A3],A8
	NOP 4
	LDW *A6[A5],A9
	NOP 4

	MPYSP A9,A8,A8
	NOP 3

	ADDSP A8,A7,A7
	NOP 3

	STW A7,*B6[B1]
	NOP 4


	SUB B1,A3,A1
	ADD A3,1,A3
	[A1] B BoucleSommation
	NOP 5


	[B1] B BoucleSortie
	NOP 5



	B B3
	NOP 5
	.end
