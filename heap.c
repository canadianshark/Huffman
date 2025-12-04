#include "heap.h"
#include "tree.h"
#include "freq.h"



void min_heap_insert(MinHeap* heap, struct Node* node) {
    // +Место, есл все занято
    if (heap->size == heap->capacity) {
        heap->capacity++;
       heap->nodes = realloc(heap->nodes, heap->capacity * sizeof(Node*));
    }

    // Берем конец кучи чтобы оттуда просеять
    int i = heap->size;
    heap->size++;

    // Толкаем все вниз чтобы вставить в нужное место искомую ноду
    while (i > 0 && node->freq < heap->nodes[PARENT(i)]->freq) {
         heap->nodes[i] = heap->nodes[PARENT(i)];
         i = PARENT(i);
    }

    // Ставим ноду на место
    heap->nodes[i] = node;

}


void heapify(struct MinHeap* heap, int i){
    while (1) {
        int smallest = i;
        int left = LEFT_CHILD(i);
        int right = RIGHT_CHILD(i);

        // Сравниваем с правым ребенком
        if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq) {
            smallest = right;
        }

        // Сравниваем с левым ребенком
        if (left < heap->size && heap->nodes[left]->freq < heap->nodes[smallest]->freq) {
            smallest = left;
        }


        // Если детские ноды больше, то все, выходим
        if (smallest == i) {
            break;
        }

        // Меняем текущую ноду с самой маленькой из детских
        Node* temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;
        
        // А тут индекс меняем
        i = smallest;
    }
}


Node* min_heap_extract(MinHeap* heap){
  if(heap->size == 0){
      return NULL;
  }

  Node* extracted = extracted =heap->nodes[0];
  heap->nodes[0] = heap->nodes[heap->size - 1];

  heap->nodes[heap->size - 1] = NULL;
  heap->size--;
  heapify(heap, 0);

  return extracted;
}


MinHeap* min_heap_build(unsigned int* freq){
    //Сначала собираем массив нод
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = 0;
    for(int n = 0; n < 256; n++){
        if(freq[n] != 0){
            min_heap_insert(heap, make_node(n,freq[n]));
        }
    }

    return heap;
}



void min_heap_free(MinHeap* heap){
    for(int n = 0; n <= heap->size; n++){
        free(heap->nodes[n]);
    }
    free(heap->nodes);
}
