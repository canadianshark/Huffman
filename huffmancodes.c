#include "huffmancodes.h"
#include "bitwriter.h"
#include "bitreader.h"
#include "heap.h"
#include "tree.h"
#include <ctype.h>



void create_codes_from_tree(Node* root, HuffmanCode* CodeTable, unsigned int curCode, int depth){
    if(root == NULL){ return;}

    if(root->left == NULL && root->right == NULL){
        CodeTable[root->byte].code = curCode;
        CodeTable[root->byte].length = (depth == 0) ? 1 : depth;
    }
    if (root->left != NULL) {
        create_codes_from_tree(root->left, CodeTable, curCode << 1, depth+1);
    }

    if (root->right != NULL) {
        create_codes_from_tree(root->right, CodeTable, curCode << 1 | 1, depth+1);
    }



}



 /*Метаданные:
 * В файле есть заголовок который хранит таблицу кодов
 * Формат:
 * количество байтов в оригинальном файле (первые 4 байта) записано это дело с младшего байта
 * количество уникальных байтов (первые 4 байта) также с младшего
 * Дальше сами байты и частота
 */


void write_header(FILE* file, unsigned int* freq,unsigned int original_size, unsigned int bytes){
    if (file == NULL || freq == NULL){return;}



    // Записываем размер и количество

    fputc(original_size & 0xFF, file);         // Младший байт
    fputc((original_size >> 8) & 0xFF, file);  // Следующий
    fputc((original_size >> 16) & 0xFF, file); // Ещё
    fputc((original_size >> 24) & 0xFF, file); // Старший байт


    fputc(bytes & 0xFF, file);
    fputc((bytes >> 8) & 0xFF, file);
    fputc((bytes >> 16) & 0xFF, file);
    fputc((bytes >> 24) & 0xFF, file);

     for (int i = 0; i < 256; i++) {
         if (freq[i] > 0) {
             // Символ (1 байт)
             fputc(i, file);

             // Частота (4 байта, little-endian)
             unsigned int ByteFreq = freq[i];
             for (int j = 0; j < 4; j++) {
                 fputc(ByteFreq & 0xFF, file);
                 ByteFreq>>= 8;
             }
         }
     }
}

void read_header(FILE* file, unsigned int* freqTable,unsigned int* original_size) {
    // Читаем original_size
    *original_size = 0;
    fread(original_size,4,1,file);

    // Читаем symbol_count
    unsigned int symbol_count = 0;
    fread(&symbol_count,4,1,file);


    // Читаем таблицу частот
    for (unsigned int i = 0; i < symbol_count; i++) {
        // Символ
        unsigned char symbol = fgetc(file);

        // Читаем Частоту
        unsigned int freq = 0;
        fread(&freq,4,1,file);




        freqTable[symbol] = freq;
    }


}




void encode(FILE* input, HuffmanCode* codes , unsigned int* freq, unsigned int original_size, unsigned int bytes,  FILE* output){

    write_header(output, freq, original_size, bytes);


    BitWriter writer;
    bit_writer_init(&writer, output);


    int byte;
    while ((byte = fgetc(input)) != EOF) {
        HuffmanCode code = codes[byte];
        bit_writer_write(&writer, code.code, code.length);
    }


    bit_writer_flush(&writer);
}


void decode(FILE* input, FILE* output){
    rewind(input);
    // Читаем таблицу частот из заголовка
    unsigned int frequencyTable[256] = {0};
    unsigned int original_size = 0;
    read_header(input,frequencyTable,&original_size);



    //Создаем кучу и строим обратно дерево
    MinHeap* heap = min_heap_build(frequencyTable);
    if(!heap) {
        printf("ERROR: Failed to build heap\n");
        return;
    }

    Node* TreeRoot = create_tree(heap);
    if(!TreeRoot) {
        printf("ERROR: Failed to create tree\n");
        return;
    }


    if(TreeRoot->left == NULL && TreeRoot->right == NULL){
        printf("DEBUG decode: Single symbol tree\n");
        for(unsigned int i = 0; i < original_size; i++) {
            fputc(TreeRoot->byte, output);
        }
        free_tree(TreeRoot);
        min_heap_free(heap);
        return;
    }


    BitReader reader;
    bit_reader_init(&reader, input);

    Node* TreePtr = TreeRoot;
    unsigned int decoded_count = 0;
    int current_length = 0;


    while (decoded_count < original_size) {
        // Читаем следующий бит
        int bit = bit_reader_read_bit(&reader);
        if (bit == -1){
            printf("ERROR: Unexpected EOF at %u/%u symbols\n", decoded_count, original_size);
            break;
        }

        if(bit == 1){
            if(!TreePtr->right) {
                printf("ERROR: TreePtr->right is NULL!\n");
                break;
            }
            TreePtr = TreePtr->right;
            current_length++;
        }
        if(bit == 0){
            if(!TreePtr->left) {
                printf("ERROR: TreePtr->left is NULL!\n");
                break;
            }
            TreePtr = TreePtr->left;
            current_length++;
        }

        if(TreePtr->left == NULL && TreePtr->right == NULL && current_length != 0){
            fputc(TreePtr->byte, output);
            decoded_count++;
            current_length = 0;
            TreePtr = TreeRoot;
        }

    }
    printf("DEBUG decode: Finished, decoded %u/%u symbols\n",
           decoded_count, original_size);
    free_tree(TreeRoot);
}

