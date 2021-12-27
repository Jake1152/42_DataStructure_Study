#include "sort.h"

/*
	- 분할:
		해결하고자 하는 문제를 작은 크기의 동일한 문제들로 분할
	- 정복
		각각의 작은 문제를 순환적으로 해결
	- 합병
		작은 문제의 해를 합하여 원래 문제에 대한 해를 구함
*/


void	mergeSort(ArrayList *pArray, int p, int r)	// A[p...r]을 정렬
{
	if (p < r)
	{
		q = (p + q) / 2;
		mergeSort(pArray, p, q);
		mergeSort(pArray, q + 1, r);
		merge(pArray, p, q, r);
	}
}

void    merge(ArrayList *pArray, int p, int q, int r)
{
	int i;
	int j;
	int k;
	int tmp[pArray->currentElementCount];	// 정렬에 쓰일 추가 메모리 공간

	i = p;
	j = q + 1;
	k = p;
	while (i <= q && j <= r)
	{
		if (pArray->pElement[i].data <= pArray->pElement[j].data)
		{
			tmp[k] = data[i];
			k++;
			i++;
		}
		else
		{
			tmp[k] = data[j];
			k++;
			j++;
		}
	}
	while (i <= q)
	{
		tmp[k] = data[i];
		k++;
		i++;
	}
	while (j <= r)
	{
		tmp[k] = data[j];
		k++;
		j++;
	}
	i = p;
	while (i <= r)
	{
		pArray->pElement[i].data = tmp[i];
		i++
	}
}


void	arrayListMergeSort(ArrayList *pArray, int orderType)
{
	continue ;
}

void	linkedListMergeSort(LinkedList *pList, int orderType)
{
	continue ;
}
