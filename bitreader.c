#include "bitreader.h"

void bit_reader_init(BitReader* reader, FILE* file) {
    reader->file = file;
    reader->buffer = 0;
    reader->bit_count = 0;
    reader->eof_flag = 0;
}

int bit_reader_read_bit(BitReader* reader) {
    if (reader->eof_flag) return -1;

    // Если буфер пуст, читаем новый байт
    if (reader->bit_count == 0) {
        int byte = fgetc(reader->file);
        if (byte == EOF) {
            reader->eof_flag = 1;
            return -1;
        }
        reader->buffer = (unsigned char)byte;
        reader->bit_count = 8;
    }


    reader->bit_count--;
    int bit = (reader->buffer >> reader->bit_count) & 1;

    return bit;
}

unsigned int bit_reader_read_bits(BitReader* reader, int count) {
    unsigned int result = 0;
    for (int i = 0; i < count; i++) {
        int bit = bit_reader_read_bit(reader);
        if (bit == -1) break;
        result = (result << 1) | bit;
    }
    return result;
}