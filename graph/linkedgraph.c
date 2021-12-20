#include "linkedgraph.h"
#include <stdlib.h>
#include <stdio.h>

/*
	- 그래프가 따로 두 덩어리가 된다면?
		그런 경우는 말이 안되는가?
		그렇다면 graph는 한번 선언할때 끝나는가?
	- direc, undirec 구분은 어떻게 할 것인가?
*/

int main(void)
{
	printf("\n");
	return (0);
}

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount, int graphType)
{
	LinkedGraph*	newLinkedGraph;
	LinkedList**	newLinkedListPtr;
	LinkedList*		newLinkedList;
	int*			newVertex;

	newLinkedGraph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	if (newLinkedGraph == NULL)
		return (NULL);
	newLinkedGraph->maxVertexCount = maxVertexCount;
	newLinkedGraph->currentVertexCount = 0;
	newLinkedGraph->currentEdgeCount = 0;
	newLinkedGraph->graphType = graphType;
	// vertex갯수만큼 linkedlist 1차원 배열의 사이즈 정해서 동적할당
	// vertex에다가 연결될 node를 표현하므로 맨처음 create에서 처리
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);
	// maxVertexCount 개수만큼 newLinkedList 
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
	// maxVertexCount 갯수만큼 ppAdjEdge에 추가될 LinkedList* 할당
	for (int i = 0; i < maxVertexCount; i++)
	{
		newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
		if (newLinkedList == NULL)
		{
			free(newLinkedGraph);
			free(newLinkedListPtr);
			for (int j = 0; j < i; j++)
				free(newLinkedListPtr[j]);
			return (NULL);
		}
		newLinkedListPtr[i] = newLinkedList;
	}
	newLinkedGraph->ppAdjEdge = newLinkedListPtr;
	// Vertex 추가 1차원 array list
	newVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	if (newVertex == NULL)
	{
		for (int i = 0; i < maxVertexCount; i++)
			free(newLinkedGraph->ppAdjEdge[i]);
		free(newLinkedGraph->ppAdjEdge);
		free(newLinkedGraph);
		return (NULL);
	}	
	newLinkedGraph->pVertex = newVertex;
	return (newLinkedGraph);
}

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

// 노드 추가
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int*	newVertex;
	int		idx;

	if (pGraph == NULL)
		return (FALSE);
	// maxVertexCount 이상이면 False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	// 새로 들어온 vertexID를 currentVertexCount index에 넣어서 vertexID는 headerNode data에 추가한다.
	pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	pGraph->currentVertexCount++;
	return (pGraph->currentVertexCount);
}

// 간선 추가
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	LinkedList*	newLinkedList;
	ListNode*	curListNode;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	/*
		linked list를 이용하는 방법
		from에서 to에 추가
		from을 어떻게 찾는가?
		중복은 어떻게할 것인가?
		신경안쓰고 중복하게 만들것인가?
		2차원인 ppAdjEdge에서 from vertex를 찾는다.
		from에 to vertex를 추가한다.
		Linked List 안에 Linked List가 있다.
		ㅁ -> ㅁㅁ
		ㅁ -> ㅁㅁㅁㅁ
		ㅁ -> ㅁㅁㅁㅁㅁㅁ
		ㅁ -> ㅁㅁㅁ
		ㅁ -> ㅁㅁㅁㅁㅁ
		ㅁ -> ㅁㅁ
	*/
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		ListNode*	newLinkedNode;
		// idx는 해당 노드 fromVertexID, toVertexID
		// node malloc 하여 값을 추가한 뒤 
		newLinkedNode = malloc(sizeof(ListNode));
		if (newLinkedNode == NULL)
			return (NULL);
		newLinkedNode->data = toVertexID;
		pGraph->ppAdjEdge[fromVertexID_idx] = newLinkedNode

		newLinkedNode = malloc(sizeof(ListNode));
		if (newLinkedNode == NULL)
			return (NULL);
		// from, to 를 나눠야한다. malloc 실패를 처리한다면.
		// 그리고 다른 부분에 대해서도 free 필요. 별도 함수 필요.
		newLinkedNode->data = toVertexID;
		pGraph->ppAdjEdge[toVertexID_idx] = newLinkedNode
	}
	else if (pGraph->graphType == GRAPH_DIRECTED)

	else
		printf("undefined Graph Type.\n");
	
	curListNode = pGraph->ppAdjEdge->headerNode;
	// curListNode에 없는경우 처리는 어떻게할 것인가?
	// 별도 함수로 뺴는게 나을 것으로 생각
	while (curListNode)
	{
		if (curListNode->data == fromVertexID)
			break ;
		curListNode = curListNode->pLink;
	}
	pGraph->ppAdjEdge = ;
	pGraph->currentEdgeCount++;
	return (pGraph->currentEdgeCount);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	/*
		undirected
		directed 나눠서 진행
	*/
	// null guard, from, to vertex들이 있는지 확인
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	if (pGraph->graphType)

	return (pGraph->currentEdgeCount);
}

// 노드의 유효성 점검.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		유효성이란 무엇인가?
		순환하는지 아닌지 부분?
		used, not used
		- 노드자체가 있는지		
		- 무방향일때
		  서로 연결되어있는지
	*/
	int idx;

	if (pGraph == NULL)
		return (FALSE);
	idx = 0;
	// vertexID가 0부터 있으리라는 보장이 없다. pVertex[idx]와 분리해서 생각
	while (pGraph->currentVertexCount > idx)
	{
		if (pGraph->pVertex[idx] == vertexID)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

// 노드 제거
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	return (pGraph->currentVertexCount);
	// NOT_USED로 변경
}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (pGraph == NULL || isEmptyLG(pGraph) \ 
		|| checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
	if (pList == NULL)
		return (FALSE);
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{
	if (pGraph == NULL || isEmptyLG(pGraph))
		return (NULL);
	deleteGraphNode();

	free(pGraph);
	pGraph = NULL
}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
	/*
		int *pVertex;			// index 받는 용도
	*/
}

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		노드별로 연결된 것들 출력
		하지만 방향성 여부에 따라 다르게 출력
		어떤 순서로 연결되어있는지?
	*/
}

// 간선 개수 반환
int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// 노드 개수 반환
int getVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

// 최대 노드 개수 반환
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

// 그래프 종류 반환.
int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->graphType);
}
