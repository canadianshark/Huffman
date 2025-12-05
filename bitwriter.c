#include "bitwriter.h"

void bit_writer_init(BitWriter* writer, FILE* file) {
    writer->file = file;
    writer->buffer = 0;
    writer->bit_count = 0;
}

void bit_writer_write(BitWriter* writer, unsigned int code, int length) {
    // Добавляем биты кода в буфер
    for (int i = length - 1; i >= 0; i--) {
        // Бит из кода (старший бит сначала)
        int bit = (code >> i) & 1;

        // Добавляем в буфер
        writer->buffer = (writer->buffer << 1) | bit;
        writer->bit_count++;

        // Если буфер заполнен (8 бит) - записываем
        if (writer->bit_count == 8) {
            fputc(writer->buffer, writer->file);
            writer->buffer = 0;
            writer->bit_count = 0;
        }
    }
}

void bit_writer_flush(BitWriter* writer) {
    if (writer->bit_count > 0) {
        // Дополняем нулями справа и записываем
        writer->buffer = writer->buffer << (8 - writer->bit_count);
        fputc(writer->buffer, writer->file);
        writer->buffer = 0;
        writer->bit_count = 0;
    }
}