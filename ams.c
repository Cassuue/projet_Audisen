#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	
	s_song mySong;

    // Ouverture du fichier
    FILE * pf = NULL;
    pf = fopen(fileName, "r");

    if(pf == NULL){
        //printf("Erreur dans l'ouverture du fichier");
        int note[4] = {0,0,0,0};
        s_tick tick_error = createTick(0, note);
        s_tick tab_tick_error[1];
        tab_tick_error[0] = tick_error;
        mySong = createSong(0,0,"", tab_tick_error);
    }
    else{

        //printf("Fichier ouvert");
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
                    if(line[i] == '^'){
                        accent = 1;
                    }
                    notes[ind] = num_note;
                    ind++;
                }
            }
            if (ind != 3){
                for(int i = ind; i<4; i++){
                    notes[i] = 0;
                }
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

    // Ouverture du fichier txt
    FILE* filetxt;
    filetxt = fopen(txtFileName, "r");

    if(filetxt == NULL){
        printf("ERROR : impossible d'ouvrir le fichier TXT");
    }
    else{

        // Ouverture du fichier ams
        FILE * fileams;
        fileams = fopen(amsFileName, "w+");

        if(fileams == NULL){
            printf("ERROR : impossible d'ouvrir le fichier AMS");
        }
        else{

            // On récupère le titre puis on l'écrit dans le fichier ams
            char title[MAX_SIZE_TITLE];
            fgets(title, MAX_SIZE_TITLE, filetxt);

            fputs(title, fileams);

            // On récupère le tempo puis on l'écrit dans le fichier ams
            char bpm[3];
            fgets(bpm, 3, filetxt);

            fputs(bpm, fileams);

            // On récupère les informations des autres lignes
            char line[MAX_SIZE_LINE];
            fseek(filetxt, 4, SEEK_CUR);

            // Ajout de la première ligne avec les numéros de notes
            fputs("\n\n", fileams);
            fprintf(fileams, "    ");
            for(int i = 1; i<61; i++){
                fprintf(fileams, "%02d ", i);
            }

            int nb_tick = 1;

            // Tableau de conversion pour les notes
            char tab_notes[61][4] = {"","C1", "C1#", "D1", "D1#", "E1", "F1", "F1#", "G1", "G1#", "A1", "A1#", "B1", "C2",
                                     "C2#","D2", "D2#", "E2", "F2", "F2#", "G2", "G2#", "A2", "A2#", "B2", "C3", "C3#",
                                     "D3", "D3#", "E3", "F3", "F3#", "G3", "G3#", "A3", "A3#", "B3", "C4", "C4#", "D4",
                                     "D4#", "E4", "F4", "F4#", "G4", "G4#", "A4", "A4#", "B4", "C5", "C5#", "D5", "D5#",
                                     "E5", "F5", "F5#", "G5", "G5#", "A5", "A5#", "B5"};

            int notes_tick[4][3] = {};

            while(fgets(line, MAX_SIZE_LINE, filetxt)){

                // On sépare la ligne selon les virgules
                char* info_note = strtok(line, ",");

                while (info_note != NULL){

                    char note[strlen(info_note)-1];

                    // On supprime les sauts à la ligne
                    if(info_note[strlen(info_note)-1] == '\n'){
                        strcpy(note, info_note);
                        note[strlen(note)-1]='\0';
                    }else{
                        strcpy(note, info_note);
                    }

                    // On détermine le temps de la note
                    int temps = 0;
                    switch (note[strlen(note)-1]) {
                        case 'R':
                            temps = 8;
                            break;
                        case 'B':
                            temps = 4;
                            break;
                        case 'N':
                            temps = 2;
                            break;
                        case 'C':
                            temps = 1;
                            break;
                        case 'D':
                            temps = 1;
                            break;
                    }

                    // On supprime les deux derniers caractères
                    note[strlen(note)-1] = '\0';
                    note[strlen(note)-1] = '\0';

                    // On récupère les caractères représentant la note
                    if (note[0] == ' '){
                        for(int i = 0; i < strlen(note)-1; i++){
                            note[i] = note[i+1];
                        }
                        note[strlen(note)-1] = '\0';
                    }

                    // On compare la note au tableau de conversion pour obtenir le numéro
                    int num_note;
                    for(int i = 0; i<61; i++){
                        if (strcmp(note, tab_notes[i]) == 0){
                            num_note = i;
                        }
                    }

                    // On ajoute la note au tableau contenant les notes de la tick
                    int test = 0;
                    for(int i = 0; i<4; i++){
                        if(notes_tick[i][0] == 0 && test == 0){
                            notes_tick[i][0] = num_note;
                            notes_tick[i][1] = temps;
                            notes_tick[i][2] = 1;
                            test = 1;
                        }
                    }

                    // On passe à la note suivante
                    info_note = strtok ( NULL, "," );
                }

                // Ecriture du numéro de tick dans le fichier .ams
                fprintf(fileams, "\n%03d|", nb_tick);

                // On remplit les ticks dans le fichier .ams
                for(int i = 1; i<61; i++){

                    // Variable permettant de savoir si on a déjà écrit une note ou pas
                    int test2 = 0;

                    for(int j = 0; j<4; j++){
                        // Test du numéro de la note
                        if(i == notes_tick[j][0]){
                            // Test du temps de la note
                            if(notes_tick[j][1] != 0){
                                // Test de l'accentuation
                                if(notes_tick[j][2] == 1){
                                    fprintf(fileams, "^ |");
                                    notes_tick[j][2] = 0;

                                } else {
                                    fprintf(fileams, "x |");
                                }

                                notes_tick[j][1]--;
                                test2 = 1;

                                // On enlève la note en la déclarant à 0 si le temps est à 0
                                if(notes_tick[j][1] == 0){
                                    notes_tick[j][0] = 0;
                                }

                            } else{
                                // On enlève la note en la déclarant à 0
                                notes_tick[j][0] = 0;
                            }
                        }
                    }

                    // Si on a pas de note, on met une case vide
                    if(test2 == 0){
                        fprintf(fileams, "  |");
                    }
                }
                nb_tick++;
            }
        }
        fclose(fileams);
    }
    fclose(filetxt);
}