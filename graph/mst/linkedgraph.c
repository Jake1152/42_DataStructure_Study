#include "linkedgraph.h"
#include "linkedlist.c"

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount)
{
    LinkedGraph *pGraph;

    pGraph = (LinkedGraph *)malloc(sizeof(LinkedGraph));
    if(!pGraph)
        return (NULL);
    pGraph->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
    if(!pGraph->pVertex)
    {
        free(pGraph);
        return (NULL);
    }
    pGraph->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * maxVertexCount);
    if(!pGraph->ppAdjEdge)
    {
        free(pGraph->pVertex);
        free(pGraph);
        return (NULL);
    }
    for(int i = 0;i < maxVertexCount; i++)
    {
        pGraph->ppAdjEdge[i] = (LinkedList *) malloc(sizeof(LinkedList));
        if(!pGraph->ppAdjEdge[i])
        {
            for(int j = 0; j < i; j++)
                free(pGraph->ppAdjEdge[j]);
            free(pGraph->ppAdjEdge);
            free(pGraph->pVertex);
            free(pGraph);
            return (NULL);
        }
    }
    pGraph->graphType = GRAPH_UNDIRECTED;
    pGraph->maxVertexCount = maxVertexCount;
    pGraph->currentEdgeCount = 0;
    pGraph->currentVertexCount = 0;
    return (pGraph);
}
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
    LinkedGraph *pGraph;

    pGraph = (LinkedGraph *)malloc(sizeof(LinkedGraph));
    if(!pGraph)
        return (NULL);
    pGraph->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
    if(!pGraph->pVertex)
    {
        free(pGraph);
        return (NULL);
    }
    pGraph->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * maxVertexCount);
    if(!pGraph->ppAdjEdge)
    {
        free(pGraph->pVertex);
        free(pGraph);
        return (NULL);
    }
    for(int i = 0;i < maxVertexCount; i++)
    {
        pGraph->ppAdjEdge[i] = (LinkedList *) malloc(sizeof(LinkedList));
        if(!pGraph->ppAdjEdge[i])
        {
            for(int j = 0; j < i; j++)
                free(pGraph->ppAdjEdge[j]);
            free(pGraph->ppAdjEdge);
            free(pGraph->pVertex);
            free(pGraph);
            return (NULL);
        }
    }
    pGraph->graphType = GRAPH_DIRECTED;
    pGraph->maxVertexCount = maxVertexCount;
    pGraph->currentEdgeCount = 0;
    pGraph->currentVertexCount = 0;
    return (pGraph);
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{
    if(!pGraph)
        return ;
    for(int i = 0; i < pGraph->maxVertexCount; i++)
        deleteLinkedList(pGraph->ppAdjEdge[i]);
    free(pGraph->ppAdjEdge);
    free(pGraph->pVertex);

}

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph)
{
    if(!pGraph)
        return (FALSE);
    if(pGraph->currentEdgeCount == 0)
        return (TRUE);
    return (FALSE);
}

// 노드 추가
// vertexID 값이 index라고 생각하고 해당하는 vertexID index의 value를 used라고 바꿔준다.
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
    if(!pGraph)
        return (FALSE);
    if(vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    if(pGraph->pVertex[vertexID] == USED)
        return (FALSE);
    pGraph->pVertex[vertexID] = USED;
    pGraph->currentVertexCount++;
    return (TRUE);
}

// 간선 추가
// weight라는 변수를 통해 얼마나 강한 연결성을 표현을 하는데 edgeLG일 경우 단순 연결 되있다고 생각을 해 USED로만 해결
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    return (addEdgewithWeightLG(pGraph, fromVertexID, toVertexID, USED));

}

// linkedlist 때 사용한 함수로 새로운 간선이 추가 될때 끝에 리스트에 추가되도록 설정 
int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    ListNode addNode;
    if (!pGraph)
        return (FALSE);
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    addNode.vertexID = toVertexID;
    addNode.weight = weight;
    addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, addNode);
    if (pGraph->graphType == GRAPH_UNDIRECTED)
    {
        addNode.vertexID = fromVertexID;
        addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, addNode);
    }
    pGraph->currentEdgeCount++;
    return (TRUE);
}

// 노드의 유효성 점검.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
    if (vertexID >= pGraph->maxVertexCount || pGraph->pVertex[vertexID] == NOT_USED)
        return (FALSE);
    return (TRUE);
}

// 노드 제거
// node 제거 도 추가와 같은 의미로 not_used로 바꿔주고 그에 해당하는 간선들을 다 제거해주었다.
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{    
    if (!pGraph)
        return (FALSE);
    if (!checkVertexValid(pGraph, vertexID))
        return (FALSE);
    for (int i = 0; i < pGraph->currentVertexCount; i++)
    {
        removeEdgeLG(pGraph, vertexID, i);
        removeEdgeLG(pGraph, i, vertexID);
    }
    pGraph->pVertex[vertexID] = NOT_USED;
    pGraph->currentVertexCount--;
    return (TRUE);
}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph)
        return (FALSE);
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
    if (pGraph->graphType == GRAPH_UNDIRECTED)
        deleteGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
    pGraph->currentEdgeCount--;
    return (TRUE);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
    if (!pList)
        return;
    int position;

    position = findGraphNodePosition(pList, delVertexID);
    if (position >= 0)
        removeLLElement(pList, position);
}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
    if (!pList)
        return (-1);
    ListNode *temp;
    int position = 0;

    temp = pList->headerNode.pLink;
    while (temp)
    {
        if (temp->vertexID == vertexID)
            return (position + 1);
        position++;
        temp = temp->pLink;
    }
    return (-1);
}

// 간선 개수 반환
int getEdgeCountLG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    return (pGraph->currentEdgeCount);
}
// 노드 개수 반환
int getVertexCountLG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    return (pGraph->currentVertexCount);
}

// 최대 노드 개수 반환
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    return (pGraph->maxVertexCount);
}

// 그래프 종류 반환.
int getGraphTypeLG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    return (pGraph->graphType);
}

void displayLinkedList(LinkedList *pList, int tag)
{
	ListNode *node;

	if (!pList)
		return;
	node = pList->headerNode.pLink;
	for (int i = 0; i < pList->currentElementCount; ++i)
		printf("====");
	printf("\n");
    printf("%d -> ", tag);
	for (int i = 0; i < pList->currentElementCount; ++i)
	{
		printf("%d ", node->vertexID);
		node = node->pLink;
	}
	printf("\n");
	for (int i = 0; i < pList->currentElementCount; ++i)
		printf("====");
	printf("\n");
}

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{
    if(!pGraph)
        return ;
    for(int i = 0; i < pGraph->maxVertexCount; i++)
    {
        if(pGraph->pVertex[i] == USED)
            displayLinkedList(pGraph->ppAdjEdge[i], i);
    }
}

int main()
{
    LinkedGraph *pGraph;

    pGraph = createLinkedDirectedGraph(6);
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
}