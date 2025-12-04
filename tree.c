#include "tree.h"
#include "heap.h"


struct Node* make_node(unsigned char byte, unsigned int freq){
    Node* newNode = malloc(sizeof(Node));
    newNode->byte = byte;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* create_tree(MinHeap* heap){
    if (heap == NULL || heap->size == 0) {
        return NULL;
    }

    while(heap->size > 1){
        Node* left = min_heap_extract(heap);
        Node* right = min_heap_extract(heap);

        Node* parent = make_node(0, left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        min_heap_insert(heap, parent);
    }
    return min_heap_extract(heap);
}

void print_tree(Node* root){

        if (root == NULL) return;

        if (root->left == NULL && root->right == NULL) {
            printf("Leaf: freq=%u, byte=0x%02X\n", root->freq, root->byte);
        } else {
            printf("Internal: freq=%u\n", root->freq);
            print_tree(root->left);
            print_tree(root->right);
        }

}

