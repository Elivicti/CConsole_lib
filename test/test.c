#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"

void demo1()
{
	int flag = 1;
	TextUi* map = readTextUi("demo1_map.txt");
	TextUi* block = readTextUi("demo1_block.txt");
	TextUiShape* blockshape = getTextUiShape(NULL, block);
	CursorAnchor anchor_map = createCursorAnchor(0, 0);
	CursorAnchor anchor_block = createCursorAnchor(4, 3);
	// setCursorVisible(FALSE);
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
	map = NULL;
}

void demo2()
{
	
}

void demo3()
{
	
}

int main(int argc, char** argv)
{
	void (*demo[])() = { demo1, demo2, demo3 };
	initConsole();
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
		}
		else
			break;
	}
	

	return 0;
}