#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"

int main()
{
	initConsole();
	TextUi* ui = readTextUi("testui.txt");
	CursorAnchor anchor = createCursorAnchor(0, 0);
	setTextAttribute(Red, White);
	drawTextUi(ui, &anchor);
	resetTextAttribute(All);
	int ch = getPressedKey();
	printf("\n%c pressed.\n", ch);
	
	deleteTextUi(ui);
	ui = NULL;
	
	return 0;
}