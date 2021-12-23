#include <stdbool.h>
#include "linkedgraph.h"
#include "arraygraph.h"

#ifndef _BFS_
#define _BFS_

void bfsList(LinkedGraph* pGraph, int vertexID);
void bfsArray(ArrayGraph* pGraph, int vertexID);

#endif
