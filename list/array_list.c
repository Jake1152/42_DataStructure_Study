#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

// int main(int argc, int argv[])
int main()
{
	/*
		t_ArratList	arr_node;

		arr_node = createALElement(argv[1], argv[2]);
	*/
	ArrayList		*first_AList;

	printf("start\n");
	first_AList = createArrayList(42);

	printf("isArrayListFull %d\n", isArrayListFull(first_AList));
	

	return (0);
}

ArrayList	*createArrayList(int maxElementCount)
{
	/*
		element의 최대 개수를 넘겨받는다.
	*/
	ArrayList		*currentArrayList;	

	currentArrayList->maxElementCount = maxElementCount;
	currentArrayList->currentElementCount = 0;
	currentArrayList->pElement = (ArrayListNode	*)malloc(sizeof(ArrayListNode) * maxElementCount);
	return (currentArrayList);
}

int getArrayListLength(ArrayList* pList)
{
	return (pList->currentElementCount);
}

int isArrayListFull(ArrayList* pList)
{
	if (pList->maxElementCount == pList->currentElementCount)
		return (TRUE);
	else
		return (FALSE);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
	/*
		- position이 currentElementCount보다 큰 경우 FALSE
		- position이 maxElementCount보다 큰경우 realloc 필요
		  current == max && position == current
		  딱 1만큼만 커야한다.

		- position == currentElementCount 즉,맨 뒤이면 그냥 추가
		  currentElementCount++;
		- position < currentElementCount
		  position이 들어갈 자리에 있는 값을 tmp에 담아둔다.
		  currentElementCount 위치 값을 한칸 뒤로 물린다.
		  currentElementCount 앞에 값도 뒤로 물린다. (기존 currentElementCount위치로)
		  position위치까지 반복
	*/
	// 최대 크기보다 2이상 크면 FALSE return
	if (position > pList->maxElementCount || position > getArrayListLength(pList))
		return (FALSE);
	// 딱 마지막 위치라면 바로 추가
	else if (position + 1 == getArrayListLength(pList))
		pList->pElement[position] = element;
	// sizeup realloc, e.g) position = 7, currentElementCount == 7
	else if (isArrayListFull(pList) && \
			(position== getArrayListLength(pList)))
	{
		ArrayList	*toBeArrayListNode;
		int			idx;

		toBeArrayListNode = createArrayList(pList->maxElementCount * 2);
		idx = 0;
		while (idx < position)
		{
			toBeArrayListNode->pElement[idx] = pList->pElement[idx];
			idx++;
		}
		toBeArrayListNode->pElement[position] = element;
		deleteArrayList(pList);
		pList = toBeArrayListNode;
	}
	// max 이내이면서 중간에 끼는 경우
	else // 기존 position 위치에 있는 것은 tmp에 담는다.
	{
		ArrayListNode	tmpNode;
		int				idx;

		tmpNode = pList->pElement[position];
		idx = pList->currentElementCount;		
		while (idx > position)
		{
			pList->pElement[idx] = pList->pElement[idx - 1];
			idx--;
		}
		pList->pElement[idx] = tmpNode;
	}
	pList->currentElementCount += 1;
	return (pList->currentElementCount);
}

int removeALElement(ArrayList* pList, int position)
{
	/*
		중간 것을 지우면 바로 뒤에것부터 하나씩 앞으로 당겨온다.
		비어있는지 확인해야할 필요가 있는지?
	*/
	int idx;

	idx = position;
	if (getArrayListLength(pList) <= position)
		return (FALSE);
	// 길이 6 posi 3(4번째)
	// 1 2 3 4 5 6
	// 1 2 3 5 5 6
	// 1 2 3 5 6
	while (idx < getArrayListLength(pList))
	{
		pList->pElement[idx] = pList->pElement[idx + 1];
		idx++;
	}
	pList->pElement[idx].data = NULL;
	pList->currentElementCount -= 1;
	return (getArrayListLength(pList));
}

ArrayListNode	*getALElement(ArrayList* pList, int position)
{
	/*
		특정  index값 반환
		비어있으면? 그래도 반환
	*/
	if (position >= pList->currentElementCount || position >= pList->maxElementCount)
		return ((ArrayListNode	*)FALSE);
	return (&(pList->pElement[position]));
}

void clearArrayList(ArrayList* pList)
{
	/*
		array list를 삭제
		모든 요소를 1개씩 삭제한다.
		마지막인지 어떻게 알 것인가?
		siseof를 이용한다.
		NULL을 넣을 것인지
		사이즈를 별도로 알 것인지
		파라미터로 사이즈를 넘겨받지 않으니까
		마지막 표시를 별도로 한다.

		clear와 다른점
		clear는 arraylist의 모든 요소를 null로 처리
        [12,3,45,6]
        => [NULL, NULL, NULL, NULL]

		currentElementCount는 어떻게 할 것인가?
		값이 담긴 것은 아니니까 0으로 만든다.
	*/
	int	idx;

	idx = 0;
	while (idx < pList->currentElementCount)
	{
		pList->pElement[idx].data = NULL;
		idx++;
	}
	pList->currentElementCount = 0;
}

void deleteArrayList(ArrayList *pList)
{
	/*
		원소전체를 초기화
		free
	*/
	int	idx;

	idx = 0;
	while (idx < pList->currentElementCount)
	{
		free(&(pList->pElement[idx]));
		idx++;	
	}
	free(pList);
}

void displayArrayList(ArrayList* pList)
{
	/*
		첫 요소부터 끝 요소까지 display
	*/
	int	idx;
	// int	min_len;

	idx = 0;
	// min_len = pList->currentElementCount;
	// 만약 max가 cur보다 작은 경우? error? 여기서 고려할 부분이 아닌가? 
	// if (pList->currentElementCount > pList->maxElementCount)
	// 	min_len = pList->maxElementCount;
	// 문제점 중간에만 비어있는 경우
	// 초기화하는 부분이 없었다.
	// 하지만 그것은 arraylist라고 보지 않는다. 연속적어이여하니까.
	// 즉, 다 연속적이라는 가정하게 진행한다.
	while (idx < pList->currentElementCount)
	{
		printf("%d\n", pList->pElement[idx].data);
		idx++;
	}
}

/* 전체 고려사항
	* add를 연속적으로 안하면?
	* 연속적으로 하게 만들어야한다.
	* 물리적, 논리적으로 연속이어야 arraylist이므로.
*/

