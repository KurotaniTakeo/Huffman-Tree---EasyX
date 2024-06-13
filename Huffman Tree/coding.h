#ifndef CODING_H
#define CODING_H

#include <cstring>
#include "huffman.h"

typedef char** HuffmanCode;

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int n);

void Encode(HuffmanTree& HT, HuffmanCode& HC, char* plaintext, char* ciphertext, int n);

void Decode(HuffmanTree& HT, char* ciphertext, char* plaintext, int n);

#endif