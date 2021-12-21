#include "linkedgraph.h"
#include <stdlib.h>
#include <stdio.h>

/*
	- 益掘覗亜 魚稽 砧 帰嬢軒亜 吉陥檎?
		益訓 井酔澗 源戚 照鞠澗亜?
		益係陥檎 graph澗 廃腰 識情拝凶 魁蟹澗亜?
	- direc, undirec 姥歳精 嬢胸惟 拝 依昔亜?
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

// 益掘覗 持失
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
	// vertex姐呪幻鏑 linkedlist 1託据 壕伸税 紫戚綜 舛背辞 疑旋拝雁
	// vertex拭陥亜 尻衣吃 node研 妊薄馬糠稽 固坦製 create拭辞 坦軒
	/* e.g)
	 け -> けけけ
	 け -> けけけけけ
	 け -> けけけけけけけけ
	 け -> け
	 け -> NULL	
	*/
	// maxVertexCount 鯵呪幻鏑 newLinkedList 幻級嬢層陥.
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);	
	if (newLinkedListPtr == NULL)
	{
		free(newLinkedGraph);
		return (NULL);
	}
	// maxVertexCount 姐呪幻鏑 ppAdjEdge拭 蓄亜吃 LinkedList* 拝雁
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
	// Vertex 蓄亜 1託据 array list
	newVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	/*
	- 叔鳶馬澗 井酔 戚穿拭 拝雁廃 1託据 linked list free
	- 2託据linked list pointer free
	- graph暁廃 free
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

// 因拷 益掘覗 食採 毒舘
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL || pGraph->currentVertexCount)
		return (FALSE);
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

// 葛球 蓄亜
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
	// maxVertexCount 戚雌戚檎 False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	printf("2\n");
	// 歯稽 級嬢紳 vertexID研 currentVertexCount index拭 隔嬢辞 vertexID澗 headerNode data拭 蓄亜廃陥.
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

// 娃識 蓄亜
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		linked list研 戚遂馬澗 号狛
		from拭辞 to拭 蓄亜
		from聖 嬢胸惟 達澗亜?
		掻差精 嬢胸惟拝 依昔亜?
		重井照床壱 掻差馬惟 幻級依昔亜?
		2託据昔 ppAdjEdge拭辞 from vertex研 達澗陥.
		from拭 to vertex研 蓄亜廃陥.
		Linked List 照拭 Linked List亜 赤陥.
		け -> けけ
		け -> けけけけ
		け -> けけけけけけ
		け -> けけけ
		け -> けけけけけ
		け -> けけ
	*/
	ListNode 	ListNodeElement;
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			addElement_status;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// 巷号狽 益掘覗析凶, 丞号狽 尻衣
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		// idx澗 背雁 葛球 fromVertexID, toVertexID
		// fromVertexID_idx 達奄 貢 fromVertexID -> toVertexID 尻衣
		if (chainingEdge(pGraph, fromVertexID, toVertexID) == FALSE)
			return (FALSE);
		// toVertexID 達奄 貢 toVertexID -> fromVertexID 尻衣
		if (chainingEdge(pGraph, toVertexID, fromVertexID) == FALSE)
			return (FALSE);
	}
	//	号狽益掘覗析��, 舘号狽生稽幻 尻衣
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
	// け -> けけけけ 尻衣軒什闘 姥薄吉 敗呪研 戚遂備食 歯稽錘 色走研 固 及拭 尻衣鞠亀系 廃陥
	// 督虞耕斗 pList, position, element 授辞
	addElement_status = addLLElement(pGraph->ppAdjEdge[fromVertexID_idx], \
					pGraph->ppAdjEdge[fromVertexID_idx]->currentElementCount, \
					ListNodeElement);
	pGraph->currentEdgeCount++;
	return (addElement_status);
}

