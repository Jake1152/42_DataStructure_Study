#ifndef _SORT_
#define _SORT_

#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"
#include "linkedlist.h"
/*
- sort O(N^2)
- sort O(N log n)
*/

// sort utils
size_t	returnArrayListMinIdx(ArrayList *pArray, size_t start_idx, size_t end_idx);
size_t	returnArrayListMaxIdx(ArrayList *pArray, size_t start_idx, size_t end_idx);

int returnLinkedListMin(LinkedList *pList, size_t start_idx, size_t end_idx);
int returnLinkedListMax(LinkedList *pList, size_t start_idx, size_t end_idx);

void swap(int *a, int *b);

// selection sort
void	arrayListSelectionSort(ArrayList *pArray, int orderType);

// bubble sort
void	arrayListBubbleSort(ArrayList *pArray, int orderType);

// insert sort
void	arrayListInsertSort(ArrayList *pArray, int orderType);
void	LinkedListInsertSort(LinkedList *pList, int orderType);

// quick sort


// merge sort


// shell sort 


// radix sort


// heap sort


#endif


#ifndef _COMMON_SORT_DEF_
#define _COMMON_SORT_DEF_

#define ARRAY	        1
#define LINKED	        2

#define ASC             1
#define DESC	        2

#endif
