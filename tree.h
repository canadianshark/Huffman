#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct Node{
    unsigned char byte;
    unsigned int freq;
    struct Node* left;
    struct Node* right;

}Node;

struct Node* make_node(unsigned char byte, unsigned int freq);

struct Node* create_tree(MinHeap* heap);

void print_tree(Node* root, int depth);