// weighted稽 馬檎 姥繕端研 痕井背醤拝 依生稽 持唖. 析舘 左嫌
int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	/*
		undirected
		directed 蟹寛辞 遭楳
	*/
	// null guard, from, to vertex級戚 赤澗走 溌昔
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// 葛球税 政反失 繊伊.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	/*
		政反失戚空 巷譲昔亜?
		授発馬澗走 焼観走 採歳?
		used, not used
		- 葛球切端亜 赤澗走		
		- 巷号狽析凶
		  辞稽 尻衣鞠嬢赤澗走
	*/
	int idx;

	if (pGraph == NULL)
		return (FALSE);
	idx = 0;
	// vertexID亜 0採斗 赤生軒虞澗 左舌戚 蒸陥. pVertex[idx]人 歳軒背辞 持唖
	while (pGraph->currentVertexCount > idx)
	{
		if (pGraph->pVertex[idx] == vertexID)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

// 葛球 薦暗
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	/*
		Node研 薦暗馬檎 尻衣吉 元滴亀 陥 薦暗
		蟹人 尻衣吉 葛球級聖 達澗陥.
	*/
	int			vertexID_idx;
	ListNode*	curListNode;

	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	vertexID_idx = findGraphNodePosition(pGraph, vertexID);
	if (vertexID_idx == -1)
		return (FALSE);
	curListNode = pGraph->ppAdjEdge[vertexID_idx]->headerNode;
	// 巷号狽
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		while (curListNode->pLink)
		{
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);
			removeEdgeLG(pGraph, curListNode->pLink->data,vertexID_idx);
			curListNode = curListNode->pLink;
		}
	}
	// 号狽
	else
	{
		while (curListNode->pLink)
		{
			// 薄仙 鎧 脊舌拭辞 尻衣吉 娃識幻 薦暗
			// 陥献 舛繊拭辞 蟹研 亜軒徹澗 井酔澗 嬢胸惟 馬澗亜?
			// 析析戚 達焼辞 薦暗廃陥?
			removeEdgeLG(pGraph, vertexID_idx, curListNode->pLink->data);			
			curListNode = curListNode->pLink;
		}
	}
	// 鎧 舛繊聖 授噺稽 達精 陥製拭 NOT_USED坦軒
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (vertexID == pGraph->pVertex[i])
			pGraph->pVertex[i] = NOT_USED;
	}
	// pGraph->currentVertexCount 痕井馬檎 及拭赤澗 idx研 凧繕 公拝 呪 赤陥.
	// 薦企稽拝形檎 array list resize馬暗蟹
	// vertex煽舌亀 linked list稽 廃陥
	// removeEdgeLG(pGraph, int fromVertexID, int toVertexID)
	pGraph->currentVertexCount--;
	return ( pGraph->currentVertexCount);
	// NOT_USED稽 痕井
}

// 娃識 薦暗
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	/*
		蓄亜拝��坦軍 号狽昔走 食採拭 魚虞 蟹堪
	*/
	int			fromVertexID_idx;
	int			toVertexID_idx;
	int			removeElement_status;

	if (pGraph == NULL || isEmptyLG(pGraph) == TRUE \ 
		|| checkVertexValid(pGraph, fromVertexID) == FALSE \
		|| checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	// 巷号狽
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
	// 号狽
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
		訊 督虞耕斗亜 LinkedList昔亜?
		走酔壱切馬澗 vertex人 尻衣吉 link研 走錘陥.
		益君檎 薄仙 戚 督析拭辞 removeEdge人 違庁陥.
		益君糠稽 紺亀 姥薄馬走 省澗陥.
	*/
	if (pList == NULL)
		exit(EXIT_FAILURE);	
}

// 益掘覗 肢薦
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
		int *pVertex;			// index 閤澗 遂亀
		LinkedList** ppAdjEdge;	// 
		// 1託据拭 企背辞 index閤澗 遂亀

		LinkedList** ppAdjEdge;拭辞 嬢胸惟 角移閤聖 依昔亜?
		* ppAdjEdge 戚係惟馬檎   1. 追戚什戚陥.
		据馬澗 依精 室稽 匝 聡, 葛球級税 header研 亜軒迭 益員戚陥.
		鉱拭辞 findGraphNodePosition(pGraph->ppAdjEdge) 戚係惟 角掩 呪赤澗亜?
		馬走幻 pGraph->ppAdjEdge 戚掻匂昔斗虞辞 照限聖暗 旭陥.
		益係陥壱 馬走幻 pGraph->ppAdjEdge 縮越 匂昔斗稽 角奄澗闇 乞牽�抓�.
		1, け -> けけけけ
		け
		け
		け
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

// 益掘覗 舛左 窒径
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		葛球紺稽 尻衣吉 依級 窒径
		馬走幻 号狽失 食採拭 魚虞 陥牽惟 窒径
		嬢恐 授辞稽 尻衣鞠嬢赤澗走?
		号狽失 雌淫蒸戚 窒径.
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

// 娃識 鯵呪 鋼発
int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// 葛球 鯵呪 鋼発
int getVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

// 置企 葛球 鯵呪 鋼発
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

// 益掘覗 曽嫌 鋼発.
int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
		return (FALSE);
	return (pGraph->graphType);
}
