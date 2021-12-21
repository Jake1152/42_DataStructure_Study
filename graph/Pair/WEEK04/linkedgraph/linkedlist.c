#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *createLinkedList()
{
	LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
	linkedList->currentElementCount = 0;
	linkedList->headerNode.pLink = NULL;
	return (linkedList);
}

int addLLElement(LinkedList *pList, int position, ListNode element)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
		*newNode = element;
		newNode->pLink = NULL;
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++)
		{
			preNode = preNode->pLink;
		}
		newNode->pLink = preNode->pLink;
		preNode->pLink = newNode;
		pList->currentElementCount++;
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}	
int removeLLElement(LinkedList *pList, int position)
{
	ListNode *next;
	ListNode *node;

	if (!pList)
		return (FALSE);
	if (pList->currentElementCount == 0)
		return (FALSE);
	if (position < 0 || position > pList->currentElementCount)
		return (FALSE);
	node = &(pList->headerNode);
	for (int i = 0; i < position - 1; i++)
	{
		node = node->pLink;
	}
	next = node->pLink;
	node->pLink = next->pLink;
	pList->currentElementCount--;
	free(next);
	return (TRUE);
}

ListNode *getLLElement(LinkedList *pList, int position)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++)
		{
			preNode = preNode->pLink;
		}
		return (preNode->pLink);
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
}

int getLinkedListLength(LinkedList *pList)
{
	if (!pList)
		return (-1);
	return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList *pList)
{
	if (!pList)
		return;
	for (int i = 0; i < pList->currentElementCount; i++)
	{
		removeLLElement(pList, 0);
	}
	free(pList);
}
