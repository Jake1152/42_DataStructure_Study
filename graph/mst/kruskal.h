#include <stdbool.h>
// #include "linkedgraph.h"
// #include "graphsearch.h"
// #include "heap.h"

#ifndef _MST_KRUSKAL_
#define _MST_KRUSKAL_

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100    // 그래프의 정점의 개수
#define INF 1000            // 무한대 값, 경로가 없음을 뜻한다.
#define MAX_ELEMENT 100     // 히프의 최대크기

// heap
typedef struct
{
  int key;  // 간선의 가중치
  int u;    // 정점 1
  int v;    // 정점 2
} element;
 
typedef struct
{
  element heap[MAX_ELEMENT];
  int heap_size;
} HeapType;

void init(HeapType *h);

int is_empty(HeapType *h);
 
void insert_min_heap(HeapType *h, element item);
void insert_heap_edge(HeapType *h, int u, int v, int weight);
void insert_all_edges(HeapType *h);

element delete_min_heap(HeapType *h);



// union-find
void    set_init(int n);
int     set_find(int vertex);
void    set_union(int s1, int s2);

// kruskal
void insert_heap_edge(HeapType *h, int u, int v, int weight);
void insert_all_edges(HeapType *h);
void kruskal(int n);
// bool			checkCircle(LinkedGraph* pGraph);
// LinkedList*		extractEdge(LinkedGraph* pGraph);
// LinkedGraph*	kruskal(LinkedGraph* pGraph);

#endif
