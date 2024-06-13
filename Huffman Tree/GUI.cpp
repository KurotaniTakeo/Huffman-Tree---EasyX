#include "GUI.h"

LPCWSTR ConvertCharToLPCWSTR(const char* charString) {
	int len = MultiByteToWideChar(CP_ACP, 0, charString, -1, NULL, 0);
	wchar_t* wCharString = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, charString, -1, wCharString, len);

	return wCharString;
}

wchar_t* ConvertToUnicode(const char* str, UINT codePage) {
	int len = MultiByteToWideChar(codePage, 0, str, -1, NULL, 0);
	wchar_t* wideStr = new wchar_t[len];
	MultiByteToWideChar(codePage, 0, str, -1, wideStr, len);

	return wideStr;
}

std::string ReplaceForwardSlash(const std::string& str) {
	std::string result = str;
	size_t pos = 0;

	// ���ַ����в��� "/"
	while ((pos = result.find("/")) != std::string::npos) {
		// �滻 "/" Ϊ "\\"
		result.replace(pos, 1, "\\\\");
	}

	return result;
}

void initWindow(char* file_name)
{
	initgraph(1000, 600, EX_SHOWCONSOLE);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, _T("�����������Ӧ�� by ���Ȼ"));
	setbkcolor(RGB(250, 248, 239));
	cleardevice();
	setfillcolor(RGB(118, 109, 101));
	solidroundrect(40, 43, 960, 133, 20, 20);
	setfillcolor(RGB(187, 173, 160));
	solidroundrect(40, 40, 960, 130, 20, 20);

	LOGFONT title_font;
	gettextstyle(&title_font);
	title_font.lfHeight = 75;// ���������С
	title_font.lfWeight = FW_BOLD; // ��������
	settextcolor(RGB(118, 109, 101));// ����������ɫ
	_tcscpy_s(title_font.lfFaceName, _T("΢���ź�"));// ��������
	RECT title_pos = { 40, 43, 960, 133 };
	title_font.lfQuality = ANTIALIASED_QUALITY;// �������Ч��Ϊ����� 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextstyle(&title_font);// ����������ʽ
	drawtext(_T("Application of Huffman Coding"), &title_pos, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	gettextstyle(&title_font);
	settextcolor(RGB(250, 248, 239));// ����������ɫ
	title_pos = { 40, 40, 960, 130 };
	settextstyle(&title_font);// ����������ʽ
	drawtext(_T("Application of Huffman Coding"), &title_pos, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	LOGFONT filePath;
	gettextstyle(&filePath);
	filePath.lfHeight = 30;// ���������С
	filePath.lfWeight = FW_BOLD;
	settextcolor(RGB(118, 109, 101));// ����������ɫ
	_tcscpy_s(filePath.lfFaceName, _T("΢���ź�"));// ��������
	RECT path_pos = { 60, 135, 960, 165 };
	filePath.lfQuality = ANTIALIASED_QUALITY;// �������Ч��Ϊ����� 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextstyle(&filePath);// ����������ʽ
	TCHAR filename[100];
	_stprintf_s(filename, _T("%s%s"), _T("Current File��"), ConvertToUnicode(file_name, CP_UTF8));
	drawtext(filename, &path_pos, DT_SINGLELINE);
}

void button(int left, int top, int right, int bottom, char* bottonText)
{
	setfillcolor(RGB(118, 109, 101));
	solidroundrect(left, top + 2, right, bottom + 2, 20, 20);
	setfillcolor(RGB(187, 173, 160));
	solidroundrect(left, top, right, bottom, 20, 20);

	RECT buttonTextPos = { left + 40, top, right, bottom };

	LOGFONT ButtonFont;
	gettextstyle(&ButtonFont);
	ButtonFont.lfHeight = 40;// ���������С
	ButtonFont.lfWeight = FW_BOLD;
	settextcolor(RGB(118, 109, 101));// ����������ɫ
	_tcscpy_s(ButtonFont.lfFaceName, _T("΢���ź�"));// ��������
	ButtonFont.lfQuality = ANTIALIASED_QUALITY;// �������Ч��Ϊ����� 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextstyle(&ButtonFont);// ����������ʽ

	TCHAR botton_text[100];
	_stprintf_s(botton_text, _T("%s"), ConvertToUnicode(bottonText, CP_UTF8));
	drawtext(botton_text, &buttonTextPos, DT_SINGLELINE | DT_VCENTER);
}

void status(const char* status)
{
	LOGFONT filePath;
	gettextstyle(&filePath);
	filePath.lfHeight = 30;// ���������С
	filePath.lfWeight = FW_BOLD;
	settextcolor(RGB(118, 109, 101));// ����������ɫ
	_tcscpy_s(filePath.lfFaceName, _T("΢���ź�"));// ��������
	filePath.lfQuality = ANTIALIASED_QUALITY;// �������Ч��Ϊ����� 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextstyle(&filePath);// ����������ʽ
	RECT path_pos = { 60, 360, 960, 560 };

	setfillcolor(RGB(218, 210, 199));
	solidroundrect(40, 350, 960, 560, 20, 20);
	TCHAR statusout[100];
	_stprintf_s(statusout, _T("%s%s"), _T("Current Staus��\n"), ConvertToUnicode(status, CP_UTF8));
	drawtext(statusout, &path_pos, DT_LEFT);
}