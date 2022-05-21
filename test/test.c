#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"
#include <conio.h>

#include <stdarg.h>

#include <string.h>
int main()
{
	moveCursor(1, 0);
	printf("aa");
	return 0;
}

// int main()
// {
// 	initConsole();
// 	printf("Program Running...\n");
// 	myprint("Hello World! %5d %d", 5, 15);

// 	printf("\nProgram Exited.\n");
// 	return 0;
// }