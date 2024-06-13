#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <string>

LPCWSTR ConvertCharToLPCWSTR(const char* charString);
wchar_t* ConvertToUnicode(const char* str, UINT codePage);
std::string ReplaceForwardSlash(const std::string& str);
void initWindow(char* file_name);
void button(int left, int top, int right, int bottom, char* bottonText);
void status(const char* status);

#endif