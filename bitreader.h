#pragma once
#include <stdio.h>

typedef struct {
    FILE* file;
    unsigned char buffer;
    int bit_count;
    int eof_flag;
} BitReader;

void bit_reader_init(BitReader* reader, FILE* file);

int bit_reader_read_bit(BitReader* reader);

unsigned int bit_reader_read_bits(BitReader* reader, int count);
