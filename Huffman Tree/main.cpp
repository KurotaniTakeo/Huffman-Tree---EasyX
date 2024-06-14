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
		MessageBox(NULL, ConvertCharToLPCWSTR("Please use the file(.txt or .hufftree) to open this program!"), ConvertCharToLPCWSTR("Warning!"), MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}

	// Get File Path
	std::string filePath = argv[1];
	initWindow((char*)filePath.data()); //Init GUI
	// Open File and read
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filePath << std::endl;
		status("Read from file FAILD!");
		button(40, 190, 960, 250, (char*)"File Encryption");
		ExMessage msg;
		while (1) {

			if (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 190 && msg.y <= 250)//File Encryption
					{
						return 1;
					}
				}
			}
		}
	}
	file.close();

	filePath = ReplaceForwardSlash(filePath);

	std::cout << "文件路径: " << filePath << std::endl;

	status("Read from file SUCCESS!");

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

	ExMessage msg;
	if (EndsWithExt(filePath, ".txt")) {
		readFromFile(file_name, plaintext);
		status("Read from file SUCCESS!\nWaiting for next step...");

		button(40, 200, 960, 260, (char*)"File Encryption");
		button(40, 280, 960, 340, (char*)"Exit ");

		while (1) {
			if (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 200 && msg.y <= 260)//File Encryption
					{
						uniqueChars(plaintext, letter, freq);
						for (int i = 0; letter[i]; i++) ++characount;
						CreateHuffmanTree(HT, freq, letter, characount);
						status("Huffman Tree Build SUCCESS!");
						HuffmanCoding(HT, HC, characount);
						Encode(HT, HC, plaintext, ciphertext, characount);
						status("Huffman Tree Build SUCCESS! \nHuffman Coding SUCCESS!");

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
						status("Ciphertext SAVED! ");

						SaveHuffmanTreeToFile(HT, characount, file_name_noext1);
						status("Ciphertext SAVED! \nHuffman tree SAVED! \nEncryption Accomplished.");
					}
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 280 && msg.y <= 340)//Exit
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
		status("Read from file SUCCESS!\nWaiting for next step...");
		button(40, 200, 960, 260, (char*)"File Decryption");
		button(40, 280, 960, 340, (char*)"Exit ");

		while (1) {
			if (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 200 && msg.y <= 260)//File Encryption
					{
						LoadHuffmanTreeFromFile(HT, characount, (char*)filePath.data());
						status("Load Huffman Coding SUCCESS!");
						char file_name_noext4[30];
						strcpy(file_name_noext4, file_name_noext);
						strcat(file_name_noext4, ".txt");

						ifstream inFile;
						inFile.open(replaceFileExtension(filePath, "huffciph"), ios::in);
						inFile >> ciphertext;
						inFile.close();

						HuffmanCoding(HT, HC, characount);
						status("Load Huffman Tree SUCCESS!\n Huffman Coding SUCCESS!");

						Decode(HT, ciphertext, plaintext_decode, characount);

						cout << plaintext_decode << endl;

						ofstream outFile;
						outFile.open(replaceFileExtension(filePath, "txt"), ios::out);
						outFile << plaintext_decode;
						outFile.close();
						status("Load Huffman Tree SUCCESS!\n Huffman Coding SUCCESS!\nPlaintext SAVED!");

						status("Huffman Coding SUCCESS!\nPlaintext SAVED!\nEncryption Accomplished.");

					}
					if (msg.x >= 40 && msg.x <= 960 && msg.y >= 280 && msg.y <= 340)//Exit
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
}