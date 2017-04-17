/********************************************************
**  Session 5 - Projet
**  Fichier SPI_driver.c
**  Auteurs : < Projet P1 >
**  Date : < 03/04/2017 >
********************************************************/


/***************************************************************************
	Include headers :
***************************************************************************/

//#include "something.h"


/***************************************************************************
	Include Module Header :
***************************************************************************/

#define SPI_DRIVER_MODULE_IMPORT
#include "SPI_driver.h"
#include <stdio.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_gpio.h>
#include <dsk6713.h>
#include <csl_mcbsphal.h>
#include <csl_irq.h>



MCBSP_Handle My_McBSP;
GPIO_Handle My_GPIO;
/****************************************************************************
	Extern content declaration :
****************************************************************************/

extern void vectors();   // Vecteurs d'interruption



/****************************************************************************
	Private macros and constants :
****************************************************************************/

// These defines are only valid is this .c



/****************************************************************************
	Private Types :
****************************************************************************/

// These type declaration are only valid in this .c
#define SPI_WRITE_CONFIG    0x0000E441
#define SPI_READ_CONFIG     0x00004000
#define SPI_WRITE           0x00008000
#define SPI_READ            0x00000000

MCBSP_Handle MySpiHandle;

/****************************************************************************
	Private global variables :
****************************************************************************/


/****************************************************************************
	Private functions :
****************************************************************************/

// these function can only be called by this .c
// Use static keyword

/****************************************************************************
	Public functions :
****************************************************************************/
MCBSP_Config MCBSP_SPI_Config = {



        MCBSP_FMKS(SPCR, FREE, NO)              |
        MCBSP_FMKS(SPCR, SOFT, NO)              |
        MCBSP_FMKS(SPCR, FRST, YES)             |
        MCBSP_FMKS(SPCR, GRST, YES)             |
        MCBSP_FMKS(SPCR, XINTM, XRDY)           |
        MCBSP_FMKS(SPCR, XSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, XRST, YES)             |
        MCBSP_FMKS(SPCR, DLB, OFF)              |
        MCBSP_FMKS(SPCR, RJUST, RZF)            |
        MCBSP_FMKS(SPCR, CLKSTP, DELAY)         | // DELAY POUR LE SPI MODE ET POUR AVOIR LE TEMPS D'ENVOYER LES DONNÉES
        MCBSP_FMKS(SPCR, DXENA, OFF)            |
        MCBSP_FMKS(SPCR, RINTM, RRDY)           |
        MCBSP_FMKS(SPCR, RSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, RRST, YES),

        MCBSP_FMKS(RCR, RPHASE, SINGLE)         |
        MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDLEN2, 8BIT)          | // 8 BIT
        MCBSP_FMKS(RCR, RCOMPAND, MSB)          |
        MCBSP_FMKS(RCR, RFIG, NO)               |
        MCBSP_FMKS(RCR, RDATDLY, 1BIT)          | // 1 BIT DATA DELAY POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(RCR, RFRLEN1, OF(0))         |
        MCBSP_FMKS(RCR, RWDLEN1, 16BIT)         | // ON VA LIRE LES 16 BIT
        MCBSP_FMKS(RCR, RWDREVRS, DISABLE),

        MCBSP_FMKS(XCR, XPHASE, SINGLE)         |
        MCBSP_FMKS(XCR, XFRLEN2, DEFAULT)       |
        MCBSP_FMKS(XCR, XWDLEN2, 8BIT)          | // ON ENVOIE 8 BIT APRES LA DISCRIMINATION
        MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
        MCBSP_FMKS(XCR, XFIG, NO)               |
        MCBSP_FMKS(XCR, XDATDLY, 1BIT)          | // 1 BIT DATA DELAY POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(XCR, XFRLEN1, OF(0))         |
        MCBSP_FMKS(XCR, XWDLEN1, 16BIT)         | // 16 BIT
        MCBSP_FMKS(XCR, XWDREVRS, DISABLE),

        MCBSP_FMKS(SRGR, GSYNC, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSP, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSM, INTERNAL)       | // INTERNAL CLOCK POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(SRGR, FSGM, DXR2XSR)         | // DXR2XSR POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(SRGR, FPER, DEFAULT)         |
        MCBSP_FMKS(SRGR, FWID, DEFAULT)         |
      //  MCBSP_FMKS(SRGR, CLKGDV, OF(32)),         // (CPU/2)/(16*BAUDRATE-1)=31 // 22 OC? (VALEUR DU PROF)
        MCBSP_FMKS(SRGR, CLKGDV, OF(100)),

        MCBSP_MCR_DEFAULT,
        MCBSP_RCER_DEFAULT,
        MCBSP_XCER_DEFAULT,

        MCBSP_FMKS(PCR, XIOEN, SP)              |
        MCBSP_FMKS(PCR, RIOEN, SP)              |
        MCBSP_FMKS(PCR, FSXM, INTERNAL)         | // INTERNAL POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
        MCBSP_FMKS(PCR, CLKXM, OUTPUT)          | // OUTOUT POUR OPÉRATION EN SPI MODE
        MCBSP_FMKS(PCR, CLKRM, INPUT)           |
        MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
        MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
        MCBSP_FMKS(PCR, FSXP, ACTIVELOW)        | // METTRE SUR ACTIVE LOW
        MCBSP_FMKS(PCR, FSRP, ACTIVELOW)        | // METTRE SUR ACTIVE LOW
        MCBSP_FMKS(PCR, CLKXP, RISING)          | // SUR LE RISING EDGE
        MCBSP_FMKS(PCR, CLKRP, RISING)
    };

