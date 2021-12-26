#include "sort.h"

/*
	왼쪽부터 뽑아서 적당한 위치에 삽입한다.
	별도의 자료 공간이 필요한가?

	별도의 자료공간 쓰지 않는다.
	arraylist의 경우 
	밀어내기해야하는 점에서 불편한 점이 있다.
	array list에 구현된 항목 사용 필요
 
    - 
    - 
    ㅁ ㅁ ㅁ ㅁ ㅁ 
    80 84 90 120
    80 50 70 10 60 20 40 30
    [80] [50 70 10 60 20 40 30]
    [50 80] [70 10 60 20 40 30]
*/

void	insertSort(ArrayList *pArray, int orderType)
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
}