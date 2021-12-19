#include "arraygraph.h"
#include <stdlib.h>

// 그래프 생성
ArrayGraph* createArrayGraph(int maxVertexCount, int graphType)
{
	/*
		**ppAdjEdge,  *pVertex 동적할당 해줘야하는가?
	*/
	ArrayGraph*	newArrayGraph;

	newArrayGraph = (ArrayGraph*)malloc(sizeof(ArrayGraph));
	if (newArrayGraph == NULL)
		return (NULL);
	newArrayGraph->maxVertexCount = maxVertexCount;
	newArrayGraph->currentVertexCount = 0;
	newArrayGraph->graphType = graphType;
	return (newArrayGraph);
}

// 그래프 삭제
void deleteArrayGraph(ArrayGraph* pGraph)
{
	
}

// 공백 그래프 여부 판단
int isEmptyAG(ArrayGraph* pGraph)
{
	
}

// 노드 추가
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	
}

// 간선 추가
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	
}

// 노드의 유효성 점검.
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	
}

// 노드 제거
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	
}

// 간선 제거
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	
}

// 그래프 정보 출력
void displayArrayGraph(ArrayGraph* pGraph)
{
	/*
	 * 	
	 * 
	 * 
	*/
}
