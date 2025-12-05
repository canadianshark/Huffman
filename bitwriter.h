#include <stdio.h>

typedef struct {
    FILE* file;
    unsigned char buffer;  // Текущий накапливаемый байт
    int bit_count;         // Сколько бит уже в буфере (0-7)
} BitWriter;

void bit_writer_init(BitWriter* writer, FILE* file);
void bit_writer_write(BitWriter* writer, unsigned int code, int length);

void bit_writer_flush(BitWriter* writer);