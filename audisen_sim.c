#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"

void audisen_sim();

void audisen_sim(){
    FILE* pf = initAMP("fichiers_musique/Playlist.amp");
    char initFrame[INIT_FRAME_MAX_SIZE]= "";
    s_song mySong;
    char tickFrame[TICK_FRAME_SIZE]="";
    s_tick myTick;
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    while(!feof(pf)){
        readAMP(pf,song_filename);
        if(fopen(song_filename,"r") == NULL){
            fclose(song_filename);
            char* song_filename_txt;
            strcpy(song_filename_txt,song_filename); //voir comment enlever .ams
            int i;
            for(i=0; i<4; i++){
                song_filename_txt[strlen(song_filename_txt)-1] = '\0';
            }
            strcat(song_filename_txt,".txt");
            createAMS(song_filename_txt,song_filename);
            //printf("txt : %s\n", song_filename_txt);
            //printf("ams : %s\n", song_filename);
        }
        readAMS(song_filename);
        createInitFrame(mySong,initFrame);

        createTickFrame(myTick,tickFrame);

    }
}
