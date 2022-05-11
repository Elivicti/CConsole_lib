#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"
#include <conio.h>


int main()
{
	initConsole();
	pauseConsole("Press Any Key to Continue...");
	return 0;
}