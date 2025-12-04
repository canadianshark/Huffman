#include "tree.h"


struct Node* make_node(unsigned char byte, unsigned int freq){
    Node* newNode = malloc(sizeof(Node*));
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

void print_free(Node* root, int depth){
        if (root == NULL) return;

        // Отступы по уровню
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }

        if (depth > 0) {
            printf("└─ ");
        }

        // Вывод узла
        if (root->byte != 0) {
            printf("'%c': %u\n", root->byte, root->freq);
        } else {
            printf("[%u]\n", root->freq);
        }

        // Детские ноды
        print_tree(root->left, depth + 1);
        print_tree(root->right, depth + 1);





}

