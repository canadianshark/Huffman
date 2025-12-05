#include <stdio.h>
#include <string.h>
#include "freq.h"
#include "heap.h"
#include "tree.h"
#include "huffmancodes.h"

int main(int argn, char* args[]){
    // ----Формат аргументов: Режим(encode/decode) *входной файл* *выходной файл* *второй выходной файл для проверки данных после кодирования(опционально)*

    if(argn < 4){
        printf("Invalid args, you should at least give mode,input and output");
        return 0;
    }

//---------------------------ENCODE----------------------------------------------------------
    if(strcmp(args[1], "encode") == 0){
      FILE* input = fopen(args[2], "rb");
      if(input == NULL){
          printf("Invalid input file, unable to open");
          return 0;
      }
      FILE* output = fopen(args[3], "wb");
      if(output == NULL){
          printf("Invalid output file, unable to open");
          return 0;
      }

      unsigned int frequencyTable[256] = {0};
      fill_freq_table(input, frequencyTable);

      unsigned int totalBytes = 0;
      unsigned int uniqueBytes = 0;

      printf("\n-------------------FREQUENCY_TABLE_INFO-------------------\n");

      for(int n = 0; n < 256; n++){
            if(frequencyTable[n] != 0){
                totalBytes += frequencyTable[n];
                uniqueBytes++;
                printf("Byte: %d - freq: %u \n", n, frequencyTable[n] );
            }
      }
      printf("Total unique bytes: %u\n", uniqueBytes);

      printf("-------------------HEAP_INFO-------------------\n");

      MinHeap* heap = min_heap_build(frequencyTable);
      for(int n = 0; n < heap->size; n++){
            printf("|b:%d : f:%u| ", heap->nodes[n]->byte, heap->nodes[n]->freq);
      }

      printf("\n-------------------TREE_INFO-------------------\n");

      Node* treeRoot = create_tree(heap);
      print_tree(treeRoot);

      printf("\n-------------------CODES_INFO-------------------\n");

        HuffmanCode codes[256];
        for(int n = 0; n <256; n++){
            codes[n].code= 0;
            codes[n].length = 0;
        }
        create_codes_from_tree(treeRoot,codes, 0 ,0 );
        int code_count = 0;
        for (int i = 0; i < 256; i++) {
            if (codes[i].length > 0) {
                code_count++;
                printf("Code for byte %d (0x%02X): ", i, i);
                for (int bit = codes[i].length - 1; bit >= 0; bit--)
                {
                    printf("%d", (codes[i].code >> bit) & 1);
                }
                printf(" (length=%d, decimal=%u)\n", codes[i].length, codes[i].code);
            }
        }
        printf("Total codes generated: %d\n", code_count);

        encode(input,codes,frequencyTable,totalBytes,uniqueBytes, output);

        printf("ENCODED SUCCESSFULLY\n");

        fclose(input);
        fclose(output);


        if(argn>4){
            FILE* checkOut = fopen(args[4], "wb");
            if(checkOut == NULL){
                printf("Invalid check output file, unable to open");
                return 0;
            }
            output = fopen(args[3], "rb");
            decode(output,checkOut);
            printf("check is done");
            fclose(output);
            fclose(checkOut);
        }









    }






}
