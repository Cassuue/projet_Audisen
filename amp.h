#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void conversionName(char* titre);

void closeAMP(FILE* pf);

void convert_lr(char* entree);

void AMP(char* filename);

#endif //AUDISEN2024_AMP_H