int cpt1=0;
void SPI_config()
{
    // 1- Configuration de la communication SPI :
    MCBSP_SPI_init();

    // 2- Configuration de l'UART :

        // Write write config
        // Read dummy to empty read buffer
        // Write read config
        // Read si la config est pareille que celle que l'on voulait écrire
        // Si pas pareil :
            // Write dummy pour avoir une nouvelle lecture
            // Read config
        // Si pareil :
            // On a finit, la config est correcte.

        // Initilialisation d'une variable contenant le résultat des lectures du MCBSP
        Uint32 result = 0;

        // On écrit la commande pour envoyer la configuration dans le MAX3111 pour configurer l'UART:
        MCBSP_write(MySpiHandle,SPI_WRITE_CONFIG);             // Entre la config d'écriture
        // On fait une lecture bidon pour pouvoir en recevoir une nouvelle plus tard
        result = MCBSP_read(MySpiHandle);                       // Dummy read;

        // On fait une petite pause pour laisser le temps aux configurations d'être appliquées
        DSK6713_waitusec(10);

        // On envoie la commande pour pouvoir lire la configuration
        MCBSP_write(MySpiHandle,SPI_READ_CONFIG);               // Entre la config de lecture
        // On fait une petite pause pour laisser le temps à la commande de se rendre
        DSK6713_waitusec(10);
        // On lit le résultat
        result = MCBSP_read(MySpiHandle);




         // Si on prend les 16 derniers bits :
         // On créé une variable qui ne contient que les 14 bits de configurations sans la commande pour configurer (2 premiers bits)
         Uint32 configWithout2FirstsBits = (Uint32)SPI_WRITE_CONFIG & 0x00003FFF;
         // Tant et aussi longtemps que le résultat
         while (result != configWithout2FirstsBits)
               {
                    // On envoie la commande pour lire la configuration
                    MCBSP_write(MySpiHandle,SPI_READ_CONFIG);
                    // On attend un peu
                    while (!MCBSP_rrdy(MySpiHandle));
                    // On lit le résultat
                     result = MCBSP_read(MySpiHandle);
                     // On pad le résulat pour ne garder que les 14 derniers bits (ceux contenants la configuration)
                     result = result & 0x00003FFF;
                     cpt1++;

                }

         while (!MCBSP_rrdy(MySpiHandle));
              // Lire une donnée de l'UART pour vider son tampon
              MCBSP_write(MySpiHandle,SPI_READ);
              result = MCBSP_read(MySpiHandle);


       // Clear ext_int4
         IRQ_clear(IRQ_EVT_EXTINT4);
         // Activer ext_int4
         init_ext_intr();

         interrupt4Flag = 0;

}
void MCBSP_SPI_init(void)
{

// 1 - close l'ancien handle qui utilisait le mcbsp0 :
    MCBSP_close(DSK6713_AIC23_CONTROLHANDLE);

// 2 - Ouvre un nouveau handle sur le mcbsp0
    MySpiHandle = MCBSP_open(MCBSP_DEV0, MCBSP_OPEN_RESET);

// 3 - Set le registre MCBSP0SEL à 1 pour spécifier une offboard (daugthercard)
    Uint8 configActuelle = DSK6713_rget(DSK6713_MISC);
    Uint8 nouvelleConfig = configActuelle|0x01;
    DSK6713_rset(DSK6713_MISC,nouvelleConfig); // DSK6713_rset(Int16 regnum, Uint8 regval);

// 4 - config
    MCBSP_config(MySpiHandle,&MCBSP_SPI_Config);//MCBSP_config(MCBSP_Handle hMcbsp, MCBSP_Config *config);

// 5 - start

    MCBSP_start(MySpiHandle, MCBSP_RCV_START | MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,  0x00000200);



    return;
}

