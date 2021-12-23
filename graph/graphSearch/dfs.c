#include <stdio.h>
#include "linkedgraph.h"
#include "arraygraph.h"
#include "dfs.h"


int visited[MAX_VERTICES];

void dfsList(LinkedGraph* pGraph, int vertexID)
{
    visited[vertexID] = VISITED;
}

void dfsArray(ArrayGraph* pGraph, int vertexID)
{

}


