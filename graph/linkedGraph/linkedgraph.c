#include "linkedgraph.h"
#include "linkedList.h"
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

	addVertexLG(mainLinkedGraph, 0);
	printf("after 1\n");
	addEdgeLG(mainLinkedGraph, 0, 1);
	printf("after 2\n");
	addEdgeLG(mainLinkedGraph, 0, 2);
	printf("after 3\n");

	// addVertexLG(mainLinkedGraph, 1);
	// addEdgeLG(mainLinkedGraph, 1, 2);

	// addVertexLG(mainLinkedGraph, 2);
	// addEdgeLG(mainLinkedGraph, 2, 3);

	// addVertexLG(mainLinkedGraph, 3);
	// addEdgeLG(mainLinkedGraph, 3, 4);

	// addVertexLG(mainLinkedGraph, 4);
	// addEdgeLG(mainLinkedGraph, 4, 5);

	// addVertexLG(mainLinkedGraph, 5);
	// addEdgeLG(mainLinkedGraph, 5, 3);

	displayLinkedGraph(mainLinkedGraph);
	
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
		newLinkedList = createLinkedList();
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
	// newLinkedGraph->ppAdjEdge = newLinkedListPtr;
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
	int*		newVertex;
	int			idx;
	int			addElement_status;
	ListNode	ListNodeElement;

	printf("in addVertexLG\n");
	if (pGraph == NULL)
		return (FALSE);
	printf("1\n");
	// maxVertexCount 이상이면 False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	printf("2\n");
	// 새로 들어온 vertexID를 currentVertexCount index에 넣어서 vertexID는 headerNode data에 추가한다.
	ListNodeElement.data = vertexID;
	printf("3\n");
	addElement_status = addLLElement(pGraph->ppAdjEdge[pGraph->currentVertexCount], \
					pGraph->ppAdjEdge[pGraph->currentVertexCount]->currentElementCount, \
					ListNodeElement);
	printf("addElement_status : %d\n", addElement_status);
	if (addElement_status == FALSE)
		return (FALSE);
	printf("4\n");
	pGraph->currentVertexCount++;
	printf("5\n");
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

	fromVertexID_idx = findGraphNodePosition(pGraph, fromVertexID);
	if (fromVertexID_idx == -1)
			return (FALSE);
	ListNodeElement.data = toVertexID;
	// ㅁ -> ㅁㅁㅁㅁ 연결리스트 구현된 함수를 이용히여 새로운 엣지를 맨 뒤에 연결되도록 한다
	// 파라미터 pList, position, element 순서
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
					pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount, \
					ListNodeElement);
	pGraph->currentEdgeCount++;
	return (addElement_status);
}

