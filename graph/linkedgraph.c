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
	printf("\n");
	return (0);
}

// 益掘覗 持失
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
	// vertex姐呪幻鏑 linkedlist 1託据 壕伸税 紫戚綜 舛背辞 疑旋拝雁
	// vertex拭陥亜 尻衣吃 node研 妊薄馬糠稽 固坦製 create拭辞 坦軒
	newLinkedListPtr = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);
	/*
		け 
		け
		け
	*/
	// maxVertexCount 鯵呪幻鏑 newLinkedList 
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

// 因拷 益掘覗 食採 毒舘
int isEmptyLG(LinkedGraph* pGraph)
{
	if (pGraph == NULL)
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
	// maxVertexCount戚雌昔 井酔, reallocation maxVertexCount 2壕稽 装亜獣徹奄
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

// 娃識 蓄亜
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	LinkedList*	newLinkedList;
	ListNode*	curListNode;

	if (pGraph == NULL || checkVertexValid(pGraph, fromVertexID) == FALSE || \
		checkVertexValid(pGraph, toVertexID) == FALSE)
		return (FALSE);
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
	curListNode = pGraph->ppAdjEdge->headerNode;
	// curListNode拭 蒸澗井酔 坦軒澗 嬢胸惟拝 依昔亜?
	// 紺亀 敗呪稽 ��澗惟 蟹聖 依生稽 持唖
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
	*/
}

// 益掘覗 舛左 窒径
void displayLinkedGraph(LinkedGraph* pGraph)
{
	/*
		葛球紺稽 尻衣吉 依級 窒径
		馬走幻 号狽失 食採拭 魚虞 陥牽惟 窒径
		嬢恐 授辞稽 尻衣鞠嬢赤澗走?
	*/
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
