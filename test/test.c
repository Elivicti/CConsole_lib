#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"
#include <conio.h>

int main()
{
	initConsole();
	setTitle("My Title");
	CConsole c = getCursor(0, 3);
	int a = 1;
	printf("This is a text\n");
	setConsoleCursor(&c);
	setTextColor(Red);
	printf("This is a text\n");
	resetTextAttribute(TextColor);
	printf("This is a text\n");
	while (!_kbhit());
	
	return 0;
}