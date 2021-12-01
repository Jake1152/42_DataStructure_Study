#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
	- 벽 1
	- 이동가능 0
	-------- 추가처리 ----------	
	- 왔던 길 2
	- 의미없는길 3
*/


int main()
{

	return(0);
}

void findPath(int mazeArray[HEIGHT][WIDTH], \
				MapPosition startPos, \
				MapPosition endPos, \
				LinkedStack *pStack)
{
	MapPosition	curPos;	
	int			dx[4] = {-1, 1, 0, 0};
	int			dy[4] = {0, 0, -1, 1};

	if (pStack == NULL)
		exit(EXIT_FAILURE);
	/*
		- 출구를 찾거나 못간곳이 없을동안 반복
		- 
		- pStack은 최종결과를 담는다.
	*/
	// 현재 위치가 갈 수 있는 곳인지?
	// 동남서북 순서로 search

	curPos = startPos;
	// 출구를 찾거나 갈수 있는 곳이 없어지면 break
	// 더이상 갈수 없다의 기준
	// 동서남북 다 돌았는데 벽이거나 이미 갔던 곳이면 
	while (TRUE)
	{
		// 갈수있는 곳 그러므로 stack에 저장하고서 2로 변경
		if (mazeArray[curPos.x][curPos.y] == 0)
		{
			
		}
	}
	pushLSMapPosition(pStack, curPos);
	newStackNode.pLink = NULL;
	pushLS(pStack, newStackNode);
}

int pushLSMapPosition(LinkedStack* pStack, MapPosition data)
{
	/*
		linked stack에 추가
	*/	

	if (pStack == NULL)
		return (FALSE);
	
	

}

void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
	if (pStack == NULL)
		exit(EXIT_FAILURE);
	
}

void printMaze(int mazeArray[HEIGHT][WIDTH])
{


}


/*
- 1안 pdf 방식
	- 연산상에 비효율적인 부분이 있지만 
	  되돌아갈때 pop해서 한칸씩 이동
	  방문한 곳은 2로 표시
	  되돌아갈때는 3으로 변경
	  즉 한번에 갈 수 있는 유효한 경로는 1번

- 2안 입구, 출구 모두 안주어짐
왼쪽 상단부터 행우선으로 순회하여 위치할 수 있는 곳이면(벽이 아니면)시작



===========================================================================================
# 토의전 생각

- 시작위치가 주어짐
1. 이동은 동서남북 순서
2. 이동할때마다 이동한 곳을 스택에 넣는다.
- 이동한 곳을 별도에 공간에 저장하거나
  기존 넘겨받은 지도에 값을 수정하여 표시한다.
  e.g)
	
	길이 1, 벽이 0인 경우
	이미 지나온 곳은 0이나 -1로 만든다.
	아니면 기존 지도는 그대로 놔두고 별도의 배열에 이동여부를 기록한다.
3. 더 이상 이동할 곳이 없다면 되돌아온다(pop)
000000
011011
001010
000000
4. 다음 가능한 곳으로 이동한다.
5. 3번 반복
6. 찾으면 출구 pop하고서 종료
	- 경로를 표시할 필요가 있는가?
	- 출구를 찾은 다음에 stack의 모든 요소를 출력하면 그것이 경로이다.
7. 못찾으면 -1 return

-----

1. 미로가 주어짐
2. 시작위치는?
	왼쪽 상단에서부터 1칸씩 이동하면서 찾아보기 
	빈공간부터 시작
3. 
4. 
*/