// weighted로 하면 구조체를 변경해야할 것으로 생각. 일단 보류
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
	/*
		Node를 제거하면 연결된 링크도 다 제거
		나와 연결된 노드들을 찾는다.
	*/
	int			vertexID_idx;
	ListNode*	curListNode;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	vertexID_idx = findGraphNodePosition(pGraph, vertexID);
	if (vertexID_idx == -1)
		return (FALSE);
	curListNode = pGraph->ppAdjEdge[vertexID_idx]->headerNode;
	// 무방향
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		while (curListNode->pLink)
		{
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);
			removeEdgeLG(pGraph, curListNode->pLink->data,vertexID_idx);
			curListNode = curListNode->pLink;
		}
	}
	// 방향
	else
	{
		while (curListNode->pLink)
		{
			// 현재 내 입장에서 연결된 간선만 제거
			// 다른 정점에서 나를 가리키는 경우는 어떻게 하는가?
			// 일일이 찾아서 제거한다?
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);			
			curListNode = curListNode->pLink;
		}
	}
	// 내 정점을 순회로 찾은 다음에 NOT_USED처리
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (vertexID == pGraph->pVertex[i])
			pGraph->pVertex[i] = NOT_USED;
	}
	// pGraph->currentVertexCount 변경하면 뒤에있는 idx를 참조 못할 수 있다.
	// 제대로할려면 array list resize하거나
	// vertex저장도 linked list로 한다
	// removeEdgeLG(pGraph, int fromVertexID, int toVertexID)
	pGraph->currentVertexCount--;
	return ( pGraph->currentVertexCount);
	// NOT_USED로 변경
}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		추가할떄처럼 방향인지 여부에 따라 나눔
	*/
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			removeElement_status;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// 무방향
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		// fromVertexID -> toVertexID
		fromVertexID_idx = findGraphNodePosition(pGraph, fromVertexID);
		if (fromVertexID_idx == -1)
			return (FALSE);
		removeElement_status = removeLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
						pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount);
		if (removeElement_status == FALSE)
			return (FALSE);
		pGraph->currentEdgeCount--;

		// toVertexID -> fromVertexID
		toVertexID_idx = findGraphNodePosition(pGraph, toVertexID);
		if (toVertexID_idx == -1)
			return (FALSE);
		removeElement_status = removeLLElement(pGraph->ppAdjEdge[toVertexID_idx], \
						pGraph->ppAdjEdge[toVertexID_idx]->currentElementCount);
		if (removeElement_status == FALSE)
			return (FALSE);
		pGraph->currentEdgeCount--;
	}
	// 방향
	else if (pGraph->graphType == GRAPH_DIRECTED)
	{
		// fromVertexID -> toVertexID
		fromVertexID_idx = findGraphNodePosition(pGraph, fromVertexID);
		if (fromVertexID_idx == -1)
			return (FALSE);
		removeElement_status = removeLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
						pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount);
		if (removeElement_status == FALSE)
			return (FALSE);
		pGraph->currentEdgeCount--;
	}
	else
	{
		printf("undefined graph type.\n");
		exit(EXIT_FAILURE);
	}
	
	return (pGraph->currentEdgeCount);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
	/*
		왜 파라미터가 LinkedList인가?
		지우고자하는 vertex와 연결된 link를 지운다.
		그러면 현재 이 파일에서 removeEdge와 겹친다.
		그러므로 별도 구현하지 않는다.
	*/
	if (pList == NULL)
		exit(EXIT_FAILURE);	
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{
	int	idx;
	if (pGraph == NULL || isEmptyLG(pGraph))
		exit(EXIT_FAILURE);
	idx = 0;
	while (pGraph->currentVertexCount > 0)
	{
		removeVertexLG(pGraph,pGraph->pVertex[idx]);
		idx++;
	}
	for (int i=0; i<pGraph->maxVertexCount; i++)
		free(pGraph->ppAdjEdge[i]);
	free(pGraph->ppAdjEdge);
	free(pGraph->pVertex);
	free(pGraph);
	pGraph = NULL;
}

int findGraphNodePosition(LinkedGraph* pGraph, int vertexID)
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
	int	vertexID_idx;

	if (pGraph == NULL || checkVertexValid(pGraph, vertexID) == FALSE)
		return (-1);
	for (int i = 0; i< pGraph->currentVertexCount; i++)
	{
		if (pGraph->ppAdjEdge[i]->headerNode->data == vertexID)
		{
			vertexID_idx = i;
			break ;
		}
	}
	return (vertexID_idx);	
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
	printf("in displayLinkedGraph \n");
	if (pGraph == NULL || pGraph->maxVertexCount <= 0 || \
		pGraph->currentVertexCount <= 0 || \
		pGraph->currentEdgeCount <= 0)
	{
		printf("displayLinkedGraph do not display, cause there are nothing.\n");
		exit(EXIT_FAILURE);
	}
	printf("display linked graph : \n\n");
	for (int idx = 0; idx < pGraph->currentVertexCount; idx++)
		displayLinkedList(pGraph->ppAdjEdge[idx]);
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
