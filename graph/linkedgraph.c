#include "linkedgraph.h"
#include "../list/linkedList.h"
#include <stdlib.h>

// �׷��� ����
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

// �׷��� ����
void deleteLinkedGraph(LinkedGraph* pGraph)
{

}

// ���� �׷��� ���� �Ǵ�
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

// ��� �߰�
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{

}

// ���� �߰�
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{

}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{

}

// ����� ��ȿ�� ����.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		��ȿ���̶� �����ΰ�?
		��ȯ�ϴ��� �ƴ��� �κ�?
	*/
}

// ��� ����
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{

}

// ���� ����
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{

}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{

}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{

}

// ���� ���� ��ȯ
int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// ��� ���� ��ȯ
int getVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

// �ִ� ��� ���� ��ȯ
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

// �׷��� ���� ��ȯ.
int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->graphType);
}

// �׷��� ���� ���
void displayLinkedGraph(LinkedGraph* pGraph)
{

}
