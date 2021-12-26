#include <bits/stdc++.h>
#define INF 1234567890

#define TRUE true
#define FALSE false
#define NOT_USED 0
#define USED 1
typedef struct _LinkedList{
	int value;
	int weight;
	struct _LinkedList *next;
} LinkedList;

typedef struct LinkedGraphType
{
	int maxVertexCount;		// 최대 노드 개수
	int currentVertexCount;	// 현재 사용되는 노드의 개수
	int currentEdgeCount;	// 현재 간선의 개수.
	int graphType;			// 그래프 종류: 1-Undirected, 2-Directed
	LinkedList** ppAdjEdge;	// 간선 저장을 위한 연결 리스트 (포인터)의 배열
	int *pVertex;			// 노드 저장을 위한 1차원 배열
} LinkedGraph;

typedef struct _Heap
{
	int cnt;
	int **arr;
} Heap;

const int n = 6;
std::vector<std::pair<int, int>> v[n];
std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> dist;

Heap* createHeap(int size)
{
	Heap * heap = (Heap *)malloc(sizeof(Heap));
	heap->cnt = 0;
    heap->arr = (int **)malloc(sizeof(int*)*2);
    for (int i = 0 ; i < 2 ; i++)
	    heap->arr[i] = (int *)malloc(sizeof(int)*size);
	return heap;
}

void AddHeap(Heap * heap, int weight, int v)
{
	int curPos, tmp;
	heap->cnt++;
	heap->arr[0][heap->cnt]= weight;
    heap->arr[1][heap->cnt]= v;
	curPos = heap -> cnt;
	while (curPos != 1)
	{
		if (heap->arr[0][curPos] < heap->arr[0][curPos / 2]){
			tmp = heap->arr[0][curPos];
			heap->arr[0][curPos] = heap->arr[0][curPos / 2];
			heap->arr[0][curPos / 2] = tmp;

            tmp = heap->arr[1][curPos];
			heap->arr[1][curPos] = heap->arr[1][curPos / 2];
			heap->arr[1][curPos / 2] = tmp;
		}
		else
			break;
		curPos /= 2;
	}
}

int * DelHeap(Heap * heap)//min힙
{
    if (heap->cnt==0)
		return NULL;
	int *ret = (int *)malloc(sizeof(int)*2);  //동적할당
	int tmp;
	ret[0] = heap->arr[0][1]; 
	ret[1] = heap->arr[1][1];
	int curPos;
	

	tmp = heap->arr[0][heap->cnt];
	curPos = 1;
	heap->arr[0][curPos] = tmp;
    tmp = heap->arr[1][heap->cnt];
    heap->arr[1][curPos] = tmp;
	heap->cnt--;
	
	
	while (curPos * 2 < heap->cnt)
	{
		if (heap->arr[0][curPos] < heap->arr[0][curPos*2] && heap->arr[0][curPos] < heap->arr[0][curPos*2 + 1])
			break;
		if (heap->arr[0][curPos*2] > heap->arr[0][curPos*2 + 1])
		{
            tmp = heap->arr[0][curPos];
			heap->arr[0][curPos] = heap->arr[0][curPos*2 + 1];
			heap->arr[0][curPos*2 + 1] = tmp;

            tmp = heap->arr[1][curPos];
			heap->arr[1][curPos] = heap->arr[1][curPos*2 + 1];
			heap->arr[1][curPos*2 + 1] = tmp;

			curPos = 2 * curPos + 1;
			
		}
		else
		{ 
			tmp = heap->arr[0][curPos];
			heap->arr[0][curPos] = heap->arr[0][curPos*2];
			heap->arr[0][curPos*2] = tmp;

            tmp = heap->arr[1][curPos];
			heap->arr[1][curPos] = heap->arr[1][curPos*2];
			heap->arr[1][curPos*2] = tmp;

			curPos *= 2;
		}
	}
	//curPos = heap -> cnt;
	return ret;
}

void HeapPrint(Heap *heap)
{
	int treecnt = 1, cnt = 0;
	for (int j = 1 ; j <= heap->cnt ; j++){
		printf("|%d %d|", heap->arr[0][j], heap->arr[1][j]);
		cnt++;
		if (treecnt == cnt){
			printf("\n");
			cnt = 0;
			treecnt*=2;
		}
	}
	printf("\n");
}

