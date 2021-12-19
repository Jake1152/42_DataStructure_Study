#include "linkedgraph.h"
#include "../list/linkedList.h"
#include <stdlib.h>

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount, int graphType)
{
	LinkedGraph*	newLinkedGraph;

	newLinkedGraph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	if (newLinkedGraph == NULL)
		return (NULL);
	newLinkedGraph->maxVertexCount = maxVertexCount;
	newLinkedGraph->currentVertexCount = 0;
	newLinkedGraph->currentEdgeCount = 0;
	newLinkedGraph->graphType = graphType;
	newLinkedGraph->ppAdjEdge = NULL;
	newLinkedGraph->pVertex = NULL;
	return (newLinkedGraph);
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{

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

}

// 간선 추가
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{

}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{

}

// 노드의 유효성 점검.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		유효성이란 무엇인가?
		순환하는지 아닌지 부분?
	*/
}

// 노드 제거
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{

}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{

}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{

}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{

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

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{

}
