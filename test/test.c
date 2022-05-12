#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"
#include <conio.h>

int main()
{
	initConsole();
	printf("Program Running...\n");
	while (1)
	{
		printf("%d\n", isCharKeyPressed('h'));
		Sleep(500);
	}
	printf("\nProgram Exited.\n");
	return 0;
}