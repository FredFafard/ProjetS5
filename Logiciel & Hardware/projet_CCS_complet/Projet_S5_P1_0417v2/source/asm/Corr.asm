;TODO (Commentaires JB de la demo)
;loader des zeros a linterieur de la grosse boucle plutot que faire une boucle independante dinitialisation
;Pas faire la racine quand on va calculer le module de la FFT


	.def _Corr_asm

_Corr_asm:

;void Corr_asm(int L, float t1[], float t2[]);
	;A4 -> Sortie
	;A1 -> Compteur
	;A3 -> Somme du diviseur
	;A7 -> Valeur Temporaire
	;A8 -> Ech courant 1
	;A9 -> Ech courant 2
	;A2 -> Pointeur tableau 2
	;A6 -> Pointeur tableau 1


	MV A4,A1
	MV B4,A2
; INITIALISATION DU TABLEAU DE SORTIE
	MVK 0,A4
	MVK 0,A3



BoucleSommation:

	SUB A1,1,A1 ;Décrémentation du  compteur

	LDW *A2[A1],A8	; Load valeur du 1er tableau
	NOP 4
	LDW *A6[A1],A9 	; Load valeur du 2e tableau
	NOP 4

	SUBSP A8,A9,A7	; Différence entre les deux valeurs
	NOP 3

	MPYSP A7,A7,A7	; Différence au carré
	NOP 3

	ADDSP A7,A4,A4	;Additionne au résultat précédent
	NOP 3

	MPYSP A9,A9,A9	; carré du 2e tableau
	NOP 3

	ADDSP A9,A3,A3 	; Additionne a la derniere valeur
	NOP 3

	[A1] B BoucleSommation
	NOP 5

	RCPSP A3,A3			; Normalisation
	MPYSP A3,A4,A4
	NOP 3
	MVKL 0x3F800000,A3
	MVKH 0x3F800000,A3 ; mettre 1 dans A3
	SUBSP A3,A4,A4
	NOP 3

	B B3
	NOP 5
	.end
