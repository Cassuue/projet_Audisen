#include "define.h"
#include "amp.h"


FILE* initAMP(char* filename){
    //Ouvre le fichier renvoie un pointeur vers le fichier si celui ci existe
    printf("All is good for the opening\n");
    return fopen(filename, "r");
}

void convert_lr(char* entree){
    int i;
    for(i=0;entree[i]!='\0';i++){
        if(entree[i]=='\r' || entree[i]=='\n'){
            entree[i]='\0';
        }
    }
}

void readAMP(FILE* pf, char* song_filename){
    char titre[MAX_SIZE_TITLE];
    if(fgets(titre,MAX_SIZE_TITLE,pf) != NULL) {
        convert_lr(titre);
        conversionName(titre);
        strcpy(song_filename, titre);
        printf("song_filename final : %s\n", song_filename);
    }
    else{
        song_filename = NULL;
        //printf("songname->NULL\n");
    }
}

void conversionName(char* titre){
    size_t longueur = strlen(titre);
    if(longueur > MAX_SIZE_TITLE){
        longueur = MAX_SIZE_TITLE;
    }
    //printf("Titre recupere entrant ds la fonction reconversion : %s\n",titre);

    //Remplacer les majuscules par des miniscules
    int i;
    for(i=0; i<longueur; i++){
        if(titre[i] >= 'A' && titre[i] <= 'Z'){
            titre[i] = titre[i] + 32;
        }
    }
    //printf("Titre sans les majuscules : %s\n",titre);

    //Remplacer les espaces... par les tirets
    int j;
    int it = 0;
    for(j=0; j<longueur; j++) {
        if (((titre[j] < 'a' || titre[j] > 'z') && (titre[j] < '0' || titre[j] > '9')) && titre[j]!='\0') {
            //Si le caractère précédent est déjà un tiret
            if(j>0){
                if (titre[j - 1] == '_') {
                    it++;
                    int k;
                    for (k = j; k < longueur ; k++) {
                        titre[k] = titre[k + 1];
                    }
                    j--;
                }
            }

            //Si le premier caractère est faux ne pas mettre de tiret
            if (j == 0) {
                it ++;
                int l;
                for (l = j; l < longueur - 1; l++) {
                    titre[l] = titre[l + 1];
                }
                j--;
            }

            if(it==0) {
                titre[j] = '_';
            }

            it = 0;
        }
    }
    printf("\n");

    //Ne pas avoir de tiret à la fin
    if(longueur>0 && titre[longueur-1]=='_'){
        titre[longueur-1] = '\0';
    }
    //printf("titre sans tout les caracteres non voulu : %s\n",titre);

    //Ajoute l'extension .ams
    strcat(titre,".ams");
}

void closeAMP(FILE* pf){
    if(pf != NULL){
        fclose(pf);
        printf("the file is close\n");
    }
}

void AMP(char* filename){
    FILE* pf = initAMP(filename);
    char* song_filename = malloc(MAX_SIZE_TITLE*sizeof(char));
    while(!feof(pf)){
        readAMP(pf,song_filename);
    }
    closeAMP(pf);
}


