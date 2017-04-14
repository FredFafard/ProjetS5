	.def _enableInterrupts

	.data
MASK_EN_NMI .set 0x00000002
MASK_EN_INT_4 .set 0x00000010
MASK_EN_INT_11 .set 0x00000800
MASK_EN_INT_14 .set 0x00004000
MASK_EN_INT_15 .set 0x00008000
MASK_EN_GIE .set 0x00000001

	.text

_enableInterrupts
	.asmfunc
;Activation des interruptions non reset
	MVC IER, B0
	MVKL MASK_EN_NMI, B1
	MVKH MASK_EN_NMI, B1
	OR B1, B0, B0
	MVC B0, IER

;Activation de l'interruption int 4
	MVC IER, B0
	MVKL MASK_EN_INT_4, B1
	MVKH MASK_EN_INT_4, B1
	OR B1, B0, B0
	MVC B0, IER

;Activation de l'interruption int 11
	MVC IER, B0
	MVKL MASK_EN_INT_11, B1
	MVKH MASK_EN_INT_11, B1
	OR B1, B0, B0
	MVC B0, IER

;Activation de l'interruption int 14
	;MVC IER, B0
	;MVKL MASK_EN_INT_14, B1
	;MVKH MASK_EN_INT_14, B1
	;OR B1, B0, B0
	;MVC B0, IER

;Activation de l'interruption int 15
	MVC IER, B0
	MVKL MASK_EN_INT_15, B1
	MVKH MASK_EN_INT_15, B1
	OR B1, B0, B0
	MVC B0, IER

;Activation de GIE
	MVC CSR, B0
	MVKL MASK_EN_GIE, B1
	MVKH MASK_EN_GIE, B1
	OR B1, B0, B0
	MVC B0, CSR

	B B3
	NOP 5

	.endasmfunc