void SPI_WRITE_DATA(char dataToWrite)
{
    // Initialisation d'une variable pour recevoir le résultat de la conversion du charactère en 32 bits
    int result;

    // Résultat du charactère placé sur 32 bits, paddé avec des zéros à gauche.
    result = (int)dataToWrite&0x000000FF;   // On ne garde que les 8 bits, mais on les place à la fin d'un 32 bits.

    // Masque avec un OR et la commande d'écriture
    result = SPI_WRITE|result;              // SPI_WRITE 0x00008000, on set le 1 pour l'écriture

    // On envoie notre commande et les bits à écrire en un seul coup.
    MCBSP_write(MySpiHandle,result);

    // On attend microsecondes
    while (!MCBSP_rrdy(MySpiHandle));
 //   while (!MCBSP_wrdy(MySpiHandle));
    // On fait une lecture bidon afin de libérer le buffer de lecture.

    result = MCBSP_read(MySpiHandle); // Dummy read pour vider le buffer;
}

// Fonction servant à lire les données
char SPI_READ_DATA()
{
    // Initialisation d'un charactère pour recevoir la donnée par le module SPI.
    char Data=0;

    // Envoie de la commande pour lire la donnée présente dans le buffer.
    MCBSP_write(MySpiHandle,SPI_READ);  // On envoie la commande pour lire SPI_READ : 0x00000000

    // On attend 10 microsecondes
    while (!MCBSP_rrdy(MySpiHandle));
  //  while (!MCBSP_wrdy(MySpiHandle));

    // On lit la donnée du buffer qui est automatiquement tranférée en un charactère à partir des 32 bits reçus.
    Data = MCBSP_read(MySpiHandle);

    return (char)0x000000FF&Data;
    // On retourne le résultat
    //return Data;
}



/****************************************************************************
	ISR :
****************************************************************************/

// Arrive lorsqu'une donnée est prête à être lue dans l'Uart.

interrupt void c_int4()
{
    // On met le flag de l'interruption 4 à 1 pour qu'elle puisse être traitée dans le main (Téléphone.c)
    interrupt4Flag = 1;

    // Réinitialisation de l'event Ext Int 4 :
    //IRQ_clear(IRQ_EVT_EXTINT4);
}

void init_ext_intr()
{


    // CSL CHAPTER 11

    CSL_init();
    // On créer la handle pour le GPIO
    My_GPIO = GPIO_open(GPIO_DEV0, GPIO_OPEN_RESET); // open GPIO
    // reset du GPIO
    GPIO_reset(My_GPIO);


    //Activation de la sortie GP0
    //GPIO_pinEnable(My_GPIO, GPIO_PIN0);
    //GPIO_pinDirection(My_GPIO,GPIO_PIN0, GPIO_OUTPUT);

    //Met la sortie a 0 pour activer le buffer U2A sur le PCB de projet
    //GPIO_write(My_GPIO,GPIO_PIN0,0);



    // Enable la Pin 4
    GPIO_pinEnable(My_GPIO,GPIO_PIN4);   // Enable GPIO 4
    // choix de I/O
    GPIO_pinDirection(My_GPIO, GPIO_PIN4, GPIO_INPUT); // direction
    // choix de la polarité
    GPIO_intPolarity(My_GPIO,GPIO_GPINT4,GPIO_FALLING);

    GPIO_pinEnable(My_GPIO,GPIO_PIN6);   // Enable GPIO 6 pour led
    // choix de I/O
    GPIO_pinDirection(My_GPIO, GPIO_PIN6, GPIO_OUTPUT); // direction


  // CONFIG IRQ

    IRQ_setVecs(vectors);
        IRQ_set(IRQ_EVT_EXTINT4);
        // On enable les interruptions en général
        IRQ_globalEnable();
        // On enable l'event de l'interruption 4
        IRQ_enable(IRQ_EVT_EXTINT4);
        // On map l'event de l'interruption 4
        IRQ_map(IRQ_EVT_EXTINT4,4);
        // On enable les non maskable interrupts
        IRQ_nmiEnable();






// end of SPI_driver.c

}
