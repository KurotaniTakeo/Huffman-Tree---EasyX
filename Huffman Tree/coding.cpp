#define _CRT_SECURE_NO_WARNINGS 1
#include "coding.h"

typedef char** HuffmanCode;

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
    HC = new char* [n + 1];
    char* cd = new char[n];
    cd[n - 1] = '\0';
    for (int i = 1; i <= n; ++i)
    {
        int start = n - 1;
        for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
        {
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], &cd[start]);
    }
    delete[] cd;
}

void Encode(HuffmanTree& HT, HuffmanCode& HC, char* plaintext, char* ciphertext, int n)
{
    int i = 0;
    while (plaintext[i] != '\0')
    {

        for (int j = 1; j <= n; j++)
        {
            if (HT[j].ch[0] == plaintext[i])
            {
                strcat(ciphertext, HC[j]);
                break;
            }
        }
        i++;
    }
}

void Decode(HuffmanTree& HT, char* ciphertext, char* plaintext, int n)
{
    int i = 0;
    int p = 2 * n - 1;
    while (ciphertext[i] != '\0')
    {
        if (ciphertext[i] == '0')
        {
            p = HT[p].lchild;
        }
        else if (ciphertext[i] == '1')
        {
            p = HT[p].rchild;
        }
        if (HT[p].lchild == 0 && HT[p].rchild == 0)
        {
            strcat(plaintext, HT[p].ch);
            p = 2 * n - 1;
        }
        i++;
    }
    plaintext[2 * MAX_STR_SIZE - 1] = '\0';
}