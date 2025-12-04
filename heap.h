#pragma once
#include <stdlib.h>

typedef struct Node Node;

typedef struct MinHeap{
    Node** nodes;
    int size;
    int capacity;
}MinHeap;

//-----Макросы для индексов кучи-----------------------------------
#define LEFT_CHILD(i) ((2 * (i)) + 1)
#define RIGHT_CHILD(i) ((2 * (i)) + 2)
#define PARENT(i) (((i) - 1) / 2)
//------------------------------------------------------------------


void min_heap_insert(MinHeap* heap, struct Node* node);

struct Node* min_heap_extract(MinHeap* heap);

void min_heap_heapify(struct MinHeap* heap, int i);

MinHeap* min_heap_build(unsigned int* freq);

void min_heap_free(MinHeap* heap);