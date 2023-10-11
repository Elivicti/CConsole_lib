#include "../include/CConsole_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
// #include <stdarg.h>

#define PERR(bSuccess, api)  {if (!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

HANDLE hStdConsole = NULL;
StdColor txt = LightGray;	// current text color
StdColor bg = Black;		// current background color
CursorAnchor UPPER_LEFT = { 0, 0 };

BYTE** alloc2dBYTE(DWORD rowCnt, DWORD rowSize)
{
	BYTE** ret = (BYTE**)malloc(sizeof(BYTE*) * rowCnt);
	for (int i = 0; i < rowCnt; i++)
	{
		ret[i] = (BYTE*)malloc(sizeof(BYTE) * rowSize);
		memset(ret[i], 0, rowSize);
	}
	return ret;
}

BYTE** copy2dBYTE(BYTE** data, DWORD rowCnt, DWORD rowSize)
{
	BYTE** ret = (BYTE**)malloc(sizeof(BYTE*) * rowCnt);
	for (int i = 0; i < rowCnt; i++)
	{
		ret[i] = (BYTE*)malloc(sizeof(BYTE) * rowSize);
		memcpy(ret[i], data[i], rowSize);
	}
	return ret;
}

void free2dBYTE(BYTE** data, DWORD rowCnt)
{
	for (int i = 0; i < rowCnt; i++)
		free(data[i]);
	free(data);
}

void initConsole() { hStdConsole = GetStdHandle(STD_OUTPUT_HANDLE); }
void setConsoleTitle(const char* title) { SetConsoleTitle(title); }
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

void setTextColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, (txt = col) | bg); }
void setTextBackgroundColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, txt | (bg = (col << 4))); }
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
	// CLEAR_BUFF();
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
	static SHORT keys[] = {ESC, TAB, CAP, Space, LShift, RShift, LAlt, RAlt, LCtrl, RCtrl, Up, Down, Left, Right};
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


void cleanTextUiData(TextUi* ui)
{
	for (int i = 0; i < ui->height; i++)
		for (int j = 0; j < ui->width && !ui->data[i][j]; ui->data[i][j] = ' ', j++);
}

TextUi* readTextUi(const char* filepath)
{
	TextUi* ui = (TextUi*)malloc(sizeof(TextUi));
	FILE* fp = fopen(filepath, "rt");
	if (fp == NULL)
	{
		perror(filepath);
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

TextUi* copyTextUi(const TextUi* ui)
{
	if (ui != NULL && ui->data != NULL)
	{
		TextUi* cp = (TextUi*)malloc(sizeof(TextUi));
		cp->data = (BYTE**)malloc(sizeof(BYTE*) * ui->height);
		for (int i = 0; i < ui->height; i++)
		{
			cp->data[i] = (BYTE*)malloc(sizeof(BYTE) * (strlen(ui->data[i]) + 1));
			strcpy(cp->data[i], ui->data[i]);
		}
		return cp;
	}
	else
		return NULL;
}

BOOL saveTextUi(TextUi* ui, const char* filepath)
{
	FILE* fp = fopen(filepath, "wt+");
	if (fp == NULL)
	{
		perror(filepath);
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
void drawTextUi(const TextUi* ui, CursorAnchor* anchor)
{
	CursorAnchor* p_anchor = (anchor ? anchor : &UPPER_LEFT);
	for (int i = 0; i < ui->height; i++)
	{
		setCursor(p_anchor);
		moveCursor(0, i);
		printf("%s", ui->data[i]);
	}
}
TextUi* rotateTextUi(TextUi* ui, BOOL clockwise)
{
	BYTE** newdata = (BYTE**)malloc(sizeof(BYTE*) * ui->width);
	for (int i = 0; i < ui->width; i++)
	{
		newdata[i] = (BYTE*)malloc(sizeof(BYTE) * (ui->height + 1));
		memset(newdata[i], 0, ui->height + 1);	// do not forget '\0'
	}
	if (clockwise)
	{
		for (int i = 0; i < ui->height; i++)
		{
			int linelen = strlen(ui->data[i]);
			for (int j = 0; j < linelen; j++)
				newdata[j][ui->height - i - 1] = ui->data[i][j];
		}
	}
	else
	{
		for (int i = 0; i < ui->height; i++)
		{
			int linelen = strlen(ui->data[i]);
			for (int j = 0; j < linelen; j++)
				newdata[ui->width - j - 1][i] = ui->data[i][j];
		}
	}
	
	for (int i = 0; i < ui->height; i++)
		free(ui->data[i]);
	free(ui->data);

	ui->width  ^= ui->height;
	ui->height ^= ui->width;
	ui->width  ^= ui->height;
	ui->data    = newdata;

	cleanTextUiData(ui);
	return ui;
}
void flipTextUi(TextUi* ui, BOOL vertical)
{
	if (vertical)
	{
		for (int i = 0; i < ui->height / 2; i++)
		{
			BYTE* line = ui->data[i];
			ui->data[i] = ui->data[ui->height - i - 1];
			ui->data[ui->height - i - 1] = line;
		}
	}
	else
	{
		for (int i = 0; i < ui->height; i++)
		{
			int slen = strlen(ui->data[i]);
			if (slen < ui->width)
			{
				BYTE* newline = (BYTE*)malloc(sizeof(BYTE) * (ui->width + 1));
				memset(newline, 0, sizeof(BYTE) * (ui->width + 1));
				strcpy(newline, ui->data[i]);
				free(ui->data[i]);
				ui->data[i] = newline;
			}
			for (int j = 0; j < ui->width / 2; j++)
			{
				ui->data[i][j] ^= ui->data[i][ui->width - j - 1];
				ui->data[i][ui->width - j - 1] ^= ui->data[i][j];
				ui->data[i][j] ^= ui->data[i][ui->width - j - 1];
			}
		}
		cleanTextUiData(ui);
	}
}
void deleteTextUi(TextUi* ui)
{
	if (ui != NULL)
	{
		free2dBYTE(ui->data, ui->height);
		ui->data = NULL;
		ui->height = 0;
		ui->width = 0;
	}
}

TextUiShape* getTextUiShape(TextUiShape* shape, TextUi* ui)
{
	if (ui == NULL || ui->data == NULL)
		return NULL;

	if ( shape != NULL && shape->data != NULL)
		deleteTextUiShape(shape);

	if (shape == NULL)
		shape = (TextUiShape*)malloc(sizeof(TextUiShape));
	
	shape->data = (BYTE**)malloc(sizeof(BYTE*) * ui->height);
	shape->height = ui->height;
	shape->width = ui->width;
	for (int i = 0; i < ui->height; i++)
	{
		shape->data[i] = (BYTE*)malloc(sizeof(BYTE) * ui->width);
		memset(shape->data[i], 0, ui->width);
		for (int j = 0; j < ui->width; j++)
			shape->data[i][j] = (!isspace(ui->data[i][j]));
		
	}
	return shape;
}

TextUiShape* copyTextUiShape(TextUiShape* shape)
{
	if (shape != NULL && shape->data != NULL)
	{
		TextUiShape* cp = (TextUiShape*)malloc(sizeof(TextUiShape));
		cp->height = shape->height;
		cp->width = shape->width;
		cp->data = copy2dBYTE(shape->data, shape->height, shape->width);
	}
	else
		return NULL;
}

void deleteTextUiShape(TextUiShape* shape)
{
	if (shape != NULL && shape->data != NULL)
	{
		free2dBYTE(shape->data, shape->height);
		shape->data = NULL;
		shape->height = 0;
		shape->width = 0;
	}
}

#ifdef __cplusplus
}
#endif