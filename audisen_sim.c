#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
//#include "usb.h"

int main(){

    //Initialisation des fichiers et structures
    FILE* pf = initAMP("Playlist.amp");
    char initFrame[INIT_FRAME_MAX_SIZE]= "";
    s_song mySong;
    char tickFrame[TICK_FRAME_SIZE]="";
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    char* song_filename_txt = malloc(MAX_SIZE_TITLE*sizeof(char));

    //Création du fichier .frm
    FILE* filefrm;
    filefrm = fopen("fileSimulation.frm", "wb");

    if(filefrm == NULL){
        printf("Erreur : impossible d'ouvrir le fichier\n");
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

        //Remplit la structure de song, crée la trame initiale et l'ajoute dans le fichier .frm
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
