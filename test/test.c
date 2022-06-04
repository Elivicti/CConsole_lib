#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../CConsole.h"

void demo1()
{
	setConsoleTitle("BMI Caculator Demo");
	printf("BMI Caculator\n\n");
	float height = 0.0f, weight = 0.0f;
	printf("Input height(cm) and weight(kg): ");
	scanf("%f %f", &height, &weight);
	float bmi = weight * 10000.0f / (height * height);
	printf("BMI : ");
	setTextColor(Cyan);
	printf("%3.1f    ", bmi);
	resetTextAttribute(TextColor);
	if (bmi < 18.5f) {
		setTextColor(White);
		printf("Undeweight\n");
	}
	else if (bmi >= 18.5f && bmi < 24.0f) {
		setTextColor(Green);
		printf("Normal\n");
	}
	else if (bmi >= 24.0f && bmi < 28.0f) {
		setTextColor(Yellow);
		printf("Overweight\n");
	}
	else {
		setTextColor(Red);
		printf("Obese\n");
	}
	resetTextAttribute(TextColor | BackgroundColor);
	pauseConsole("\nPress Any Key to Return to Main Menu.");
}

void demo2()
{
#define KeyCase(c) case c: strcpy(chs, #c);
	setConsoleTitle("Keyboard Event Demo");
	printf("Try to press a Key.\n");
	int flag = 1;
	while (flag)
	{
		char chs[20] = { 0 };
		int ch = getPressedKey();
		if (ch >= 32 && ch <= 126)
			printf("%6c - %d\n", ch, ch);
		else
		{
			switch (ch)
			{
			KeyCase(ESC)
				flag = 0;
				break;
			KeyCase(TAB)	break;
			KeyCase(CAP)	break;
			KeyCase(Space)	break;
			KeyCase(LShift)	break;
			KeyCase(RShift)	break;
			KeyCase(LAlt)	break;
			KeyCase(RAlt)	break;
			KeyCase(LCtrl)	break;
			KeyCase(RCtrl)	break;
			KeyCase(Up)		break;
			KeyCase(Down)	break;
			KeyCase(Left)	break;
			KeyCase(Right)	break;
			default:
				break;
			}
			printf("%s - %d\n", chs, ch);
		}
		Sleep(100);
	}
	CLEAR_BUFFER();
	printf("Returning to main menu.");
	Sleep(3000);
#undef KeyCase
}

void demo3()
{
	int flag = 1;
	TextUi* map = readTextUi("demo3_map.txt");
	TextUi* block = readTextUi("demo3_block.txt");
	TextUiShape* blockshape = getTextUiShape(NULL, block);
	CursorAnchor anchor_map = createCursorAnchor(0, 0);
	CursorAnchor anchor_block = createCursorAnchor(4, 3);
	setCursorVisible(FALSE);
	setConsoleTitle("Tetris FrameWork Demo");
	while (flag)
	{ 
		drawTextUi(map, &anchor_map);
		printf("\n");
		moveCursor(0, -4);
		printf("Block Shape:\n");
		for (int i = 0; i < blockshape->height; i++)
		{
			for (int j = 0; j < blockshape->width; j++)
				printf("%2d", blockshape->data[i][j]);
			printf("\n");
		}

		drawTextUi(block, &anchor_block);
		int ch = getPressedKey();

		switch (ch)
		{
		case 'w':
			if (anchor_block.y > 1)
				moveCursorAnchor(&anchor_block, 0, -1);

			break;
		case 'a':
			if (anchor_block.x > 1)
				moveCursorAnchor(&anchor_block, -1, 0);
			break;
		case 's':
			if (anchor_block.y < map->height - 5 - block->height)
				moveCursorAnchor(&anchor_block, 0, 1);
			break;
		case 'd':
			if (anchor_block.x < map->width - 3 - block->width)
				moveCursorAnchor(&anchor_block, 1, 0);
			break;
		case 'h':
			rotateTextUi(block, TRUE);
			blockshape = getTextUiShape(blockshape, block);
			break;
		case ESC:
			flag = 0;
			break;

		default:
			break;
		}
	}
	
	deleteTextUi(map);
	deleteTextUi(block);
	deleteTextUiShape(blockshape);

	setCursorVisible(TRUE);	
}

int main(int argc, char** argv)
{
	void (*demo[])() = { demo1, demo2, demo3 };
	initConsole();
	setConsoleTitle("C Console Lib Demo");
	TextUi* menu = readTextUi("menu.txt");

	while (1)
	{
		drawTextUi(menu, NULL);
		int choice = 0;
		scanf("%d", &choice);
		if (choice > 0 && choice <= 3)
		{
			clearConsole();
			demo[choice - 1]();
			clearConsole();
			setConsoleTitle("C Console Lib Demo");
		}
		else
			break;
	}
	return 0;
}