#include "CConsole_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

#define CLEAR_BUFF() {int __ch; while ((__ch = getchar()) != EOF && __ch != '\n');}
#define PERR(bSuccess, api)  {if (!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

HANDLE hStdConsole = NULL;
StdColor txt = LightGray;	// current text color
StdColor bg = Black;		// current background color

void initConsole() { hStdConsole = GetStdHandle(STD_OUTPUT_HANDLE); }
void setTitle(const char* title) { SetConsoleTitle(title); }
void setCursorVisible(BOOL visible)
{
	CONSOLE_CURSOR_INFO cursor_info = {1, visible};
	SetConsoleCursorInfo(hStdConsole, &cursor_info);
}
void clearConsole()
{
	COORD coordScreen = { 0, 0 };			// Coordinate of upper left
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;		// Screen buffer
	DWORD dwConSize;						// Buffer size
	bSuccess = GetConsoleScreenBufferInfo(hStdConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// Fill buffer with blank
	bSuccess = FillConsoleOutputCharacter(hStdConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	bSuccess = GetConsoleScreenBufferInfo(hStdConsole, &csbi);
	// Fill console screen
	bSuccess = FillConsoleOutputAttribute(hStdConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// Set cursor position
	bSuccess = SetConsoleCursorPosition(hStdConsole, coordScreen);
}

CursorAnchor createCursorAnchor(SHORT x, SHORT y) 
{
	CursorAnchor ret = { x, y };
	return ret;
}
void setCursorAnchor(CursorAnchor* anchor, SHORT x, SHORT y) { anchor->x = x; anchor->y = y; }
void moveCursorAnchor(CursorAnchor* anchor, SHORT dx, SHORT dy) { anchor->x += dx; anchor->y += dy; }

CursorAnchor getCursor()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(hStdConsole, &screen_info);
	CursorAnchor anchor = { screen_info.dwCursorPosition.X, screen_info.dwCursorPosition.Y };
	return anchor;
}
void setCursor(CursorAnchor* anchor)
{
	COORD c = { anchor->x, anchor->y };
	SetConsoleCursorPosition(hStdConsole, c);
}
void moveCursor(SHORT dx, SHORT dy)
{
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(hStdConsole, &screen_info);
	COORD c = { screen_info.dwCursorPosition.X + dx, screen_info.dwCursorPosition.Y + dy };
	SetConsoleCursorPosition(hStdConsole, c);
}

void setTextColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, txt = col); }
void setTextBackgroundColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, bg = (col << 4)); }
void setTextAttribute(StdColor textColor, StdColor bgColor) { SetConsoleTextAttribute(hStdConsole, (txt = textColor) | (bg = (bgColor << 4))); }
void resetTextAttribute(TextAttributeType attri)
{
	switch (attri)
	{
	case All:
		SetConsoleTextAttribute(hStdConsole, LightGray | (Black << 4));
		break;
	case TextColor:
		SetConsoleTextAttribute(hStdConsole, LightGray | bg);
		break;
	case BackgroundColor:
		SetConsoleTextAttribute(hStdConsole, txt | (Black << 4));
		break;
	}
}

void pauseConsole(const char* tip)
{
	if (tip) printf("%s", tip);
	while (!_kbhit());	// Pause
	CLEAR_BUFF();
	if (tip) printf("\n");
}
BOOL isCharKeyPressed(char ch)
{
	if (_kbhit()) 
		return ch == _getch();
}
BOOL isKeyPressed(KeyType key) { return (GetKeyState(key) & 0x8000); }
BOOL isKeyToggled(KeyType key) { return (GetKeyState(key) & 0x01); }
int getPressedKey()
{
	static SHORT keys[] = {ESC, TAB, CAP, Space, LShift, Rshift, LAlt, RAlt, LCtrl, RCtrl, Up, Down, Left, Right};
	BOOL vk_flag = FALSE;
	int i = 0;
	while (TRUE)
	{
		for (i = 0; (i < 14) && !vk_flag; vk_flag = isKeyPressed(keys[i]), i++);
		if (vk_flag)
			return keys[i - 1];
		if (_kbhit())
			return _getch();
	}
}

TextUi* readTextUi(const char* filepath)
{
	TextUi* ui = (TextUi*)malloc(sizeof(TextUi));
	FILE* fp = fopen(filepath, "rt");
	if (fp == NULL)
	{
		perror("Failed to open file.");
		return NULL;
	}

	// Read and preprocess data
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	BYTE* fdata = (BYTE*)malloc(sizeof(BYTE) * (fsize + 1));
	rewind(fp);
	fread(fdata, sizeof(BYTE), fsize, fp);
	fdata[fsize] = '\0';								// Append '\0' to make a usable string
	fdata[fsize - 1] *= (fdata[fsize - 1] != '\n');		// Ignore '\n' at the end
	
	// Calculate line count
	ui->height = 1;
	for (int i = 0; i < fsize; i++)
		ui->height += (fdata[i] == '\n');

	ui->data = (BYTE**)malloc(sizeof(BYTE*) * ui->height);
	
	// Split file data into lines
	BYTE* line = strtok(fdata, "\n");	// Because of here, the processed data does not contain '\n'
	ui->width = 0;
	for (int i = 0; i < ui->height && line != NULL; i++)
	{
		size_t len = strlen(line);
		if (len > ui->width)			// Only save the length of the longest line ('\0' not included)
			ui->width = len;

		ui->data[i] = (BYTE*)malloc(sizeof(BYTE) * (len + 1));
		strcpy(ui->data[i], line);
		line = strtok(NULL, "\n");		// Because of here, the processed data does not contain '\n'
	}

	free(fdata);
	fclose(fp);

	return ui;
}
BOOL saveTextUi(TextUi* ui, const char* filepath)
{
	FILE* fp = fopen(filepath, "wt+");
	if (fp == NULL)
	{
		perror("Failed to open file.");
		return FALSE;
	}

	for (int i = 0; i < ui->height; i++)
	{
		fwrite(ui->data[i], sizeof(BYTE), strlen(ui->data[i]), fp);
		fwrite("\n", sizeof(char), strlen("\n"), fp);
	}
	
	fclose(fp);
	return TRUE;
}
void drawTextUi(TextUi* ui, CursorAnchor* anchor)
{
	for (int i = 0; i < ui->height; i++)
	{
		setCursor(anchor);
		moveCursor(0, i);
		printf("%s", ui->data[i]);
	}
}
void deleteTextUi(TextUi* ui)
{
	if (ui != NULL)
	{
		for (int i = 0; i < ui->height; i++)
			free(ui->data[i]);
		free(ui->data);
		ui->data   = NULL;
		ui->height = 0;
		ui->width  = 0;
	}
}

#ifdef __cplusplus
}
#endif