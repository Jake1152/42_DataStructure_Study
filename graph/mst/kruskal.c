#include "kruskal.h"

#include <stdio.h>
#include <stdlib.h>

/*
- 도로건설
- 네트워크 연결
- 전기회로
- 배관

- greedy

1. 간선 가중치를 기준으로 오름차순으로 정렬 
2. 가장 짧은 간선부터 이어붙였을떄 순환이 안되는 경우만 이어붙인다. 
3. 연결된 간선의 개수가 정점개수 -1 이면 모두 연결된것ㅇ
ㅁ - ㅁ - ㅁ
출처: C로 쉽게 풀어쓴 자료구조 2nd

e log_2_e

*/

int parent[MAX_VERTICES];	
int num[MAX_VERTICES];		// 집합 내의 원소 개수

void    set_init(int n)
{
	int i;
	
	i = 0;
	while (i < n)
	{
		parent[i] = -1;
		num[i] = 1;
		i++;
	}
}

int set_find(int vertex)
{
  int p, s, i = -1; // p: 부모노드
 
  // 루트노드까지 반복한다. p가 -1이 되면 반복문은 종료한다.
  // p가 -1이라는 건 현재 노드(i)가 루트라는 뜻이다.
  // 우리는 위에서 루트노드의 부모는 -1로 설정했다.
  for (i = vertex; (p = parent[i]) >= 0; i = p)
	  ; 
  s = i;  // 루트노드 정보를 s에 저장
 
  // vertex의 조상노드들이 s(루트 노드)를 향하게끔 설정한다.
  for (i = vertex; (p = parent[i]) >= 0; i = p)
    parent[i] = s;
 
  return s; // 모든 노드의 부모인 루트를 반환한다.
}

// 개별로 되어있던 각각의 집합을 1개의 집합으로 합친다.
void    set_union(int s1, int s2)
{
	// 더 큰 집합으로 인수합병
	if (num[s1] < num[s2])
	{
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else
	{
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void init(HeapType *h)
{
  h->heap_size = 0;
}

int is_empty(HeapType *h)
{
  if (h->heap_size == 0)
    return TRUE;
  else
    return FALSE;
}

void insert_min_heap(HeapType *h, element item)
{
  int i = ++(h->heap_size);
 
  // 단말노드부터 부모노드로 거슬러 올라가며 확인하는 과정
  while ((i != 1) && (item.key < h->heap[i / 2].key))
  {
    // 거슬러 올라가기 위해 현재노드를 부모노드로 설정한다.
    h->heap[i] = h->heap[i / 2];
 
    // 인덱스를 부모노드로 설정한다.
    i /= 2;
  }
  // 올라올만큼 올라왔으므로 넣어준다.
  h->heap[i] = item;
}

void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
  element e;
  e.u = u;
  e.v = v;
  e.key = weight;
  insert_min_heap(h, e);
}
 
void insert_all_edges(HeapType *h)
{
  // 최소히프이므로 가장 작은 노드가 루트노드로 위치하게 된다.
  insert_heap_edge(h, 0, 1, 29);
  insert_heap_edge(h, 1, 2, 16);
  insert_heap_edge(h, 2, 3, 12);
  insert_heap_edge(h, 3, 4, 22);
  insert_heap_edge(h, 4, 5, 27);
  insert_heap_edge(h, 5, 0, 10);
  insert_heap_edge(h, 6, 1, 15);
  insert_heap_edge(h, 6, 3, 18);
  insert_heap_edge(h, 6, 4, 25);
}

element delete_min_heap(HeapType *h)
{
  int parent, child;
  element item, temp;
 
  // 루트값(min heap에서 최소값) 저장
  item = h->heap[1];
 
  // 맨 마지막에 있는 노드의 값을 temp에 저장, 루트 뻇으므로 1감소
  temp = h->heap[h->heap_size];
  h->heap_size--;
 
  // 빈 루트자리를 맨 단말노드를 넣어서 heapify하는 과정
  parent = 1; // 맨 첫 실행의 부모노드를 루트로 둔다.
  child = 2; // 그 왼쪽 자식을 자식노드로 둔다.
 
  // child가 힙 사이즈보다 크면 힙을 벗어난 비교이므로 실행이 안된다.
  while (child <= h->heap_size)
  {
    // 두 개의 자녀 중 더 작은 자녀를 비교기준으로 삼기 위해 아래의 if문 실행
	// 오른쪽 자녀가 있다고 생각하면, child는 힙사이즈보다 작아야 한다.
	
    if ((child < h->heap_size) && \
		(h->heap[child].key) > h->heap[child + 1].key)
      	// 오른쪽 자녀 (child + 1)이 더 작기 때문에 새로운 기준점을 만들어주기 위해 child++ 을 해준다.
		child++;
 
    // 비교 대상인 child를 설정했으니 루트노드에 위치 중인 temp와 비교한다.
    // temp가 더 작다면 위치이동을 할 필요가 없으므로 이 반복문을 빠져나간다.
    // 제자리에 있다는 뜻이다. 최소히프는 작은 값이 부모로 있어야 한다.
    if (temp.key <= h->heap[child].key)
      break;
 
    // 여기까지 왔다는 건 temp의 자리교환이 필요하다는 뜻이다.
    // temp가 있을 곳을 찾기 위해 비교대상을 한 단계 아래로 이동한다.
    h->heap[parent] = h->heap[child]; // 자녀의 값이 새로운 비교 기준점이 된다.
    parent = child; // 자녀가 부모로 된다. (다음 비교를 위해)
    child *= 2; // 2를 곱하여 다음 자녀로 된다.
  }
  // 위 반복문을 빠져나오면, parent가 temp가 위치할 곳이 되어 있을 것이다.
  h->heap[parent] = temp;
  return item;
}

// kruskal의 최소 비용 신장 트리 알고리즘
void kruskal(int n)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수
	HeapType h;		       	// 최소 히프
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	element e;				// 히프 요소

	init(&h);					// 히프 초기화
	insert_all_edges(&h);		// 히프에 간선들을 삽입
	set_init(n);				// 집합 초기화
   
	while (edge_accepted < (n - 1)) // 간선의 수 < (n - 1)
	{
		e = delete_min_heap(&h);  // 가장 작은 가중치의 간선 획득
		// 획득됨과 동시에 해당 간선은 히프에서 제거된다.
		uset = set_find(e.u);   // 정점 u의 집합 번호
		vset = set_find(e.v);   // 정점 v의 집합 번호
	
		// 두 집합이 서로 다른 집합에 속한다면
		if (uset != vset)
		{
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);  // 두 개의 집합을 합친다.
		}
	}
}

int main(void)
{
	printf("start in main()\n");
	kruskal(7);
	printf("end of main()\n");
	return (0);
}


/*
LinkedGraph*	kruskal(LinkedGraph* pGraph)
{
	
	//    - 간선들을 가중치를 기준으로 오름차순으로 정렬
	//    - 가중치가 가장 낮으면서 서클을 만들지 않는 간선을 뽑는다 (pop)
	//    - 그래프의 모든 노드가 n-1개까지 연결될때까지 반복
	
}

void			initGraph(LinkedGraph* pGraph)
{

}

int				checkSortedEdge(LinkedGraph* pGraph)
{

}

bool			checkCircle(LinkedGraph* pGraph)
{

}

LinkedList*		extractEdge(LinkedGraph* pGraph)
{

}

*/