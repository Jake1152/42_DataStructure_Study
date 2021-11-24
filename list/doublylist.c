#include <stdio.h>

#include "doublylist.h"

int main()
{

	return (0);
}

DoublyList* createDoublyList()
{
	/*
		lLink
		rLink
		data초기화는?x
	*/
	DoublyList*		newDoublyList;
	DoublyListNode	newDoublyListNode;
	// newDoublyListNode *가 안붙어도 되는가?

	newDoublyListNode.pLLink = NULL;
	newDoublyListNode.pRLink = NULL;
	newDoublyList->headerNode = newDoublyListNode;

	return (newDoublyList);
}

void displayDoublyList(DoublyList* pList)
{
	DoublyListNode	*curDoublyListNode;

	if (pList == NULL)
		return ;
	curDoublyListNode = &(pList->headerNode);
	while (curDoublyListNode)
	{
		printf("%d ", curDoublyListNode->data);
		curDoublyListNode = curDoublyListNode->pRLink;
	}
}

int getDoublyListLength(DoublyList* pList)
{
	if (pList == NULL)
		return (FALSE);
	return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
	/*
		양방향으로 연결 되어있으니까 어디로 접근하는게 빠를지 생각해보는것도 좋을거 같다.
		원형과 차이는 무엇이라고 할 수 있는가?
		어디가 진짜 head인가?
		head가 가리키는 곳은 어디인가?
		마지막에 추가되는 것?
	*/
	DoublyListNode	*curDoublyListNode;

	if (pList == NULL)
		return ;
	return (curDoublyListNode);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
	/*
		원형 연결리스트 구현시 새 노드를 헤더가 가리키게 하는 방식이 있었다.
		양뱡향일때는 어떻게 해야하는가?
		동일한가?
	*/

}

void deleteDoublyList(DoublyList* pList)
{
	/*
	
	*/
}

int removeDLElement(DoublyList* pList, int position)
{

}

void clearDoublyList(DoublyList* pList)
{

}
