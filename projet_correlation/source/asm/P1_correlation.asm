		.def	_P1_correlation

;		.data
;satPlus .word 0xFFFFFF 		; 2^24-1
;satMoin .word 0xFF000000	; -(2^24)
	;.text

_P1_correlation:
	.asmfunc

; Mémoriser le contenu de AMR / contexte
			MVC	AMR, B5
			STW	B5,*--B15

; Ajuster le registre AMR
			MVKL 0x00C08000, B9	; Utiliser B7 comme pointeur avec BK1 comme compteur vers
			MVKH 0x00C08000, B9	; Le tampon contient 64 échantillons de 16 bits chacuns, donc 128 octets (2 X 64)
			MVC B9, AMR


;	faire la correlation ici !
; 	on charge les 2 tableaux a correler dans A4, B4
;	sortir dans A6





; Restaurer le contenu de AMR	/ contexte
			LDW	*B15++,B5
			NOP	5
			MVC	B5,AMR

	B B3		;branche de sortie
	NOP 5
	.endasmfunc
.end
