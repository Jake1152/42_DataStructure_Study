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

// �׷��� ����
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
	// vertex������ŭ linkedlist 1���� �迭�� ������ ���ؼ� �����Ҵ�
	// vertex���ٰ� ����� node�� ǥ���ϹǷ� ��ó�� create���� ó��
	/* e.g)
	 �� -> ������
	 �� -> ����������
	 �� -> ����������������
	 �� -> ��
	 �� -> NULL	
	*/
	// maxVertexCount ������ŭ newLinkedList ������ش�.
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);	
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
	// maxVertexCount ������ŭ ppAdjEdge�� �߰��� LinkedList* �Ҵ�
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
	// Vertex �߰� 1���� array list
	newVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	/*
	- �����ϴ� ��� ������ �Ҵ��� 1���� linked list free
	- 2����linked list pointer free
	- graph���� free
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

// ���� �׷��� ���� �Ǵ�
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL || pGraph->currentVertexCount)
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
	// maxVertexCount �̻��̸� False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	// ���� ���� vertexID�� currentVertexCount index�� �־ vertexID�� headerNode data�� �߰��Ѵ�.
	pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	pGraph->currentVertexCount++;
	return (pGraph->currentVertexCount);
}

// ���� �߰�
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
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
	ListNode 	ListNodeElement;
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			addElement_status;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// ������ �׷����϶�, ����� ����
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		// idx�� �ش� ��� fromVertexID, toVertexID
		// fromVertexID_idx ã�� �� fromVertexID -> toVertexID ����
		if (chainingEdge(pGraph, fromVertexID, toVertexID) == FALSE)
			return (FALSE);
		// toVertexID ã�� �� toVertexID -> fromVertexID ����
		if (chainingEdge(pGraph, toVertexID, fromVertexID) == FALSE)
			return (FALSE);
	}
	//	����׷����ϋ�, �ܹ������θ� ����
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
	// �� -> �������� ���Ḯ��Ʈ ������ �Լ��� �̿����� ���ο� ������ �� �ڿ� ����ǵ��� �Ѵ�
	// �Ķ���� pList, position, element ����
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
		LinkedList** ppAdjEdge;	// 
		// 1������ ���ؼ� index�޴� �뵵

		LinkedList** ppAdjEdge;���� ��� �Ѱܹ��� ���ΰ�?
		* ppAdjEdge �̷����ϸ�   1. ���̽��̴�.
		���ϴ� ���� ���� �� ��, ������ header�� ����ų �װ��̴�.
		�ۿ��� findGraphNodePosition(pGraph->ppAdjEdge) �̷��� �ѱ� ���ִ°�?
		������ pGraph->ppAdjEdge ���������Ͷ� �ȸ����� ����.
		�׷��ٰ� ������ pGraph->ppAdjEdge �̱� �����ͷ� �ѱ�°� �𸣁ٴ�.
		1, �� -> ��������
		��
		��
		��
	*/
	LinkedList* pCurList;

	pCurList = pList;
	if (pList == NULL)
		return (FALSE);
	// pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	if (pList->headerNode.data == vertexID)
	
}

// �׷��� ���� ���
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		��庰�� ����� �͵� ���
		������ ���⼺ ���ο� ���� �ٸ��� ���
		� ������ ����Ǿ��ִ���?
		���⼺ ������� ���.
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
