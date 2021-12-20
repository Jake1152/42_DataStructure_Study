#include "linkedgraph.h"
#include <stdlib.h>
#include <stdio.h>

/*
	- �׷����� ���� �� ����� �ȴٸ�?
		�׷� ���� ���� �ȵǴ°�?
		�׷��ٸ� graph�� �ѹ� �����Ҷ� �����°�?
	- direc, undirec ������ ��� �� ���ΰ�?
*/

int main(void)
{
	printf("\n");
	return (0);
}

// �׷��� ����
LinkedGraph* createLinkedGraph(int maxVertexCount, int graphType)
{
	LinkedGraph*	newLinkedGraph;
	LinkedList**	newLinkedListPtr;
	int*			newVertex;

	newLinkedGraph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	if (newLinkedGraph == NULL)
		return (NULL);
	newLinkedGraph->maxVertexCount = maxVertexCount;
	newLinkedGraph->currentVertexCount = 0;
	newLinkedGraph->currentEdgeCount = 0;
	newLinkedGraph->graphType = graphType;
	// vertex������ŭ linkedlist 1���� �迭�� ������ ���ؼ� �����Ҵ�
	// vertex���ٰ� ����� node�� ǥ���ϹǷ� ��ó�� create���� ó��
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);
	/*
		�� 
		��
		��
	*/
	// maxVertexCount ������ŭ newLinkedList 
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
	newLinkedGraph->ppAdjEdge = newLinkedListPtr;
	newVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	if (newVertex == NULL)
	{
		free(newLinkedGraph);
		free(newLinkedListPtr);
		return (NULL);
	}
	newLinkedGraph->pVertex = newVertex;
	return (newLinkedGraph);
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
	int*	newVertex;
	int		idx;

	if (pGraph == NULL)
		return (FALSE);
	// maxVertexCount�̻��� ���, reallocation maxVertexCount 2��� ������Ű��
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
	{
		return (FALSE);
		/*
		newVertex = (int*)malloc(sizeof(int) * pGraph->maxVertexCount * 2);
		if (newVertex == NULL)
			return (NULL);
		idx = 0;
		while (pGraph->currentVertexCount)
		{
			newVertex[idx] = pGraph->pVertex[idx];
			idx++;
		}
		free(pGraph->pVertex);
		pGraph->pVertex = newVertex;
		pGraph->maxVertexCount = pGraph->maxVertexCount * 2;
		*/
	}
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	// vertexID find in ppAdjEdge
	pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	pGraph->currentVertexCount++;
	return (pGraph->currentVertexCount);
}

// ���� �߰�
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	LinkedList*	newLinkedList;
	ListNode*	curListNode;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	/*
		linked list�� �̿��ϴ� ���
		from���� to�� �߰�
		from�� ��� ã�°�?
		�ߺ��� ����� ���ΰ�?
		�Ű�Ⱦ��� �ߺ��ϰ� ������ΰ�?
		2������ ppAdjEdge���� from vertex�� ã�´�.
		from�� to vertex�� �߰��Ѵ�.
		Linked List �ȿ� Linked List�� �ִ�.
		�� -> ����
		�� -> ��������
		�� -> ������������
		�� -> ������
		�� -> ����������
		�� -> ����
	*/
	curListNode = pGraph->ppAdjEdge->headerNode;
	// curListNode�� ���°�� ó���� ����� ���ΰ�?
	// ���� �Լ��� ���°� ���� ������ ����
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
		directed ������ ����
	*/
	// null guard, from, to vertex���� �ִ��� Ȯ��
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	if (pGraph->graphType)

	return (pGraph->currentEdgeCount);
}

// ����� ��ȿ�� ����.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		��ȿ���̶� �����ΰ�?
		��ȯ�ϴ��� �ƴ��� �κ�?
		used, not used
		- �����ü�� �ִ���		
		- �������϶�
		  ���� ����Ǿ��ִ���
	*/
	int idx;

	if (pGraph == NULL)
		return (FALSE);
	idx = 0;
	// vertexID�� 0���� ��������� ������ ����. pVertex[idx]�� �и��ؼ� ����
	while (pGraph->currentVertexCount > idx)
	{
		if (pGraph->pVertex[idx] == vertexID)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

// ��� ����
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	return (pGraph->currentVertexCount);
	// NOT_USED�� ����
}

// ���� ����
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

// �׷��� ����
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
		int *pVertex;			// index �޴� �뵵
	*/
}

// �׷��� ���� ���
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		��庰�� ����� �͵� ���
		������ ���⼺ ���ο� ���� �ٸ��� ���
		� ������ ����Ǿ��ִ���?
	*/
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
