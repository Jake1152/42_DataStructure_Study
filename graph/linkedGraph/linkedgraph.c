#include "linkedgraph.h"
#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

/*
	- ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½î¸®ï¿½ï¿½ ï¿½È´Ù¸ï¿½?
		ï¿½×·ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ÈµÇ´Â°ï¿½?
		ï¿½×·ï¿½ï¿½Ù¸ï¿½ graphï¿½ï¿½ ï¿½Ñ¹ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ò¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Â°ï¿½?
	- direc, undirec ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½î¶»ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Î°ï¿½?
	- ÀÎÁ¢¸®½ºÆ®
	- °¢ ³ëµåº°·Î ÀÎÁ¢ÇÑ ¸®½ºÆ®µéÀ» Ç¥ÇöÇÑ´Ù.
	- ½Ã°£º¹Àâµµ
		- Å½»ö
			- ³ëµå(V)¿¡ ¿¬°áµÈ °£¼±(E)¸¸Å­			
		- »èÁ¦
			- ³ëµå¸¦ Ã£¾Æ¼­ ¿¬°áµÈ °£¼± Áß ¾î¶² °£¼±À» ²÷À»Áö ¿¬°á¸®½ºÆ® ¼øÈ¸·Î Ã£¾Æ¾ßÇÑ´Ù.
		- »ðÀÔ
			- ³ëµå¸¦ Ã£¾Æ¼­ ¿¬°áµÈ °£¼± Áß ¾î¶² °£¼±À» ²÷À»Áö ¿¬°á¸®½ºÆ® ¼øÈ¸·Î Ãß°¡
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

// ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
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
	// vertexï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Å­ linkedlist 1ï¿½ï¿½ï¿½ï¿½ ï¿½è¿­ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ò´ï¿½
	// vertexï¿½ï¿½ï¿½Ù°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? nodeï¿½ï¿½ Ç¥ï¿½ï¿½ï¿½Ï¹Ç·ï¿½ ï¿½ï¿½Ã³ï¿½ï¿½ createï¿½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½
	/* e.g)
	 ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	 ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	 ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	 ï¿½ï¿½ -> ï¿½ï¿½
	 ï¿½ï¿½ -> NULL	
	*/
	// maxVertexCount ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Å­ newLinkedList ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø´ï¿?.
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);	
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
	// maxVertexCount ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Å­ ppAdjEdgeï¿½ï¿½ ï¿½ß°ï¿½ï¿½ï¿½ LinkedList* ï¿½Ò´ï¿½
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
	// Vertex ï¿½ß°ï¿½ 1ï¿½ï¿½ï¿½ï¿½ array list
	newVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	/*
	- ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ò´ï¿½ï¿½ï¿½ 1ï¿½ï¿½ï¿½ï¿½ linked list free
	- 2ï¿½ï¿½ï¿½ï¿½linked list pointer free
	- graphï¿½ï¿½ï¿½ï¿½ free
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

// ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ç´ï¿½
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL || pGraph->currentVertexCount)
		return (FALSE);
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

// ï¿½ï¿½ï¿? ï¿½ß°ï¿½
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
	// maxVertexCount ï¿½Ì»ï¿½ï¿½Ì¸ï¿½ False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	printf("2\n");
	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ vertexIDï¿½ï¿½ currentVertexCount indexï¿½ï¿½ ï¿½Ö¾î¼­ vertexIDï¿½ï¿½ headerNode dataï¿½ï¿½ ï¿½ß°ï¿½ï¿½Ñ´ï¿½.
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

// ï¿½ï¿½ï¿½ï¿½ ï¿½ß°ï¿½
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		linked listï¿½ï¿½ ï¿½Ì¿ï¿½ï¿½Ï´ï¿½ ï¿½ï¿½ï¿?
		fromï¿½ï¿½ï¿½ï¿½ toï¿½ï¿½ ï¿½ß°ï¿½
		fromï¿½ï¿½ ï¿½î¶»ï¿½ï¿½ Ã£ï¿½Â°ï¿½?
		ï¿½ßºï¿½ï¿½ï¿½ ï¿½î¶»ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î°ï¿½?
		ï¿½Å°ï¿½È¾ï¿½ï¿½ï¿? ï¿½ßºï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î°ï¿??
		2ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ppAdjEdgeï¿½ï¿½ï¿½ï¿½ from vertexï¿½ï¿½ Ã£ï¿½Â´ï¿½.
		fromï¿½ï¿½ to vertexï¿½ï¿½ ï¿½ß°ï¿½ï¿½Ñ´ï¿½.
		Linked List ï¿½È¿ï¿½ Linked Listï¿½ï¿½ ï¿½Ö´ï¿½.
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½
	*/
	ListNode 	ListNodeElement;
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			addElement_status;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½ï¿½ï¿½Ï¶ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		// idxï¿½ï¿½ ï¿½Ø´ï¿½ ï¿½ï¿½ï¿? fromVertexID, toVertexID
		// fromVertexID_idx Ã£ï¿½ï¿½ ï¿½ï¿½ fromVertexID -> toVertexID ï¿½ï¿½ï¿½ï¿½
		if (chainingEdge(pGraph, fromVertexID, toVertexID) == FALSE)
			return (FALSE);
		// toVertexID Ã£ï¿½ï¿½ ï¿½ï¿½ toVertexID -> fromVertexID ï¿½ï¿½ï¿½ï¿½
		if (chainingEdge(pGraph, toVertexID, fromVertexID) == FALSE)
			return (FALSE);
	}
	//	ï¿½ï¿½ï¿½ï¿½×·ï¿½ï¿½ï¿½ï¿½?‹ï¿½, ï¿½Ü¹ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î¸ï¿½ ï¿½ï¿½ï¿½ï¿½
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
	// ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½á¸®ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ô¼ï¿½ï¿½ï¿½ ï¿½Ì¿ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ú¿ï¿½ ï¿½ï¿½ï¿½ï¿½Çµï¿½ï¿½ï¿? ï¿½Ñ´ï¿½
	// ï¿½Ä¶ï¿½ï¿½ï¿½ï¿? pList, position, element ï¿½ï¿½ï¿½ï¿½
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
					pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount, \
					ListNodeElement);
	pGraph->currentEdgeCount++;
	return (addElement_status);
}

