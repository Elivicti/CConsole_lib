#include "CConsole_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <conio.h>

HANDLE hStdConsole = NULL;

void initConsole() { hStdConsole = GetStdHandle(STD_OUTPUT_HANDLE); }
void setTitle(const char* title) { SetConsoleTitle(title); }
void setCursorVisible(BOOL visible)
{
	CONSOLE_CURSOR_INFO cursor_info = {1, visible};
	SetConsoleCursorInfo(hStdConsole, &cursor_info);
}
CConsole getCursor(SHORT x, SHORT y) 
{
	CConsole ret = {x, y};
	return ret;
}

void setCursor(CConsole* cursor, SHORT x, SHORT y) { cursor->x = x; cursor->y = y; }
void moveCursor(CConsole* cursor, SHORT dx, SHORT dy) { cursor->x += dx; cursor->y += dy; }
void setConsoleCursor(CConsole* cursor)
{
	COORD c = { cursor->x, cursor->y };
	SetConsoleCursorPosition(hStdConsole, c);
}

void setTextColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, col); }
void setTextBackgroundColor(StdColor col) { SetConsoleTextAttribute(hStdConsole, col << 4); }
void setTextAttribute(StdColor textColor, StdColor bgColor) { SetConsoleTextAttribute(hStdConsole, textColor | (bgColor << 4)); }
void resetTextAttribute(TextAttributeType attri)
{
	switch (attri)
	{
	case All:
		SetConsoleTextAttribute(hStdConsole, LightGray | (Black << 4));
		break;
	case TextColor:
		SetConsoleTextAttribute(hStdConsole, LightGray);
		break;
	case BackgroundColor:
		SetConsoleTextAttribute(hStdConsole, Black << 4);
		break;
	}
}

void pauseConsole(const char* tip)
{
#ifndef _MSC_VER
	if (tip) printf("%s", tip);
#else
	if (tip) printf_s("%s", tip);
#endif
	while (!_kbhit());	// pause
#ifndef _MSC_VER
	if (tip) printf("\n");
#else
	if (tip) printf_s("\n");
#endif
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

#ifdef __cplusplus
}
#endif