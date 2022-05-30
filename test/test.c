#include <stdio.h>

#define __CCONSOLE_TEST___
#include "../CConsole.h"

void demo1()
{
	TextUi* map = readTextUi("uimap.txt");
	TextUi* block = readTextUi("block1.txt");
	TextUiShape* blockshape = getTextUiShape(NULL, block);
	CursorAnchor anchor_map = createCursorAnchor(0, 0);
	CursorAnchor anchor_block = createCursorAnchor(4, 3);
	// setCursorVisible(FALSE);
	while (1)
	{
		drawTextUi(map, &anchor_map);
		printf("\n");
		moveCursor(0, -3);
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
			if (anchor_block.y < map->height - 1 - block->height)
				moveCursorAnchor(&anchor_block, 0, 1);
			break;
		case 'd':
			if (anchor_block.x < map->width - 1 - block->width)
				moveCursorAnchor(&anchor_block, 1, 0);
			break;
		case 'h':
			rotateTextUi(block, FALSE);
			blockshape = getTextUiShape(blockshape, block);

		default:
			break;
		}
	}
	
	deleteTextUi(map);
	deleteTextUi(block);
	map = NULL;
}

int main(int argc, char** argv)
{
	initConsole();
	demo1();

	return 0;
}