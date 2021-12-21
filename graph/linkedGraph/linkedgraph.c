#include "linkedgraph.h"
#include "linkedList.h"
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
	int*		newVertex;
	int			idx;
	int			addElement_status;
	ListNode	ListNodeElement;

	printf("in addVertexLG\n");
	if (pGraph == NULL)
		return (FALSE);
	printf("1\n");
	// maxVertexCount �̻��̸� False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	printf("2\n");
	// ���� ���� vertexID�� currentVertexCount index�� �־ vertexID�� headerNode data�� �߰��Ѵ�.
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

	fromVertexID_idx = findGraphNodePosition(pGraph, fromVertexID);
	if (fromVertexID_idx == -1)
			return (FALSE);
	ListNodeElement.data = toVertexID;
	// �� -> �������� ���Ḯ��Ʈ ������ �Լ��� �̿����� ���ο� ������ �� �ڿ� ����ǵ��� �Ѵ�
	// �Ķ���� pList, position, element ����
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
					pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount, \
					ListNodeElement);
	pGraph->currentEdgeCount++;
	return (addElement_status);
}

// weighted�� �ϸ� ����ü�� �����ؾ��� ������ ����. �ϴ� ����
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
	/*
		Node�� �����ϸ� ����� ��ũ�� �� ����
		���� ����� ������ ã�´�.
	*/
	int			vertexID_idx;
	ListNode*	curListNode;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	vertexID_idx = findGraphNodePosition(pGraph, vertexID);
	if (vertexID_idx == -1)
		return (FALSE);
	curListNode = pGraph->ppAdjEdge[vertexID_idx]->headerNode;
	// ������
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		while (curListNode->pLink)
		{
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);
			removeEdgeLG(pGraph, curListNode->pLink->data,vertexID_idx);
			curListNode = curListNode->pLink;
		}
	}
	// ����
	else
	{
		while (curListNode->pLink)
		{
			// ���� �� ���忡�� ����� ������ ����
			// �ٸ� �������� ���� ����Ű�� ���� ��� �ϴ°�?
			// ������ ã�Ƽ� �����Ѵ�?
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);			
			curListNode = curListNode->pLink;
		}
	}
	// �� ������ ��ȸ�� ã�� ������ NOT_USEDó��
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (vertexID == pGraph->pVertex[i])
			pGraph->pVertex[i] = NOT_USED;
	}
	// pGraph->currentVertexCount �����ϸ� �ڿ��ִ� idx�� ���� ���� �� �ִ�.
	// ������ҷ��� array list resize�ϰų�
	// vertex���嵵 linked list�� �Ѵ�
	// removeEdgeLG(pGraph, int fromVertexID, int toVertexID)
	pGraph->currentVertexCount--;
	return ( pGraph->currentVertexCount);
	// NOT_USED�� ����
}

// ���� ����
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		�߰��ҋ�ó�� �������� ���ο� ���� ����
	*/
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			removeElement_status;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// ������
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
	// ����
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
		�� �Ķ���Ͱ� LinkedList�ΰ�?
		��������ϴ� vertex�� ����� link�� �����.
		�׷��� ���� �� ���Ͽ��� removeEdge�� ��ģ��.
		�׷��Ƿ� ���� �������� �ʴ´�.
	*/
	if (pList == NULL)
		exit(EXIT_FAILURE);	
}

// �׷��� ����
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

// �׷��� ���� ���
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		��庰�� ����� �͵� ���
		������ ���⼺ ���ο� ���� �ٸ��� ���
		� ������ ����Ǿ��ִ���?
		���⼺ ������� ���.
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
	{
		if (checkVertexValid(pGraph, pGraph->ppAdjEdge[idx]) == TRUE)
			displayLinkedList(pGraph->ppAdjEdge[idx]);
	}
		
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
