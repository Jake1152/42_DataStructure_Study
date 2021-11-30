#include <stdio.h>
#include <stdlib.h>
#include "arraystack.h"

ArrayStack* createArrayStack(int maxElementCount)
{
	/*
		element의 최대 개수를 넘겨받는다.
	*/
	ArrayStack*		curArrayStack;
	// ArrayStackNode*	curArrayStackNode;

	if (maxElementCount <= 0)
		return (NULL);
	curArrayStack = malloc(sizeof(ArrayStack));
	if (curArrayStack == NULL)
		return (NULL);
	curArrayStack->pElement = malloc(sizeof(ArrayStackNode) * maxElementCount);
	if (curArrayStack->pElement)
		return (NULL);
	curArrayStack->maxElementCount = maxElementCount;
	curArrayStack->currentElementCount = 0;
	
	return (curArrayStack);
}

int pushAS(ArrayStack* pStack, ArrayStackNode element)
{
	int top;
	//size_t, ssize_t
	if (pStack == NULL)
		return (NULL);
	if (isArrayStackFull(pStack) == FALSE)
		return (NULL);
	top = pStack->currentElementCount;
	pStack->pElement[top].data = element.data;	
	pStack->currentElementCount += 1;

	return (pStack->currentElementCount);
}

ArrayStackNode* peekAS(ArrayStack* pStack)
{
	int top;
	ArrayStackNode* retArrayStackNode;
	//size_t
	if (pStack == NULL)
		return (NULL);
	if (isArrayStackEmpty(pStack) == TRUE)
		return (NULL);
	top = pStack->currentElementCount - 1;
	retArrayStackNode->data = pStack->pElement[top].data;
	// pStack자체로 접근한다ㅣ.
	return (retArrayStackNode);
}

ArrayStackNode* popAS(ArrayStack* pStack)
{
	int top;
	ArrayStackNode* retArrayStackNode;
	//size_t
	if (pStack == NULL)
		return (NULL);
	if (isArrayStackEmpty(pStack) == FALSE)
		return (NULL);
	top = pStack->currentElementCount - 1;
	retArrayStackNode->data = pStack->pElement[top].data;
	// retArrayStackNode으로 할것이면 동적할당을 해줘야하는가?
	pStack->pElement[top].data = '\0';
	// NULL할당하는게 나은가?
	pStack->currentElementCount -= 1;

	return (retArrayStackNode);
}

void deleteArrayStack(ArrayStack* pStack)
{
	if (pStack == NULL)
		exit(EXIT_FAILURE);
	free(pStack);
	// free(pStack);
	// pStack 가리키던 메모리영역이 할당 해제된다.
	// 그러므로 멤버변수 값들 초기화 시킬 필요는 없다 생각
}

int isArrayStackFull(ArrayStack* pStack)
{
	if (pStack == NULL)
		return (NULL);
	if (pStack->currentElementCount == pStack->maxElementCount)
		return (TRUE);
	return (FALSE);
}

int isArrayStackEmpty(ArrayStack* pStack)
{
	if (pStack == NULL)
		return (NULL);
	if (pStack->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}
