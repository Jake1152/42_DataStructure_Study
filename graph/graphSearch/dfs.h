#include <stdbool.h>
#include "linkedgraph.h"
#include "arraygraph.h"

#ifndef _DFS_
#define _DFS_
#define MAX_VERTICES 42
#define VISITED 1
#define NOT_VISITED 0

void dfsList(LinkedGraph* pGraph, int vertexID);
void dfsArray(ArrayGraph* pGraph, int vertexID);

#endif
