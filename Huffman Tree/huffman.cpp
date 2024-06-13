#include "huffman.h"

void CreateHuffmanTree(HuffmanTree& HT, int* w, char* letter, int n)
{
    if (n <= 1)
        return;
    int m = 2 * n - 1;      // The total number of nodes of the tree
    HT = new HTNode[m + 1]; // Empty position of 0 in the array

    // Add the leaf nodes to the tree
    for (int i = 1; i <= n; ++i)
    {
        HT[i].weight = w[i - 1];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].ch[0] = letter[i - 1]; // Setting the value of a character
        HT[i].ch[2] = '\0';          // Add '\0'
    }
    
    // Init the rest of the nodes
    for (int i = n + 1; i <= m; ++i)
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].ch[0] = '\0'; // Character field for non-leaf nodes set to '\0'
    }

    // Create the Tree Structure
    for (int i = n + 1; i <= m; ++i)
    {
        int s1 = 0, s2 = 0;
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

// The select function, to pick out the least two weights from the tree.
void Select(HuffmanTree& HT, int pos, int& s1, int& s2)
{
    int i;
    for (i = 1; i <= pos; ++i)
    {
        if (HT[i].parent == 0)
        {
            s1 = i;
            break;
        }
    }
    for (i = i + 1; i <= pos; ++i)
    {
        if (HT[i].parent == 0)
        {
            s2 = i;
            break;
        }
    }
    if (HT[s1].weight > HT[s2].weight)
    {
        int temp = s1;
        s1 = s2;
        s2 = temp;
    }

    // Find two nodes with minimum weight and no parent node
    for (int i = 1; i <= pos; ++i)
    {
        if (HT[i].parent == 0)
        {
            if (HT[i].weight < HT[s1].weight)
            {
                s2 = s1;
                s1 = i;
            }
            else if (HT[i].weight < HT[s2].weight && i != s1)
            {
                s2 = i;
            }
        }
    }
}