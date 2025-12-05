#define _CRT_SECURE_NO_WARNINGS
#include "freq.h"

void fill_freq_table(FILE* file, unsigned int* freq){
    if(file == NULL){
        return;
    }
    int byte;
    while((byte = fgetc(file)) != EOF){
        freq[byte]++;
    }
    fclose(file);
}


