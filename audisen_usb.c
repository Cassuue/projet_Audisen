#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"
#include <windows.h>


int main(){
    FILE* pf = initAMP("fichiers_musique/Playlist.amp");
    char initFrame[INIT_FRAME_MAX_SIZE]= "";
    s_song mySong;
    char tickFrame[TICK_FRAME_SIZE]="";
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    char* song_filename_txt = malloc(MAX_SIZE_TITLE*sizeof(char));

    FT_HANDLE ftHandle = initUSB();
    if(ftHandle == NULL){
        return 0;
    }

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
        writeUSB(initFrame,ftHandle);

        for(int i=0; i<mySong.nTicks; i++){
            createTickFrame(mySong.tickTab[i],tickFrame);
            writeUSB(tickFrame,ftHandle);
        }
        Sleep(1);
    }
    closeAMP(pf);
    closeUSB(ftHandle);
}
