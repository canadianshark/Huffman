#pragma once
#include <stdio.h>
#include <stdlib.h>


void fill_freq_table(const char* filename, unsigned int* freq);


struct Node* build_node_arr(unsigned int* freq);