
#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	
	s_song mySong;

    // Ouverture du fichier
    FILE * pf = NULL;
    pf = fopen(fileName, "r");

    if(pf == NULL){
        printf("Erreur dans l'ouverture du fichier");
        int note[4] = {0,0,0,0};
        s_tick tick_error = createTick(0, note);
        s_tick tab_tick_error[1];
        tab_tick_error[0] = tick_error;
        mySong = createSong(0,0," ", tab_tick_error);
    }
    else{

        printf("Fichier ouvert");
        // On récupère le titre du morceau
        char title[MAX_SIZE_TITLE];
        fgets(title, MAX_SIZE_TITLE, pf);

        // On récupère le tempo que l'on convertit en tick par minute
        char bpm[3]; // 1 bpm = 2 tpm
        int tpm;
        fgets(bpm, 3, pf);
        tpm = atoi(bpm)*2;

        // On se déplace dans le fichier pour arriver à la partition
        char line[MAX_SIZE_LINE];

        fseek(pf, 4, SEEK_CUR);
        fgets(line, MAX_SIZE_LINE, pf);

        // On analyse chaque ligne pour récupérer les notes

        s_tick tab_ticks[MAX_NUMBER_TICKS];
        int nb_tick = 0;

        while(fgets(line, MAX_SIZE_LINE, pf) != NULL){
            int num_note = 0;

            int ind = 0;
            int notes[ind];
            int accent = 0;

            int taille = strlen(line);

            // On récupère les notes pour les ticks
            for(int i = 4; i<taille ; i+=3){
                num_note ++;
                if(line[i] == '^' || line[i]== 'x'){
                    if(ind == 0 && line[i] == '^'){
                        accent = 1;
                    }
                    notes[ind] = num_note;
                    ind++;
                }
            }
            if (ind != 4){
                notes[ind] = 0;
            }

            // Création d'un tick et ajout à la liste de tick du morceau
            s_tick t = createTick(accent, notes);
            tab_ticks[nb_tick] = t;
            nb_tick++;
        }

        // Création du morceau
        mySong = createSong(tpm, nb_tick, title, tab_ticks);
    }

    fclose(pf);
    return mySong;
}

s_tick createTick(int accent, int note[4]){
    s_tick t;
    t.accent = accent;
    for (int i=0; i<4; i++){
        t.note[i] = note[i];
    };
    return t;
}

s_song createSong(int tpm, int nTicks, char title[MAX_SIZE_TITLE], s_tick tickTab[MAX_NUMBER_TICKS]){
    s_song s;
    s.tpm = tpm;
    s.nTicks = nTicks;
    strcpy(s.title, title);

    for(int i =0; i<MAX_NUMBER_TICKS; i++){
        s.tickTab[i] = tickTab[i];
    }
    return s;
}


void createAMS(char* txtFileName, char* amsFileName){


}