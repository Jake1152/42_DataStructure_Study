#ifndef _SIM_UTIL_
#define _SIM_UTIL_
#include "linkedqueue.h"

typedef struct DequeNodeType
{
	char data;
	struct DequeNodeType* pLink;
} QueueNode;

typedef struct LinkedDequeType
{
	int currentElementCount;	// ���� ������ ����
	QueueNode* pFrontNode;		// Front ����� ������
} LinkedQueue;

// ���� ���� ť�� ���� �߰�.
void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue);

// ���� ���� ó��.
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue);

// ���� ���� ó��.
QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);

// ���� ���� ó��.
QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
					  int *pServiceUserCount, int *pTotalWaitTime);

// ������ ���¸� ���?.
void printSimCustomer(int currentTime, SimCustomer customer);

// ���? ���� ���¸� ���?.
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);

// ���� �ùķ��̼� ���?(����?) ���?.
void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime);

#endif