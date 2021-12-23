#include <stdbool.h>
#include "linkedgraph.h"
#include "graphsearch.h"

#ifndef _MST_KRUSKAL_
#define _MST_KRUSKAL_

void			initGraph(LinkedGraph* pGraph);
int				checkSortedEdge(LinkedGraph* pGraph);
bool			checkCircle(LinkedGraph* pGraph);
LinkedList*		extractEdge(LinkedGraph* pGraph);
LinkedGraph*	kruskal(LinkedGraph* pGraph);

#endif
