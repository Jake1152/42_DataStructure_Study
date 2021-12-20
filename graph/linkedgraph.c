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
	LinkedGraph*	mainLinkedGraph;
	int				maxVertexCount;
	int				graphType;

	maxVertexCount = 7;
	graphType = GRAPH_UNDIRECTED;
	mainLinkedGraph = createLinkedGraph(maxVertexCount, graphType);
	// mainLinkedGraph

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

	if (maxVertexCount <= 0 || graphType < GRAPH_UNDIRECTED \
		|| graphType > GRAPH_DIRECTED)
		return (NULL);
	newLinkedGraph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	if (newLinkedGraph == NULL)
		return (NULL);
	// vertex갯수만큼 linkedlist 1차원 배열의 사이즈 정해서 동적할당
	// vertex에다가 연결될 node를 표현하므로 맨처음 create에서 처리
	/* e.g)
	 ㅁ -> ㅁㅁㅁ
	 ㅁ -> ㅁㅁㅁㅁㅁ
	 ㅁ -> ㅁㅁㅁㅁㅁㅁㅁㅁ
	 ㅁ -> ㅁ
	 ㅁ -> NULL	
	*/
	// maxVertexCount 개수만큼 newLinkedList 만들어준다.
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);	
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
	/*
	- 실패하는 경우 이전에 할당한 1차원 linked list free
	- 2차원linked list pointer free
	- graph또한 free
	*/
	if (newVertex == NULL)
	{
		for (int i = 0; i < maxVertexCount; i++)
			free(newLinkedGraph->ppAdjEdge[i]);
		free(newLinkedGraph->ppAdjEdge);
		free(newLinkedGraph);
		return (NULL);
	}	
	newLinkedGraph->pVertex = newVertex;
	newLinkedGraph->maxVertexCount = maxVertexCount;
	newLinkedGraph->currentVertexCount = 0;
	newLinkedGraph->currentEdgeCount = 0;
	newLinkedGraph->graphType = graphType;
	return (newLinkedGraph);
}

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL || pGraph->currentVertexCount)
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
	ListNode 	ListNodeElement;
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			addElement_status;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// 무방향 그래프일때, 양방향 연결
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		// idx는 해당 노드 fromVertexID, toVertexID
		// fromVertexID_idx 찾기 및 fromVertexID -> toVertexID 연결
		if (chainingEdge(pGraph, fromVertexID, toVertexID) == FALSE)
			return (FALSE);
		// toVertexID 찾기 및 toVertexID -> fromVertexID 연결
		if (chainingEdge(pGraph, toVertexID, fromVertexID) == FALSE)
			return (FALSE);
	}
	//	방향그래프일떄, 단방향으로만 연결
	else if (pGraph->graphType == GRAPH_DIRECTED)
	{
		if (chainingEdge(pGraph, fromVertexID, toVertexID) == FALSE)
			return (FALSE);
	}
	else
	{
		printf("undefined Graph Type.\n");
		return (FALSE);
	}
	return (pGraph->currentEdgeCount);
}

int	chainingEdge(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	int			fromVertexID_idx;
	int			addElement_status;
	ListNode	ListNodeElement;

	for (int i = 0; i<pGraph->currentVertexCount; i++)
	{
		if (pGraph->ppAdjEdge[i]->header.data == fromVertexID)
		{
			fromVertexID_idx = i;
			break ;
		}
	}
	ListNodeElement.data = toVertexID;
	// ㅁ -> ㅁㅁㅁㅁ 연결리스트 구현된 함수를 이용히여 새로운 엣지를 맨 뒤에 연결되도록 한다
	// 파라미터 pList, position, element 순서
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
					pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount, \
					ListNodeElement);
	pGraph->currentEdgeCount++;
	return (addElement_status);
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
		LinkedList** ppAdjEdge;	// 
		// 1차원에 대해서 index받는 용도

		LinkedList** ppAdjEdge;에서 어떻게 넘겨받을 것인가?
		* ppAdjEdge 이렇게하면   1. 케이스이다.
		원하는 것은 세로 줄 즉, 노드들의 header를 가리킬 그곳이다.
		밖에서 findGraphNodePosition(pGraph->ppAdjEdge) 이렇게 넘길 수있는가?
		하지만 pGraph->ppAdjEdge 이중포인터라서 안맞을거 같다.
		그렇다고 하지만 pGraph->ppAdjEdge 싱글 포인터로 넘기는건 모르곘다.
		1, ㅁ -> ㅁㅁㅁㅁ
		ㅁ
		ㅁ
		ㅁ
	*/
	LinkedList* pCurList;

	pCurList = pList;
	if (pList == NULL)
		return (FALSE);
	// pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	if (pList->headerNode.data == vertexID)
	
}

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		노드별로 연결된 것들 출력
		하지만 방향성 여부에 따라 다르게 출력
		어떤 순서로 연결되어있는지?
		방향성 상관없이 출력.
	*/
	LinkedList*	curLinkedList;
	if (pGraph == NULL || pGraph->maxVertexCount <= 0 || \
		pGraph->currentVertexCount <= 0 || \
		pGraph->currentEdgeCount <= 0)
	{
		printf("displayLinkedGraph do not display, cause there are nothing.\n");
		exit(EXIT_FAILURE);
	}
	curLinkedList = pGraph->ppAdjEdge;
	while (curLinkedList->)

		
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
