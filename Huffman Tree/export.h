#ifndef EXPORT_H
#define EXPORT_H

#include "huffman.h"
#include <fstream>

void SaveHuffmanTreeToFile(HuffmanTree HT, int totalNodes, const char* filename);
#endif