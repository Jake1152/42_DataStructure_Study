#ifndef _HEAP_
#define _HEAP_

typedef struct HeapNodeType
{
	int key;
	char value;

	struct HeapNodeType* pLeftChild;
	struct HeapNodeType* pRightChild;
} HeapNode;

typedef struct HeapType
{
	HeapNode *pRootNode;
} Heap;


/*

- heap, priorty queue

- max heap, --min heap--
	- flag로 표현?
	- 처음에 create할때 적용?
	- insert할때 적용?
	- 이미 min인것을 max로 변경할려면 해당 함수도 넣어야하는가?

- createArrayHeap
	- Queue Array 이용
- clearArrayHeap
	- Array 포인터가 가리키는 공간을 free
- deleteArrayHeap
	- Array 포인터가 가리키는 공간과 가리키던 포인터도 free
- addALHeapElement
	- 완전이진트리
	- 1/2인거 이용
	- 권오흠님 강의 참고
- removeALHeapElement
	- 권오흠님 강의 참고
	- 3가지 경우
		- 단말
		- 자식 1개
		- 2개
	- heapify
- reverseHeap
	- min, max를 바뀌줌
	- 어떻게 heapify해야하는가?

- heapify
	- min, max인지에 따라 맞춤

*/