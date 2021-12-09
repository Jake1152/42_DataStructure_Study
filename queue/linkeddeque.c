#include <stdio.h>
#include <stdlib.h>
#include "linkeddeque.h"

LinkedDeque* createLinkedDeque()
{
	LinkedDeque*    newLinkedDeque;

	newLinkedDeque = (LinkedDeque *)malloc(sizeof(LinkedDeque));

	newLinkedDeque->currentElementCount = 0;
	newLinkedDeque->pFrontNode = (DequeNode*)NULL;
	newLinkedDeque->pRearNode = (DequeNode*)NULL;

	return (newLinkedDeque);
}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	/*
		둘다 널
	*/
	if (pDeque == NULL)
		return (FALSE);
	if (pDeque->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	/*
		currentElementCount++
		front에 추가
	*/
	DequeNode*	newDequeNode;
	if (pDeque == NULL)
		return (FALSE);
	newDequeNode = (DequeNode *)malloc(sizeof(newDequeNode));
	if (newDequeNode == NULL)
		return (FALSE);
	newDequeNode->data = element.data;
	if (pDeque->pFrontNode == NULL)
	{
		pDeque->pFrontNode = newDequeNode;
		newDequeNode->pRLink = newDequeNode;
		newDequeNode->pLLink = newDequeNode;
	}		
	else
	{
		/* code */
		newDequeNode->pLLink = pDeque->pFrontNode->pLLink;
		pDeque->pFrontNode->pLLink->pRLink = newDequeNode;
		pDeque->pFrontNode->pLLink = newDequeNode;
		newDequeNode->pRLink = pDeque->pFrontNode;
		pDeque->pFrontNode = newDequeNode;
	}
	
	// ㅁ = ㅁ = ㅁ = ㅁ 양끝도 연결되어있음
	// ㅇ ㅁ ㅁ ㅁ ㅁ 
	newDequeNode->pLLink = pDeque->pFrontNode->pLLink;
	pDeque->pFrontNode->pLLink->pRLink = newDequeNode;
	pDeque->pFrontNode->pLLink = newDequeNode;
	newDequeNode->pRLink = pDeque->pFrontNode;
	pDeque->pFrontNode = newDequeNode;
	// node가 한개인 경우도 가정해야하는가?
	// 1개도 없었다면?
	
	pDeque->currentElementCount++;

	return (pDeque->currentElementCount);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	/*
		currentElementCount++
		rear에 추가
	*/
	if (pDeque == NULL)
		return (FALSE);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	/*

	*/
	if (pDeque == NULL)
		return (NULL);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
	/*

	*/
	if (pDeque == NULL)
		return (NULL);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	/*

	*/
	if (pDeque == NULL)
		return (NULL);
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
	/*

	*/
	if (pDeque == NULL)
		return (NULL);
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
	/*

	*/
	if (pDeque == NULL)
		return exit(EXIT_FAILURE);
}

