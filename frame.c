#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "frame.h"
#include "define.h"


void createInitFrame(s_song mySong, char* frame){
	char var[5];
    char data[50];
    strcpy(frame,"");
    strcpy(data, "");

    strcat(frame,"#");

    strcat(data,mySong.title);
    strcat(data,",");
    sprintf(var,"%d",mySong.tpm);
    strcat(data,var);
    strcat(data,",");
    sprintf(var,"%d",mySong.nTicks);
    strcat(data,var);

    int sum = checksum(data);
    sprintf(var,"%02x",sum);

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
    strcpy(frame,"");
    strcpy(dataT, "");

    strcat(frame,"#");

    //mode ?
    strcat(dataT,"0");
    strcat(dataT,",");

    sprintf(varT,"%d",myTick.accent);
    strcat(dataT,varT);
    strcat(dataT,",");

    if(myTick.note[0] != 0){
        sprintf(varT,"%d",myTick.note[0]);
        strcat(dataT,varT);
    }
    else{
        strcat(dataT,"00");
    }
    strcat(dataT,",");

    if(myTick.note[1] != 0){
        sprintf(varT,"%d",myTick.note[1]);
        strcat(dataT,varT);
    }
    else{
        strcat(dataT,"00");
    }
    strcat(dataT,",");

    if(myTick.note[2] != 0){
        sprintf(varT,"%d",myTick.note[2]);
        strcat(dataT,varT);
    }
    else{
        strcat(dataT,"00");
    }
    strcat(dataT,",");

    if(myTick.note[3] != 0){
        sprintf(varT,"%d",myTick.note[3]);
        strcat(dataT,varT);
    }
    else{
        strcat(dataT,"00");
    }

    int sum = checksum(dataT);
    sprintf(varT,"%02x",sum);

    strcat(frame,dataT);
    strcat( frame,"*");
    strcat(frame,varT);
    strcat(frame,"*");
    strcat(frame,"\r\n");
}