int prim(LinkedGraph* graph, Heap * heap, int vertex)
{
    std::cout << "vertex cnt:" <<graph->maxVertexCount << '\n';
    bool selected[6];    
    int ret = 0;
    for (int i = 0 ; i < n ; i++){
        selected[i] = false;
    }

    AddHeap(heap, 0, vertex);
	HeapPrint(heap);

    for (int i = 0 ; i < n ; i++)
    {
        int now = -1, min_dist = INF;
        while (heap->cnt)
        {
            int * heapret;
            heapret = DelHeap(heap);
            now = heapret[1];
            std::cout <<"now: "<< now << '\n';
            if (!selected[now]){
                min_dist = heapret[0];
                break;
            }
        }

        ret += min_dist;
		printf("sum:%d\n", ret);
        selected[now] = true;

        int size = 0;
        LinkedList* node = graph->ppAdjEdge[now];
        node = node->next;
        while (node)
        {
			AddHeap(heap, node->weight, node->value);
            node = node->next;
        }

		HeapPrint(heap);
    }
    return ret;
}


LinkedGraph* createLinkedGraph(int maxVertexCount)
{
	LinkedGraph* graph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	// 예외처리, 프리
	graph->maxVertexCount = maxVertexCount;
	graph->currentVertexCount = 0;
	graph->currentEdgeCount = 0;
	graph->graphType = 1;
	graph->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
	memset(graph->pVertex, NOT_USED, sizeof(int) * maxVertexCount);
	graph->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList*)* maxVertexCount);
	for (int i = 0 ; i < maxVertexCount ; i++){
		graph->ppAdjEdge[i] = (LinkedList *)malloc(sizeof(LinkedList));
		graph->ppAdjEdge[i]->value = i;
		graph->ppAdjEdge[i]->next = NULL;
	}
	return graph;	
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	pGraph->pVertex[vertexID] = 1;
	return TRUE;
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (pGraph->graphType == 1){
		
		//pGraph->ppAdjEdge[fromVertexID]
		LinkedList * tmp = pGraph->ppAdjEdge[fromVertexID];
		while (tmp->next){
			if (tmp->value == toVertexID)
				return FALSE;//에러 예상 지점
			tmp = tmp->next;
		}
		LinkedList * newNode = (LinkedList*)malloc(sizeof(LinkedList));//생성
		newNode->next = NULL;
		newNode->value = toVertexID;
		newNode->weight = weight;

		tmp->next = newNode;
		
		//2번째
		tmp = pGraph->ppAdjEdge[toVertexID];
		while (tmp->next){
			if (tmp->value == fromVertexID)
				return FALSE;//에러 예상 지점
			tmp = tmp->next;
		}
		newNode = (LinkedList*)malloc(sizeof(LinkedList));//생성
		newNode->next = NULL;
		newNode->value = fromVertexID;
		newNode->weight = weight;

		tmp->next = newNode;
		
		return TRUE;
	}

	else if(pGraph->graphType == 2){
		
		//pGraph->ppAdjEdge[fromVertexID]
		LinkedList * tmp = pGraph->ppAdjEdge[fromVertexID];
		while (tmp->next){
			if (tmp->value == toVertexID)
				return FALSE;//에러 예상 지점
			tmp = tmp->next;
		}
		LinkedList * newNode = (LinkedList*)malloc(sizeof(LinkedList));//생성
		newNode->next = NULL;
		newNode->value = toVertexID;
		newNode->weight = weight;

		tmp->next = newNode;		
		return TRUE;
	}
	return FALSE;
}

void displayLinkedGraph(LinkedGraph* pGraph)
{
	printf("vertex info\n");
	for (int i = 0 ; i < pGraph->maxVertexCount ; i++)
		if (pGraph->pVertex[i])
			printf(" %d", i);
	printf("\n\n");
	for (int i = 0 ; i < pGraph->maxVertexCount ; i++){
		printf("vertex%d:",i);
		LinkedList * tmp = pGraph->ppAdjEdge[i];
		tmp=tmp->next;
		while (tmp){
			printf("|v:%d w:%d| ",tmp->value, tmp->weight);
			tmp=tmp->next;
		}
		printf("\n");
	}
}


int main()
{
    LinkedGraph * graph = createLinkedGraph(6);
    for (int i = 0 ; i < graph->maxVertexCount ; i++)
	{
		addVertexLG(graph, i);
	}
    int num;
    std::cin >> num;


    addEdgewithWeightLG(graph, 0, 1, 4);
    
    addEdgewithWeightLG(graph, 0, 2, 3);
    
    addEdgewithWeightLG(graph, 1, 2, 2);
    
    addEdgewithWeightLG(graph, 2, 3, 1);
    
    addEdgewithWeightLG(graph, 3, 4, 1);
    
    addEdgewithWeightLG(graph, 3, 5, 5);
    
    addEdgewithWeightLG(graph, 4, 5, 6);
    
	printf("-----연결 확인-----\n");
    displayLinkedGraph(graph);
    printf("-----연결 완료-----\n\n\n");

    Heap *heap = createHeap(100);
    printf("sum%d",prim(graph, heap, num));
}
