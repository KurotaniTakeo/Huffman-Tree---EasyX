#define _CRT_SECURE_NO_WARNINGS 1
#include "huffman.h"
#include "import.h"
#include "export.h"
#include "coding.h"
#include "GUI.h"
#include <stdlib.h>  
#include <windows.h> 

int main(int argc, char* argv[])
{
	if (argc < 2) {
		MessageBox(NULL, ConvertCharToLPCWSTR("Please use the file(.txt or .huffman) to open this program!"), ConvertCharToLPCWSTR("Warning!"), MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}

	// Get File Path
	std::string filePath = argv[1];

	// Open File and read
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filePath << std::endl;
		return 1;
	}
	file.close();

	filePath = ReplaceForwardSlash(filePath);

	std::cout << "文件路径: " << filePath << std::endl;
	/*cout << endl << "文件读取成功!" << endl;
	cout << "-------------------------------" << endl;
	Sleep(2000);
	system("cls");*/



	// Init Variables
	char* file_name = (char*)filePath.data();                // The name of the opened file
	char plaintext[2 * MAX_STR_SIZE] = "";        // The Plaintext read from the file
	char letter[2 * MAX_STR_SIZE] = { 0 };          // The Number of the character in the file
	char ciphertext[2 * MAX_STR_SIZE] = "";       // The Ciphertext encoded from the file
	char plaintext_decode[2 * MAX_STR_SIZE] = ""; // The Plaintext decoded from the  ciphertext
	int freq[MAX_STR_SIZE] = { 0 }, characount = 0; // The Frequency of each letter
	char file_name_noext[MAX_STR_SIZE] = "";

	HuffmanTree HT = nullptr; // The Haffman Tree
	HuffmanCode HC = nullptr; // The Haffman Code

	//strcpy(file_name, "text.txt");
	strcpy(letter, "");
	strcpy(plaintext, "");
	strcpy(ciphertext, "");
	strcpy(plaintext_decode, "");
	strcpy(file_name_noext, (char*)ExtractFileNameWithoutExtension(filePath).data());
	freq[MAX_STR_SIZE - 1] = { 0 };
	characount = 0;
	HT = nullptr;
	HC = nullptr;
	initWindow((char*)filePath.data()); //Init GUI

	ExMessage msg;
	if (EndsWithExt(filePath, ".txt")) {
		readFromFile(file_name, plaintext);
		uniqueChars(plaintext, letter, freq);
		for (int i = 0; letter[i]; i++) ++characount;
		CreateHuffmanTree(HT, freq, letter, characount);
		HuffmanCoding(HT, HC, characount);
		Encode(HT, HC, plaintext, ciphertext, characount);

		button(40, 190, 960, 250, (char*)"1. File Encryption");
		button(40, 260, 960, 320, (char*)"2. Exit ");

		while (1) {
			if (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 190 && msg.y <= 250)//File Encryption
					{
						char file_name_noext1[30];
						char file_name_noext2[30];
						strcpy(file_name_noext1, file_name_noext);
						strcpy(file_name_noext2, file_name_noext);
						strcat(file_name_noext1, ".hufftree");
						strcat(file_name_noext2, ".huffciph");

						ofstream outFile;
						outFile.open(file_name_noext2, ios::out);
						outFile << ciphertext;
						outFile.close();

						SaveHuffmanTreeToFile(HT, characount, file_name_noext1);
					}
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 260 && msg.y <= 320)//File Compression
					{
						exit(0);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	if (EndsWithExt(filePath, ".hufftree"))
	{
		LoadHuffmanTreeFromFile(HT, characount, (char*)filePath.data());

		char file_name_noext3[30];
		char file_name_noext4[30];
		strcpy(file_name_noext3, file_name_noext);
		strcpy(file_name_noext4, file_name_noext);
		strcat(file_name_noext3, ".huffciph");
		strcat(file_name_noext4, ".txt");

		ifstream inFile;
		inFile.open(file_name_noext3, ios::in);
		inFile >> ciphertext;
		inFile.close();

		cout << ciphertext << endl;
		cout << characount << endl;

		HuffmanCoding(HT, HC, characount);

		cout << "Character" << "    Huffman Code " << endl;
			for (int i = 1; i <= characount; i++)
			{
				cout << "      \"" << HT[i].ch << "\" -- " << HC[i] << endl;
			}

		cout << plaintext_decode << endl;

		system("pause");
	}
}