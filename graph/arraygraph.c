#include "arraygraph.h"
#include <stdlib.h>

// �׷��� ����
ArrayGraph* createArrayGraph(int maxVertexCount, int graphType)
{
	/*
		**ppAdjEdge,  *pVertex �����Ҵ� ������ϴ°�?
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

// �׷��� ����
void deleteArrayGraph(ArrayGraph* pGraph)
{
	
}

// ���� �׷��� ���� �Ǵ�
int isEmptyAG(ArrayGraph* pGraph)
{
	
}

// ��� �߰�
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	
}

// ���� �߰�
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	
}

// ����� ��ȿ�� ����.
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	
}

// ��� ����
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	
}

// ���� ����
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	
}

// �׷��� ���� ���
void displayArrayGraph(ArrayGraph* pGraph)
{
	/*
	 * 	
	 * 
	 * 
	*/
}
