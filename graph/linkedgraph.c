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
	// mainLinkedGraph

	printf("\n");
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
	int*	newVertex;
	int		idx;

	if (pGraph == NULL)
		return (FALSE);
	// maxVertexCount 戚雌戚檎 False
	if (pGraph->maxVertexCount <= pGraph->currentVertexCount)
		return (FALSE);
	pGraph->pVertex[pGraph->currentVertexCount] = vertexID;
	// 歯稽 級嬢紳 vertexID研 currentVertexCount index拭 隔嬢辞 vertexID澗 headerNode data拭 蓄亜廃陥.
	pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	pGraph->currentVertexCount++;
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

	for (int i = 0; i<pGraph->currentVertexCount; i++)
	{
		if (pGraph->ppAdjEdge[i]->header.data == fromVertexID)
		{
			fromVertexID_idx = i;
			break ;
		}
	}
	ListNodeElement.data = toVertexID;
	// け -> けけけけ 尻衣軒什闘 姥薄吉 敗呪研 戚遂備食 歯稽錘 色走研 固 及拭 尻衣鞠亀系 廃陥
	// 督虞耕斗 pList, position, element 授辞
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
		directed 蟹寛辞 遭楳
	*/
	// null guard, from, to vertex級戚 赤澗走 溌昔
	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
	if (pGraph->graphType)

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
	if (pGraph == NULL || isEmptyLG(pGraph) || checkVertexValid(pGraph, vertexID))
		return (FALSE);
	return (pGraph->currentVertexCount);
	// NOT_USED稽 痕井
}

// 娃識 薦暗
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

// 益掘覗 肢薦
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
	LinkedList* pCurList;

	pCurList = pList;
	if (pList == NULL)
		return (FALSE);
	// pGraph->ppAdjEdge[pGraph->currentVertexCount]->headerNode.data = vertexID;
	if (pList->headerNode.data == vertexID)
	
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
