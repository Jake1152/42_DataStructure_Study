#include <stdio.h>
#include <stdlib.h>
#include "simdef.h"
#include "simutil.h"

/*

- ���ť�� ������ ���۽ð� �������� ó��
- ���� �ð��� �Ǿ����� �׶� ó��
- �� ���� ����ð��� �Ǹ� ���� ���ť�� �ִ� �۾��� ���۽ð��� �Ǿ����� �۾��� ó���Ѵ�.
- �׷��� simdef.h�� ������ ������ Ÿ���� ���� ���°��ΰ�?
- queue�� ������ ����ϴ� ������ ���δ�.
- ��ü ������ ��� �Ǵ°�?
	- �ð��� �帥��
	- ���� ó�� ���� ���� ������
	- ���ʸ��� ���ť�� ���� �ִ��� Ȯ���Ѵ�.
		- ���ť�� ���� �ִ��� ����ð��� �����ؼ� �����ص� �Ǵ��� �����Ѵ�.
		- 
	- ���� ������ ���ť�� �߰��Ѵ�.

- ���� �ý���
- 

- ���α׷��ӽ� �ٸ��ǳʱ�� ����ϴ� ����.

*/

// ���� ���� ť�� ���� �߰�.
void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
	/*
		���� ���࿡ �����ϰ�
		���� ���ť�� �߰��Ѵ�.
	*/
	pQueue->pFrontNode

}


// ���� ���� ó��.
QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
	/*
		���ť���� ���� ���۽ð��� ����ð� Ȥ�� ����ð� ������ ��带 �����.
		���� ���� ó��
		�ð��� ���� �帥��.
		QueueNode*�� ����
		�׷��� �帥 �ð��� ��� �����ϴ°�?
		���ť���� ������ processServiceNodeStart�Լ��� ���� �ʿ���
		����ð����� ����ó���ؾ��� ����� ó���ð��� ���Ѵ�.
		�׷��� ������ ó�� �߿� ������ �ֵ鿡 ���� ó���̴�.
		�׶��� ����ð��� �������� �ʿ�� ���°�?
		���� ���ص� ���� ������ ����.
		������ 
		���� ������ ������ ������ ���ť�� �߰����ָ� �Ǹ�
		���ť���� ������ ����ð��� �����ִ°� �ʿ��ϴ�.
		�ʵ� 1�ʾ� �����ϰ� �� �ʿ�� ���°� ����.
		���ť�� �ִ� ���� ���۽ð��� ���� �ð��� ���̸�ŭ �����൵ �ȴ�.
		������ ���ť�� ���� ���ٸ� �ð��� 1�ʾ� �귯���Ѵ�.
	*/

}

// ���� ���� ó��.
QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
					  int *pServiceUserCount, int *pTotalWaitTime)
{

}

// ������ ���¸� ���??.
void printSimCustomer(int currentTime, SimCustomer customer)
{
	/*
		�� �� ��ü�� print
		���� ���� �ִ°�?
		ó���� ��� ������?
		ó���� ������ ������?
		���ť�� ������?
		�׷��� SimCustomer type�� ��� �ִ°�?
		LinkedQueue�� ���ο� member�� �߰��� �ʿ�� �ִ°�?
	*/
}

// ���?? ���� ���¸� ���??.
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
	/*
		��⿭�� �ִ� ������ ����Ѵ�.
		������ � ������ ��������ϴ°�?
		�׳� ����Ʈ�� �����൵ �Ǵ°�
	*/
}

// ���� �ùķ��̼� ���??(����?) ���??.
void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime)
{
	if (pWaitQueue == NULL)
		exit(EXIT_FAILURE);
	if (serviceUserCount < 0 || totalWaitTime < 0)
	{
		// message box need
		printf("totalWaitTime, serviceUserCount should be zero or natural number");
		exit(EXIT_FAILURE);
	}
	/*
		report �Լ��� ������ �ϴ°�?
		��ü ����� �����ִ� ���̶� ����
		
		�������� �����̾�����
		���� �������� ���԰�
		���� ������ �������� �Ǿ�����

		�� 1��� ó�� �ð��� ��ߴ���
		���

		������ ��� ��� �ð��� ��ߴ���?
	*/
}

// ���� ���� ó��.
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
	/*
		���ϴ� �Լ��ΰ�?
		���μ��� ��ü�� ����Ǵ� ���?
		�׷��ٸ� �������� ���� �ù����̼� ����� ����Ѵ�.

		���� �ùķ��̼� ����δ� ��� �ʿ��Ѱ�?
		�ؿ� �� �Լ��� ���⼭ ȣ���ҰŸ�
		processArrival �Լ� ��ü�� �ǹ̰� �ִ°�?
		� �ǵ��� �� �Լ��� �ִ°�?
		printReport
	*/
	

}