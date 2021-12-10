#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

typedef struct DequeNodeType
{
	char	data;
	struct DequeNodeType* pLink;
} QueueNode;

typedef struct LinkedDequeType
{
	int currentElementCount;	// ���� ������ ����
	int	front;
	int	rear;
	QueueNode* pFrontNode;		// Front ����� ������	
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int insertRearLD(LinkedQueue* pDeque, LinkedQueue element);
// single queue에서 front rear를 넣을 필요가 있는가?

QueueNode* deleteFrontLD(LinkedQueue* pDeque);
QueueNode* peekFrontLD(LinkedQueue* pDeque);
void deleteLinkedQueue(LinkedQueue* pDeque);
int isLinkedQueueEmpty(LinkedQueue* pDeque);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif