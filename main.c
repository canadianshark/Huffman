#include <stdio.h>
#include "freq.h"
#include "heap.h"
#include "tree.h"

int main(void) {
  unsigned int frequencyTable[256] = {0};
  char filename[1024] = "trial.txt";
  fill_freq_table(filename, frequencyTable);
  int bytes = 0;
  for(int n = 0; n < 256; n++){
    if(frequencyTable[n] != 0){
      bytes++;
      printf("Byte: %d - freq: %u \n", n, frequencyTable[n] );
    }
  }
  printf("\n--------------------------------HEAP_TEST-------------------------------------------------\n");
  MinHeap* heap = min_heap_build(frequencyTable);
  for(int n = 0; n < heap->size; n++){
    printf("|b:%d : f:%u| ", heap->nodes[n]->byte, heap->nodes[n]->freq);
  }
  printf("\n--------------------------------TREE_TEST-------------------------------------------------\n");
  Node* treeRoot = create_tree(heap);
  print_tree(treeRoot);








}
