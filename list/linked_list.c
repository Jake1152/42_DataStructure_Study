#include "linkedlist.h"
#include <stdlib.h>

int main()
{

	return (0);
}

LinkedList	*createLinkedList()
{
	/*
		넘겨받는 아무 argument가 없다.
	*/	
	LinkedList		*curLinkedList;
	ListNode		*curListNode;
	
	curLinkedList = malloc(sizeof(LinkedList));
	if (!(curLinkedList))
		return (NULL);	
	// curListNode를 꼭 초기화 해주어야하는가?
	curListNode->data = 0;
	curListNode->pLink = NULL;
	curLinkedList->headerNode = *curListNode;
	//curLinkedList->headerNode->pLink = NULL;
	curLinkedList->currentElementCount = 0;

	return (curLinkedList);
}

ListNode*	getLLElement(LinkedList* pList, int position)
{
	int			idx;
	ListNode	*curListNode;

	idx = 0;
	curListNode = pList->headerNode->pLink;
	while(idx < position)
	{
		curListNode = curListNode->pLink;
		idx++;
	}
	return (curListNode);
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
	int			idx;
	ListNode	curListNode;

	idx = 0;
	while(idx < position)
	{
		curListNode = pList->headerNode;
		idx++;
	}
	/*
		index 3에 추가
		012 3
		0123 4
	*/
}


int removeLLElement(LinkedList* pList, int position)
{
	/*

	*/

}


void clearLinkedList(LinkedList* pList)
{
	/*

	*/

}

int getLinkedListLength(LinkedList* pList)
{
	int			l_size;
	ListNode	*curLinkedNode;

	l_size = 0;
	curLinkedNode = pList->headerNode->pLink;
	while (curLinkedNode)
	{
		curLinkedNode = curLinkedNode->pLink;
		l_size++;
	}
	return (l_size);

}

void deleteLinkedList(LinkedList* pList)
{

}