// weightedï¿½ï¿½ ï¿½Ï¸ï¿½ ï¿½ï¿½ï¿½ï¿½Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ø¾ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½. ï¿½Ï´ï¿½ ï¿½ï¿½ï¿½ï¿½
int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	/*
		undirected
		directed ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	*/
	// null guard, from, to vertexï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ï¿½ï¿½ È®ï¿½ï¿½
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½È¿ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		ï¿½ï¿½È¿ï¿½ï¿½ï¿½Ì¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Î°ï¿½?
		ï¿½ï¿½È¯ï¿½Ï´ï¿½ï¿½ï¿½ ï¿½Æ´ï¿½ï¿½ï¿½ ï¿½Îºï¿½?
		used, not used
		- ï¿½ï¿½ï¿½ï¿½ï¿½Ã¼ï¿½ï¿? ï¿½Ö´ï¿½ï¿½ï¿½		
		- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï¶ï¿½
		  ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ï¿½Ö´ï¿½ï¿½ï¿?
	*/
	int idx;

	if (pGraph == NULL)
		return (FALSE);
	idx = 0;
	// vertexIDï¿½ï¿½ 0ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½. pVertex[idx]ï¿½ï¿½ ï¿½Ð¸ï¿½ï¿½Ø¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	while (pGraph->currentVertexCount > idx)
	{
		if (pGraph->pVertex[idx] == vertexID)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

// ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	/*
		Nodeï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï¸ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½Å©ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Ã£ï¿½Â´ï¿½.
	*/
	int			vertexID_idx;
	ListNode*	curListNode;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	vertexID_idx = findGraphNodePosition(pGraph, vertexID);
	if (vertexID_idx == -1)
		return (FALSE);
	curListNode = pGraph->ppAdjEdge[vertexID_idx]->headerNode;
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		while (curListNode->pLink)
		{
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);
			removeEdgeLG(pGraph, curListNode->pLink->data,vertexID_idx);
			curListNode = curListNode->pLink;
		}
	}
	// ï¿½ï¿½ï¿½ï¿½
	else
	{
		while (curListNode->pLink)
		{
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½å¿¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
			// ï¿½Ù¸ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Å°ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½î¶»ï¿½ï¿½ ï¿½Ï´Â°ï¿½?
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Ã£ï¿½Æ¼ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ñ´ï¿½?
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);			
			curListNode = curListNode->pLink;
		}
	}
	// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¸ï¿½ï¿½ Ã£ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ NOT_USEDÃ³ï¿½ï¿½
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (vertexID == pGraph->pVertex[i])
			pGraph->pVertex[i] = NOT_USED;
	}
	// pGraph->currentVertexCount ï¿½ï¿½ï¿½ï¿½ï¿½Ï¸ï¿½ ï¿½Ú¿ï¿½ï¿½Ö´ï¿½ idxï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö´ï¿½.
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò·ï¿½ï¿½ï¿? array list resizeï¿½Ï°Å³ï¿½
	// vertexï¿½ï¿½ï¿½åµµ linked listï¿½ï¿½ ï¿½Ñ´ï¿½
	// removeEdgeLG(pGraph, int fromVertexID, int toVertexID)
	pGraph->currentVertexCount--;
	return ( pGraph->currentVertexCount);
	// NOT_USEDï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
}

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		ï¿½ß°ï¿½ï¿½Ò‹ï¿½Ã³ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	*/
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			removeElement_status;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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
	// ï¿½ï¿½ï¿½ï¿½
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
		ï¿½ï¿½ ï¿½Ä¶ï¿½ï¿½ï¿½Í°ï¿? LinkedListï¿½Î°ï¿½?
		ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿? vertexï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? linkï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?.
		ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ removeEdgeï¿½ï¿½ ï¿½ï¿½Ä£ï¿½ï¿½.
		ï¿½×·ï¿½ï¿½Ç·ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ê´Â´ï¿½.
	*/
	if (pList == NULL)
		exit(EXIT_FAILURE);	
}

// ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
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
		int *pVertex;			// index ï¿½Þ´ï¿½ ï¿½ëµµ
		LinkedList** ppAdjEdge;	// 
		// 1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ indexï¿½Þ´ï¿½ ï¿½ëµµ

		LinkedList** ppAdjEdge;ï¿½ï¿½ï¿½ï¿½ ï¿½î¶»ï¿½ï¿½ ï¿½Ñ°Ü¹ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î°ï¿½?
		* ppAdjEdge ï¿½Ì·ï¿½ï¿½ï¿½ï¿½Ï¸ï¿½   1. ï¿½ï¿½ï¿½Ì½ï¿½ï¿½Ì´ï¿½.
		ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ headerï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Å³ ï¿½×°ï¿½ï¿½Ì´ï¿½.
		ï¿½Û¿ï¿½ï¿½ï¿½ findGraphNodePosition(pGraph->ppAdjEdge) ï¿½Ì·ï¿½ï¿½ï¿½ ï¿½Ñ±ï¿½ ï¿½ï¿½ï¿½Ö´Â°ï¿½?
		ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ pGraph->ppAdjEdge ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í¶ï¿½ ï¿½È¸ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
		ï¿½×·ï¿½ï¿½Ù°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ pGraph->ppAdjEdge ï¿½Ì±ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Í·ï¿½ ï¿½Ñ±ï¿½Â°ï¿? ï¿½ð¸£Ù´ï¿½.
		1, ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		ï¿½ï¿½
		ï¿½ï¿½
		ï¿½ï¿½
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

// ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		ï¿½ï¿½åº°ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½Íµï¿½ ï¿½ï¿½ï¿?
		ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½â¼º ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
		ï¿½î¶² ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ï¿½Ö´ï¿½ï¿½ï¿??
		ï¿½ï¿½ï¿½â¼º ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿?.
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

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¯
int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¯
int getVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

// ï¿½Ö´ï¿½ ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¯
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

// ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¯.
int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->graphType);
}
