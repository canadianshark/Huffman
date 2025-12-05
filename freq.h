#pragma once
#include <stdio.h>
#include <stdlib.h>


void fill_freq_table(FILE* file, unsigned int* freq);


struct Node* build_node_arr(unsigned int* freq);