#include "arraygraph.h"

/**
 * @brief Create a Array Graph object
 * 
 * @param maxVertexCount 
 * @return ArrayGraph* 
 1. 무방향 그래프
        1. 간선은 간선을 통해 양쪽 방향을 갈 수 있음을 나타내며, 정점 A와 B가 간선을 통해 연결되어 있다고 한다
        2. (A,B) = (B,A)
2. 방향그래프
        1. 방향 그래프에서의 간선은 단방향성의 성질을 가지고 있어요. 방향 그래프에서의 간선은 '>'를 이용하여 나타내며 <A,B>와 <B,A>는 서로 다른 간선이되죠.
3. 인접행렬
장점 : 그리고, 노드 i와 노드 j가 연결되어 있는지 확인하고 싶을 때,
adj[i][j]가 1인지 0인지만 확인하면 되기 때문에 O(1)이라는 시간 복잡도에 확인할 수 있다는 점이 있습니다. 
단점 : 전체 노드의 개수를 V개, 간선의 개수를 E개라고 해봅시다.
노드 i에 연결된 모든 노드들에 방문해보고 싶은 경우 adj[i][1]부터 adj[i][V]를 모두 확인해보아야 하기 때문에 총 O(V)의 시간이 걸린다는 점입니다.
 * 
 */

ArrayGraph* createArrayGraph(int maxVertexCount)
{
    ArrayGraph *pGraph;
    
    pGraph = (ArrayGraph *)malloc(sizeof(ArrayGraph));
    if(!pGraph)
        return (NULL);
    pGraph->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
    if(!pGraph->pVertex)
    {
        free(pGraph);
        return (NULL);
    }
    pGraph->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
    if(!pGraph->ppAdjEdge)
    {
        free(pGraph->pVertex);
        free(pGraph);
        return (NULL);
    }
    for(int i = 0;i < maxVertexCount; i++)
    {
        pGraph->ppAdjEdge[i] = (int *) malloc(sizeof(int) * maxVertexCount);
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
    pGraph->currentVertexCount = 0;
    return (pGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
    ArrayGraph *pGraph;
    
    pGraph = (ArrayGraph *)malloc(sizeof(ArrayGraph));
    if(!pGraph)
        return (NULL);
    pGraph->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
    if(!pGraph->pVertex)
    {
        free(pGraph);
        return (NULL);
    }
    pGraph->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
    if(!pGraph->ppAdjEdge)
    {
        free(pGraph->pVertex);
        free(pGraph);
        return (NULL);
    }
    for(int i = 0;i < maxVertexCount; i++)
    {
        pGraph->ppAdjEdge[i] = (int *) malloc(sizeof(int) * maxVertexCount);
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
    pGraph->currentVertexCount = 0;
    return (pGraph);
}

// 그래프 삭제
void deleteArrayGraph(ArrayGraph* pGraph)
{
    if(!pGraph)
        return ;
    for(int i = 0; i < pGraph->maxVertexCount; i++)
        free(pGraph->ppAdjEdge[i]);
    free(pGraph->ppAdjEdge);
    free(pGraph->pVertex);
}

// 공백 그래프 여부 판단
int isEmptyAG(ArrayGraph* pGraph)
{
    if(!pGraph)
        return (TRUE);
    if(pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

// 노드 추가
// vertexID 가 해당 인덱스를 나타내는지 알아야 함.
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if(!pGraph)
        return (FALSE);
    if(pGraph->maxVertexCount <= vertexID || pGraph->pVertex[vertexID] == USED)
        return (FALSE);
    pGraph->pVertex[vertexID] = USED;
    pGraph->currentVertexCount++;
    return (TRUE);
}

// 간선 추가
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    return (addEdgewithWeightAG(pGraph,fromVertexID,toVertexID,USED));
}
// 
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if(!pGraph)
        return (FALSE);
    if(!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
    return(TRUE);
}

// 노드의 유효성 점검.
// 노드가 used 인지 아닌지 
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if(!pGraph)
        return (FALSE);
    if(pGraph->maxVertexCount <= vertexID)
        return (FALSE);
    if(pGraph->pVertex[vertexID] == NOT_USED)
        return (FALSE);
    return (TRUE);
}

// 노드 제거
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if(!pGraph)
        return (FALSE);
    if(isEmptyAG(pGraph))
        return (FALSE);
    pGraph->pVertex[vertexID] = NOT_USED;
    for(int i = 0; i < pGraph->currentVertexCount; i++)
        pGraph->ppAdjEdge[vertexID][i] = 0;
    for(int i = 0; i < pGraph->currentVertexCount; i++)
        pGraph->ppAdjEdge[i][vertexID] = 0;
    pGraph->currentVertexCount--;
    return (TRUE);
}

// 간선 제거
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(!pGraph)
        return (FALSE);
    if(!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID][toVertexID] = NOT_USED;
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        pGraph->ppAdjEdge[toVertexID][fromVertexID] = NOT_USED;
    return(TRUE);
}

// 그래프 정보 출력
void displayArrayGraph(ArrayGraph* pGraph)
{
    for(int i = 0; i < pGraph->currentVertexCount; i++)
    {
        for(int j = 0; j <pGraph->currentVertexCount; j++)
        {
            printf("%d",pGraph->ppAdjEdge[j][i]);
        }
        printf("\n");
    }
}

int main()
{
    ArrayGraph *pGraph;

    pGraph = createArrayGraph(6);
    addVertexAG(pGraph,0);
    addVertexAG(pGraph,1);
    addVertexAG(pGraph,2);
    addVertexAG(pGraph,3);
    addVertexAG(pGraph,4);
    addVertexAG(pGraph,5);
    addEdgeAG(pGraph,1,0);
    addEdgeAG(pGraph,1,2);
    addEdgeAG(pGraph,0,2);
    addEdgeAG(pGraph,2,3);
    addEdgeAG(pGraph,4,3);
    addEdgeAG(pGraph,3,5);
    addEdgeAG(pGraph,4,5);
    displayArrayGraph(pGraph);
    printf("\n");
    printf("after 3 , 5\n");
    removeEdgeAG(pGraph,3,5);
    displayArrayGraph(pGraph);
}