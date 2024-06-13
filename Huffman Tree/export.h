#ifndef EXPORT_H
#define EXPORT_H

#include "huffman.h"
#include <fstream>

void PreOrderSave(HuffmanTree HT, int root, std::ofstream& outfile);
void SaveHuffmanTreeToFile(HuffmanTree HT, int totalNodes, const char* filename);
#endif