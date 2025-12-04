#define _CRT_SECURE_NO_WARNINGS
#include "freq.h"

void fill_freq_table(const char* filename, unsigned int* freq){
    FILE* file = fopen(filename, "rb");
    if(file == NULL){
        return;
    }
    int byte;
    while((byte = fgetc(file)) != EOF){
        freq[byte]++;
    }
    fclose(file);
}


