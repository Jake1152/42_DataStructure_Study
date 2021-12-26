#include "linkedgraph.h"

#ifndef _MST_PRIM_
#define _MST_PRIM_

void			initGraph(LinkedGraph* pGraph);
bool			checkCircle(LinkedGraph* pGraph);
LinkedList*		selectEdge(LinkedGraph* pGraph);
LinkedGraph*	prim(LinkedGraph* pGraph);

#endif

