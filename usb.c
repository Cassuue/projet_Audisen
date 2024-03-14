#include "define.h"
#include "frame.h"
#include <windows.h>
#include "ftd2xx.h"
#include "usb.h"

//https://www.ftdichip.com/Support/Knowledgebase/index.html?ftd2xx_h.htm

//ouvrir -> FT_Open
//vérifier statut port USB -> FT_STATUS -> ok : FT_OK
//niveau de base de la ligne est 1, le bit de start est donc un 0
//Baud à 9600 pr la carte STM32 -> FT_SetBaudRate : FT_BAUD_9600
//8 bits de données -> FT_BITS_8
//elle n’utilise pas de « flow control » -> FT_FLOW_NONE
//pas de contrôle de la parité -> FT_PARITY_NONE
//stop bit de longueur 1 -> FT_STOP_BITS_1
//fermer port USB -> FT_Close
//ecrire -> FT_Write


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    //Verifier si le port USB s'ouvre
    if(FT_Open(0,&ftHandle) != FT_OK){
        printf("Impossible d'ouvrir le port USB");
        return NULL;
    }

    //Configuration du rythme
    if(FT_SetBaudRate(ftHandle,FT_BAUD_9600) != FT_OK){
        printf("Impossible de configurer le rythme (baud)");
        closeUSB(ftHandle);
        return NULL;
    }

    //ftStatus = FT_SetDataCharacteristics(ftHandle,FT_BITS_8,FT_STOP_BITS_1,FT_PARITY_NONE);
    if(FT_SetDataCharacteristics(ftHandle,FT_BITS_8,FT_STOP_BITS_1,FT_PARITY_NONE) != FT_OK){
        printf("Impossible de configurer les caractéristiques");
        closeUSB(ftHandle);
        return NULL;
    }

    //ftStatus = FT_SetFlowControl(ftHandle,FT_FLOW_NONE,0,0);
    if(FT_SetFlowControl(ftHandle,FT_FLOW_NONE,0,0) != FT_OK){
        printf("Impossible de configurer le flow de controle");
        closeUSB(ftHandle);
        return NULL;
    }

    printf("Initialiser");
    return ftHandle;
}

void closeUSB(FT_HANDLE ftHandle){
    if (ftHandle != NULL) {
        FT_Close(ftHandle);
        printf("Fermer");
    }
}

void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_STATUS ftStatus;
    DWORD nbrBitEcrit;
    ftStatus = FT_Write(ftHandle,frame,sizeof(frame),&nbrBitEcrit);

    if(ftStatus == FT_OK){
        printf("Trame écrite avec succès");
    }
    else{
        printf("Erreur trame non écrite");
    }
}