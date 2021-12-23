#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

static LinkedList	*reverseLinkedList(LinkedList* pList);

/*

int main()
{
	LinkedList*	mainLinkedList;
	ListNode 	element;

	mainLinkedList = createLinkedList();
	for (int i = 0; i < 10; i++)
	{
		element.data = i;
		printf("addLLElement(mainLinkedList, i, element) : %d\n", addLLElement(mainLinkedList, i, element));
	}
	printf("currentElementCount : %d\n", mainLinkedList->currentElementCount);
	displayLinkedList(mainLinkedList);
	for (int i = 4; i < 6; i++)
		printf("removeLLElement(mainLinkedList, i) : %d\n", removeLLElement(mainLinkedList, i));
	printf("currentElementCount : %d\n", mainLinkedList->currentElementCount);
	displayLinkedList(mainLinkedList);
	// clearLinkedList(mainLinkedList);
	// printf("after clearLinkedList\n");
	// displayLinkedList(mainLinkedList);
	printf("mainLinkedList pointer address : %p\n", mainLinkedList);
	printf("mainLinkedList pointer : %x\n", mainLinkedList);
	clearLinkedList(mainLinkedList);// double pointer	
	printf("after clearLinkedList\n");
	printf("mainLinkedList pointer address : %p\n", mainLinkedList);
	printf("mainLinkedList pointer : %x\n", mainLinkedList);
	displayLinkedList(mainLinkedList);
	element.data = 42;
	printf("addLLElement(mainLinkedList, i, element) : %d\n", addLLElement(mainLinkedList, 0, element));
	printf("getLinkedListLength(mainLinkedList) : %d\n", getLinkedListLength(mainLinkedList));
	displayLinkedList(mainLinkedList);
	printf("done\n");

	return (0);
}

*/

LinkedList	*createLinkedList()
{
	/*
		넘겨받는 아무 argument가 없다.
	*/
	LinkedList*	curLinkedList;

	curLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
	if (curLinkedList == NULL)
		return (NULL);
	curLinkedList->currentElementCount = 0;
	return (curLinkedList);
}

int getLinkedListLength(LinkedList* pList)
{
	int			l_size;
	ListNode	*curLinkedNode;

	if (pList == NULL)
		return (FALSE);
	l_size = 0;
	curLinkedNode = pList->headerNode;
	// ListNode headerNode.;
	// struct ListNodeType* pLink;
	while (curLinkedNode)
	{
		curLinkedNode = curLinkedNode->pLink;
		l_size++;
	}
	return (l_size);
}

ListNode*	getLLElement(LinkedList* pList, int position)
{
	int			idx;
	ListNode	*curListNode;

	if (pList == NULL)
		return (NULL);
	if (position > pList->currentElementCount)
		return (NULL);
	idx = 0;
	curListNode = pList->headerNode;
	while(idx < position)
	{
		curListNode = curListNode->pLink;
		idx++;
	}
	return (curListNode);
}

int	addLLElement(LinkedList* pList, int position, ListNode element)
{
	ListNode*	newListNode;
	ListNode*	prevListNode;

	printf("in addLLElement\n");
	if (pList == NULL)
		return (FALSE);
	if (position >= 0 && position > pList->currentElementCount)
	{
		printf("position : %d\n", position);
		printf("pList->currentElementCount : %d\n", pList->currentElementCount);
		return (FALSE);
	}	
	newListNode = (ListNode*)malloc(sizeof(ListNode));
	// pList도 각 요소들 다 
	if (newListNode == NULL)
		return (FALSE);
	newListNode->data = element.data;
	if (position == 0)
	{
		newListNode->pLink = NULL;
		pList->headerNode = newListNode;
		// printf("test in addElement\n");
		// printf("pList->headerNode->data : %d\n", pList->headerNode->data);
	}
	else
	{
		// printf("test in addElement second \n");
		// printf("position : %d\n", position);
		prevListNode = getLLElement(pList, position - 1);
		newListNode->pLink = prevListNode->pLink;
		prevListNode->pLink = newListNode;
	}
	pList->currentElementCount++;
	return (pList->currentElementCount);
}

