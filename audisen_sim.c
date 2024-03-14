#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
//#include "usb.h"

int main(){
    FILE* pf = initAMP("Playlist.amp");
    char initFrame[INIT_FRAME_MAX_SIZE]= "";
    s_song mySong;
    char tickFrame[TICK_FRAME_SIZE]="";
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    char* song_filename_txt = malloc(MAX_SIZE_TITLE*sizeof(char));

    FILE* filefrm;
    filefrm = fopen("fileSimulation.frm", "wb");

    if(filefrm == NULL){
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return 0;
    }
    printf("File open \n");

    while(!feof(pf)){
        readAMP(pf,song_filename);
        printf(song_filename);

        if(fopen(song_filename,"r") == NULL){
            strcpy(song_filename_txt,song_filename);
            for(int i=0; i<4; i++){
                song_filename_txt[strlen(song_filename_txt)-1] = '\0';
            }
            strcat(song_filename_txt,".txt");
            createAMS(song_filename_txt,song_filename);
        }
        mySong = readAMS(song_filename);
        createInitFrame(mySong,initFrame);
        fputs(initFrame, filefrm);

        // Ajouter la frame de tick au fichier .frm
        for(int i=0; i<mySong.nTicks; i++){
            createTickFrame(mySong.tickTab[i],tickFrame);
            // Ajouter la tick au fichier .frm
            fputs(tickFrame, filefrm);
        }
    }
    fclose(filefrm);
    return 0;

}
