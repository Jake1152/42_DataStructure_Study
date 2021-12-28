#include "sort.h"

/*
	- 왼쪽에 가장 작은 값을 넣는다.
	- 왼쪽은 정렬된 리스트
	- 오른쪽은 아직 정렬안된 리스트
	- array, linked list에 따른 구분 필요
		- 처음에 넘겨줄떄 처리해야한다.
		- pArrayList, pLinkedList를 넘겨줄지 갈리므로.
	- 정렬순서에 따른 구분

	- 시작은 ASC

	- array list 기준

	- key 값은 무조건 int라는 가정이어야하는가?
	- 그렇게하는게 편리하기에 그렇게하며
	- int 이외인것은 data로 별도로 뺴서 판단한다. key와 data는 개별로 관리

	- 원본은 놔두고 sorted된 것을 반환해주는 함수도 줄것인가?
*/

void    arrayListSelectionSort(ArrayList *pArray, int orderType)
{
	size_t	idx;
	size_t	start_idx;
	size_t		key_idx;

	if (pArray == NULL)
	{
		printf("pArray is NULL.\n");
		return ;
	}
	if (pArray->currentElementCount > pArray->maxElementCount)
	{
		printf("pArray currentElementCount is over maxElementCount.\n");
		return ;
	}
	if (pArray->currentElementCount <= 1)
	{
		printf("pArray size is under 1.\n");
		return ;
	}
	idx = 0;
	if (orderType == DESC)
	{
		while (idx < pArray->currentElementCount - 1)
		{
			start_idx = idx + 1;
			// find min
			key_idx = returnArrayListMaxIdx(pArray,  start_idx, pArray->currentElementCount);
			if (pArray->pElement[key_idx].data > pArray->pElement[idx].data)
				swap(&(pArray->pElement[key_idx].data), &(pArray->pElement[idx].data));
			idx++;
		}
	}
	else // DESC가 아니면 무조건 ASC로 되게한다.
	{
		/*
			80 50 70 10 60 20 40 30
			[10] [50 70 80 60 20 40 30]

			i 부터 size-1까지 순회
			j는 i+1부터 size중에 가장 작은 값을 찾아서 
			i와 비교한뒤 옮긴다.
		*/
		// pArray->pElement->data;
		while (idx < pArray->currentElementCount - 1)
		{
			start_idx = idx + 1;
			// find min
			key_idx = returnArrayListMinIdx(pArray,  start_idx, pArray->currentElementCount);
			if (key_idx < pArray->pElement[idx].data)
				swap(&(pArray->pElement[key_idx].data), &(pArray->pElement[idx].data));
			idx++;
		}
	}

}

