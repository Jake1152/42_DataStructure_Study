#include "sort.h"

/*
	- min, max check
*/

size_t	returnArrayListMinIdx(ArrayList *pArray, size_t start_idx, size_t end_idx)
{
	size_t	idx;
	int		min_idx;

	if (pArray == NULL || pArray->currentElementCount <= start)
		return (FALSE);
	min_idx = start_idx;
	idx = start_idx + 1;
	while (idx <= end_idx)
	{
		if (pArray->pElement[idx]->data < pArray->pElement[min_idx]->data)
			min_idx = idx;
		idx++;
	}
	return (min_idx)
}

size_t	returnArrayListMaxIdx(ArrayList *pArray, size_t start_idx, size_t end_idx)
{
	size_t	idx;
	int		max_idx;

	if (pArray == NULL || pArray->currentElementCount <= start)
		return (FALSE);
	max_idx = start_idx;
	idx = start_idx + 1;
	while (idx <= end_idx)
	{
		if (pArray->pElement[idx]->data > pArray->pElement[max_idx]->data)
			max_idx = idx;
		idx++;
	}
	return (max_idx)
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}