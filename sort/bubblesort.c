#include "sort.h"

/*
	80 50 70 10 60 20 40 30

	오른쪽에 제일 큰 값(혹은 제일 작은 값)부터 넣는다.
	// ASC
	- 80 50 70 10 60 20 40 30
		- 50 80 70 10 60 20 40 30
		- 50 70 80 10 60 20 40 30
		- 50 70 10 80 60 20 40 30
		- 50 70 10 60 80 20 40 30
		- 50 70 10 60 20 80 40 30
		- 50 70 10 60 20 40 80 30
		- 50 70 10 60 20 40 30 80
	- 50 70 10 60 20 40 30 "80"
		- 50 70 10 60 20 40 30 "80"
		- 50 10 70 60 20 40 30 "80"
		- 50 10 60 70 20 40 30 "80"
		- 50 10 60 20 70 40 30 "80"
		- 50 10 60 20 40 70 30 "80"
		- 50 10 60 20 40 30 70 "80"
	- 50 10 60 20 40 30 "70" "80"
	... repeat
*/

void    bubbleSort(ArrayList *pArray, int orderType)
{
	size_t  target_idx;
	size_t	cur_idx;
	size_t  prev_idx;

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
	// 끝 인덱스를 점점 줄여야한다.	
	// 오른쪽부터 시작
	target_idx = pArray->currentElementCount - 1;
	if (orderType == DESC)
	{
		while (target_idx >= 1)
		{
			cur_idx = 1;
			while (cur_idx <= target_idx)
			{
				prev_idx = cur_idx - 1;
				if (pArray->pElement[prev_idx].data < pArray->pElement[cur_idx].data)
					swap(&(pArray->pElement[prev_idx].data), &(pArray->pElement[cur_idx].data));
				cur_idx++;
			}
			target_idx--;
		}
	}
	else // ASC
	{
		while (target_idx >= 1)
		{
			cur_idx = 1;
			while (cur_idx <= target_idx)
			{
				prev_idx = cur_idx - 1;
				if (pArray->pElement[prev_idx].data > pArray->pElement[cur_idx].data)
					swap(&(pArray->pElement[prev_idx].data), &(pArray->pElement[cur_idx].data));
				cur_idx++;
			}
			target_idx--;
		}
	}
}
