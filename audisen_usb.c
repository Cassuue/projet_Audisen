#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"
#include <windows.h>


int main(){

    //Initialisation des fichiers et structures
    FILE* pf = initAMP("Playlist.amp");
    char initFrame[INIT_FRAME_MAX_SIZE]= "";
    s_song mySong;
    char tickFrame[TICK_FRAME_SIZE]="";
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    char* song_filename_txt = malloc(MAX_SIZE_TITLE*sizeof(char));

    //Initialise le port USB
    FT_HANDLE ftHandle = initUSB();
    if(ftHandle == NULL){
        return 0;
    }

    while(!feof(pf)){
        readAMP(pf,song_filename);

        //On vérifie si le fichierr ams existe sinon on le crée à partir du txt
        if(fopen(song_filename,"r") == NULL){
            strcpy(song_filename_txt,song_filename);
            for(int i=0; i<4; i++){
                song_filename_txt[strlen(song_filename_txt)-1] = '\0';
            }
            strcat(song_filename_txt,".txt");
            createAMS(song_filename_txt,song_filename);
        }

        //Remplit la structure de song, crée la trame initiale et ecrit en USB
        mySong = readAMS(song_filename);
        createInitFrame(mySong,initFrame);
        writeUSB(initFrame,ftHandle);

        //Ecrit la trame de tick en USB
        for(int i=0; i<mySong.nTicks; i++){
            createTickFrame(mySong.tickTab[i],tickFrame);
            writeUSB(tickFrame,ftHandle);
        }

        //Ajoute une pause de temps de 1s
        Sleep(1000);
    }
    closeAMP(pf);
    closeUSB(ftHandle);
}
