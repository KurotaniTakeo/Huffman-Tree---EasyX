#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_STR_SIZE 512

#include <iostream>
using namespace std;

// The struct of the Huffman Tree
typedef struct
{
    int weight;
    int parent, lchild, rchild;
    char ch[2];
} HTNode, * HuffmanTree;

// Create the Huffman Tree
// n being the total of the leaf node
// w pointing to the integer array
void CreateHuffmanTree(HuffmanTree& HT, int* w, char* letter, int n);

// The select function, to pick out the least two weights from the tree.
void Select(HuffmanTree& HT, int pos, int& s1, int& s2);

#endif