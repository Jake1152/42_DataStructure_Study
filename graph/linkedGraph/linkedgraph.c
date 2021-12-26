#include "linkedgraph.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	LinkedGraph*	pGraph;
	int				maxVertexCount;
	int				graphType;

	maxVertexCount = 7;
	graphType = GRAPH_UNDIRECTED;

	pGraph = createLinkedGraph(6, graphType);
    addVertexLG(pGraph,0);
    addVertexLG(pGraph,1);
    addVertexLG(pGraph,2);
    addVertexLG(pGraph,3);
    addVertexLG(pGraph,4);
    addVertexLG(pGraph,5);
    addEdgeLG(pGraph,0,1);
    addEdgeLG(pGraph,1,2);
    addEdgeLG(pGraph,2,3);
    addEdgeLG(pGraph,2,1);
    addEdgeLG(pGraph,2,0);
    addEdgeLG(pGraph,3,4);
    addEdgeLG(pGraph,3,2);
    addEdgeLG(pGraph,4,5);
    addEdgeLG(pGraph,5,3);
    displayLinkedGraph(pGraph);
    printf("after remove  3, 2\n");
    removeEdgeLG(pGraph,3,2);
    displayLinkedGraph(pGraph);
    printf("after remove  2, 0\n");
    removeEdgeLG(pGraph,2,0);
    displayLinkedGraph(pGraph);
    printf("vertex 총개수\n");
    printf("%d\n", getVertexCountLG(pGraph));
    printf("간선 총 개수 \n");
    printf("%d\n",getEdgeCountLG(pGraph));
    printf("4노드 제거\n");
    removeVertexLG(pGraph,4);
    displayLinkedGraph(pGraph);

	return (0);
}

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
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);	
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
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
	newLinkedGraph->ppAdjEdge = newLinkedListPtr;
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
	newLinkedGraph->maxVertexCount = maxVertexCount;
	newLinkedGraph->currentVertexCount = 0;
	newLinkedGraph->currentEdgeCount = 0;
	newLinkedGraph->graphType = graphType;
	return (newLinkedGraph);
}

int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL || pGraph->currentVertexCount)
		return (FALSE);
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int*		newVertex;
	int			idx;

	if (pGraph == NULL)
		return (FALSE);
	if (vertexID < 0 || vertexID > pGraph->currentVertexCount ||\
		pGraph->pVertex[vertexID] == USED)
		return (FALSE);
	pGraph->pVertex[vertexID] = USED;
	pGraph->currentVertexCount++;
	return (pGraph->currentVertexCount);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	ListNode 	ListNodeElement;
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			addElement_status;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	if (pGraph->graphType != GRAPH_UNDIRECTED && \
		pGraph->graphType != GRAPH_DIRECTED)
		return (FALSE);
	// from -> to linked
	ListNodeElement.data = toVertexID;
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID], \
					pGraph->ppAdjEdge[fromVertexID]->currentElementCount, \
					ListNodeElement);
	if (addElement_status == FALSE)
		return (FALSE);
	// to -> from linked when it is undirected
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		ListNodeElement.data = fromVertexID;
		addElement_status = addLLElement(pGraph->ppAdjEdge[toVertexID], \
						pGraph->ppAdjEdge[toVertexID]->currentElementCount, \
						ListNodeElement);
		if (addElement_status == FALSE)
			return (FALSE);
	}
	pGraph->currentEdgeCount++;
	return (pGraph->currentEdgeCount);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	int idx;

	if (pGraph == NULL || \
		(vertexID < 0 || vertexID >= pGraph->maxVertexCount))
		return (FALSE);
	if (pGraph->pVertex[vertexID] == USED)
		return (TRUE);
	return (FALSE);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int			vertexID_idx;
	ListNode*	curListNode;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	if (pGraph->graphType != GRAPH_UNDIRECTED && pGraph->graphType != GRAPH_DIRECTED)
		return (FALSE);
	while (curListNode && pGraph->ppAdjEdge[vertexID]->currentElementCount)
	{
		/*
			 0 1 2 3 4
			 2 -> 0 3 4 
		*/
		removeEdgeLG(pGraph, vertexID, curListNode->data);
		curListNode = curListNode->pLink;
	}
	pGraph->currentVertexCount--;
	return ( pGraph->currentVertexCount);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	int			removeElement_status;
	int			position;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	if (pGraph->graphType != GRAPH_UNDIRECTED &&\
		 pGraph->graphType != GRAPH_DIRECTED)
		return (FALSE);
	deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		deleteGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
	pGraph->currentEdgeCount--;
	return (pGraph->currentEdgeCount);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
	int	position;

	if (pList == NULL || pList->currentElementCount <= 0)
	{
		printf("there are no graph node to delete\n");
		return ;
	}
	// removeLLElement �ߵǴ��� Ȯ�� �ʿ�
	removeLLElement(pList, position);
}

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

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
	ListNode*	curListNode;
	int			position;

	if (pList == NULL)
		return (-1);
	curListNode = pList->headerNode;
	position = 0;
	while (curListNode)
	{
		if (curListNode->data == vertexID)
			return (position);
		curListNode = curListNode->pLink;
		position++;
	}
	return (-1);
}

void displayLinkedGraph(LinkedGraph* pGraph)
{
	// printf("in displayLinkedGraph \n");
	if (pGraph == NULL || pGraph->maxVertexCount <= 0 || \
		pGraph->currentVertexCount <= 0 || \
		pGraph->currentEdgeCount <= 0)
	{
		printf("displayLinkedGraph do not display, cause there are nothing.\n");
		exit(EXIT_FAILURE);
	}
	// printf("display linked graph : \n\n");
	for (int idx = 0; idx < pGraph->currentVertexCount; idx++)
	{
		if (checkVertexValid(pGraph, idx) == TRUE)
			displayLinkedList(pGraph->ppAdjEdge[idx]);
	}		
}

int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

int getVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->graphType);
}
