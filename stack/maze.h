#ifndef _MAZE_STACK_
#define _MAZE_STACK_
#define	HEIGHT 100
#define WIDTH 100
#include "linkedstack.h"

typedef struct MapPositionType {
	int			x;
	int			y;
	StackNode	*newStackNode;
} MapPosition;

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, \
				MapPosition endPos, \
				LinkedStack *pStack);
int pushLSMapPosition(LinkedStack* pStack, MapPosition data);
void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH]); void printMaze(int mazeArray[HEIGHT][WIDTH]);

#endif
