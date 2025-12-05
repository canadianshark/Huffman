#pragma once
#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Code{
    unsigned int code;
    unsigned char length;
} HuffmanCode;

void create_codes_from_tree(Node* root, HuffmanCode* CodeTable, unsigned int curCode, int depth);


void write_code_bytes(FILE* file, unsigned int code, int length);


void write_header(FILE* file, unsigned int* freq,unsigned int original_size, unsigned int bytes);

void read_header(FILE* file, unsigned int* freqTable,unsigned int* original_size);

void encode(FILE* input, HuffmanCode* codes , unsigned int* freq, unsigned int original_size, unsigned int bytes,  FILE* output);

void decode(FILE* input, FILE* output);
