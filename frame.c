#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "frame.h"
#include "define.h"


void createInitFrame(s_song mySong, char* frame){
	char var[5];
    char data[50];
    //Réinitialise les chars pour qu'ils soient vide
    strcpy(frame,"");
    strcpy(data, "");

    strcat(frame,"#");

    //Récupère les valeurs entre le # et * pour la checksum
    strcat(data,mySong.title);
    strcat(data,",");
    sprintf(var,"%d",mySong.tpm);
    strcat(data,var);
    strcat(data,",");
    sprintf(var,"%d",mySong.nTicks);
    strcat(data,var);

    //Calcul la checksum
    int sum = checksum(data);
    sprintf(var,"%02x",sum);

    //Recupère le char data et l'ajoute à frame
    strcat(frame,data);
    strcat(frame,"*");
    strcat(frame,var);
    strcat(frame,"\r\n");
}

int checksum(char data[]){
    int val = (int)data[0];
    int i;
    int len = strlen(data);
    for(i=1; i<len; i++){
        val = val ^ (int)data[i];
    }
    return val;
}

void createTickFrame(s_tick myTick, char* frame){
    char varT[5];
    char dataT[50];
    //Réinitialise les chars pour qu'ils soient vide
    strcpy(frame,"");
    strcpy(dataT, "");

    strcat(frame,"#");

    //Récupère les valeurs entre le # et * pour la checksum
    //mode ?
    strcat(dataT,"0");
    strcat(dataT,",");
    sprintf(varT,"%d",myTick.accent);
    strcat(dataT,varT);
    strcat(dataT,",");

    // Ajout de la note au frame
    for(int i = 0; i<4; i++){
        if(myTick.note[i] != 0){
            sprintf(varT,"%d",myTick.note[i]);
            strcat(dataT,varT);
        }
        else{
            strcat(dataT,"00");
        }
        if(i != 3){
            strcat(dataT,",");
        }
    }

    //Calcul la checksum
    int sum = checksum(dataT);
    sprintf(varT,"%02x",sum);

    //Recupère le char data et l'ajoute à frame
    strcat(frame,dataT);
    strcat( frame,"*");
    strcat(frame,varT);
    strcat(frame,"*");
    strcat(frame,"\r\n");
}