int removeLLElement(LinkedList* pList, int position)
{
	/*
		넘겨받는 node를 지움
		- position이 cur 이상인지
		- 이전 노드를 가져옴
		- 이전 노드에게 position 다음 노드를 가리키게 만듦
		- header가 가리키는것 변경
	*/
	ListNode	*prevListNode;
	ListNode	*delListNode;
	ListNode	*now;
	ListNode	*prev;
	int			prev_idx;

	if (pList == NULL)
		return (FALSE);
	if (position >= pList->currentElementCount)
		return (FALSE);
	prev_idx = position - 1;
	if (position == 0)
		prev_idx = 0;
	if (pList->currentElementCount == 1)
	{
		free(pList->headerNode);
		pList->headerNode = NULL;
	}
	else
	{
		prevListNode = getLLElement(pList, prev_idx);
		delListNode = prevListNode->pLink;
		prevListNode->pLink = prevListNode->pLink->pLink;
		free(delListNode);
		// dangling 방지를 할 필요가 있는가?// dangling 방지를 할 필요가 있는가?
		delListNode = NULL;
		
	}
	pList->currentElementCount--;
	return (TRUE);
}

void clearLinkedList(LinkedList* pList)
{
	/*
		전부 NULL처리
		currentElementCount 0으로 바꾸어야하는가?
		
	*/
	if (pList == NULL || pList->currentElementCount <= 0)
		// exit(EXIT_FAILURE);
		return ;
	while (pList->currentElementCount)
		removeLLElement(pList, 0);
}

void deleteLinkedList(LinkedList** pList)
{
	/*
		전부 free
		하나하나 방문 끝까지
		풀고 다음으로
		void type일때 처리
		exit(EXIT_FAILURE);
		그런데 void가 아닐때 별도 처리하게 하면 일관성이 없다.
		어떻게 하는게 좀더 일관적이면 나을 것인가?
	*/
	clearLinkedList(*pList);
	free(*pList);
	// pList->headerNode = malloc(sizeof(ListNode));
	// pList->headerNode->data = 42;
	*pList = NULL;
}

static LinkedList	*reverseLinkedList(LinkedList* pList)
{
	LinkedList	*reversedLinkedList;
	ListNode	*curListNode;
	ListNode	*prevListNode;

	if (pList == NULL)
		return (NULL);
	reversedLinkedList = createLinkedList();
	prevListNode = NULL;
	curListNode = NULL;

	// getLLElement(LinkedList* pList, int position)
	while (curListNode)
	{
		curListNode = curListNode->pLink;
		prevListNode->pLink = prevListNode;
		prevListNode = 
		curListNode->pLink = prevListNode;
		
		prevListNode = curListNode;
	}
	return (reversedLinkedList);
}

void	displayLinkedList(LinkedList* pList)
{
	ListNode*	curListNode;

	// pList->headerNode == NULL 왜 error인가?
	if (pList == NULL || pList->currentElementCount <= 0)
		return ;
		// exit(EXIT_FAILURE);
	printf("pList->currentElementCount : %d\n", pList->currentElementCount);
	curListNode = pList->headerNode;
	printf("display linked list : \n");
	while (curListNode->pLink)
	{
		printf("%d -> ", curListNode->data);
		curListNode = curListNode->pLink;
	}
	printf("%d\n", curListNode->data);
}


/*

메모리가 한정적일떄도 linked list
필요할때마다 연결 가능하니까
arraylist는 미리 할당해줘야하고
사이즈업할때 2배 이상의 공간이 필요하게 된다.

어디에 쓸 것인지
왜 쓰이는지

문제해결
- 회원관리
-
-
-

DS 배우는 이유
- 왜 공부하는지
- 어떤 형식으로 관리할 것인가?
- 메모리에 검색용?
- management용으로 쓸것인지?
- 메모리에서 유지할 것이냐
- 자료구조의 핵심
- 어디에 쓸것인지에 따라 달라진다.
- stack
	- 프링글스
	- 최근 자료를 꺼내고 집어넣을때
	- game save, 무르기

- queue
	- 선착순
	- 아이스크림 대기열
	- 
- 어떤 라이브러리로 구현되어있는가?
- 공부를 좀더 폭넓게


- 다음주 분량

- double linked list
	- array 보다는 몇번째 것을 찾아가는데 operation이 있을것이다
- 역순만들기
	- doulbe, single상관없다.
	- pseudo code
	- single인 상태 code
	- reverse
	- 
- 다항식의 덧셈
	- degree가 같으면 더한다.
	- 각 항을 linked list element로 둔다.
	- coef, degree, link
	- 

*/

