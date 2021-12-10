#include <stdio.h>
#include <stdlib.h>
#include "simdef.h"
#include "simutil.h"

/*

- 대기큐에 들어오면 시작시간 기준으로 처리
- 현재 시간이 되었을때 그때 처리
- 그 다음 종료시간이 되면 다음 대기큐에 있는 작업이 시작시간이 되었을때 작업을 처리한다.
- 그런데 simdef.h에 정의한 데이터 타입은 언제 쓰는것인가?
- queue에 넣을때 사용하는 것으로 보인다.
- 전체 과정은 어떻게 되는가?
	- 시간이 흐른다
	- 현재 처리 중인 고객이 없으면
	- 매초마다 대기큐에 고객이 있는지 확인한다.
		- 대기큐에 고객이 있더라도 현재시간과 대조해서 시작해도 되는지 봐야한다.
		- 
	- 고객이 들어오면 대기큐에 추가한다.

- 은행 시스템
- 

- 프로그래머스 다리건너기와 비슷하다 생각.

*/

// 占쏙옙占쏙옙 占쏙옙占쏙옙 큐占쏙옙 占쏙옙占쏙옙 占쌩곤옙.
void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
	/*
		고객이 은행에 도착하고
		고객을 대기큐에 추가한다.
	*/
	pQueue->pFrontNode

}


// 占쏙옙占쏙옙 占쏙옙占쏙옙 처占쏙옙.
QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
	/*
		대기큐에서 고객의 시작시간이 현재시간 혹은 현재시간 이후인 노드를 빼어낸다.
		이후 서비스 처리
		시간은 매초 흐른다.
		QueueNode*를 리턴
		그런데 흐른 시간은 어떻게 감안하는가?
		대기큐에서 꺼내서 processServiceNodeStart함수에 보낸 쪽에서
		현재시간에서 현재처리해야할 노드의 처리시간을 더한다.
		그런데 문제는 처리 중에 들어오는 애들에 대한 처리이다.
		그때는 현재시간을 감안해줄 필요는 없는가?
		굳이 안해도 문제 없을거 같다.
		이유는 
		새로 들어오는 고객들은 무조건 대기큐에 추가해주면 되며
		대기큐에서 꺼낼때 현재시간을 더해주는게 필요하다.
		초도 1초씩 진행하게 할 필요는 없는거 같다.
		대기큐에 있는 고객의 시작시간과 현재 시간의 차이만큼 더해줘도 된다.
		하지만 대기큐에 고객이 없다면 시간이 1초씩 흘러야한다.
	*/

}

// 占쏙옙占쏙옙 占쏙옙占쏙옙 처占쏙옙.
QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
					  int *pServiceUserCount, int *pTotalWaitTime)
{

}

// 占쏙옙占쏙옙占쏙옙 占쏙옙占승몌옙 占쏙옙占??.
void printSimCustomer(int currentTime, SimCustomer customer)
{
	/*
		고객 그 자체를 print
		언제 쓸모가 있는가?
		처음에 들어 왔을때?
		처리가 끝나고 나갈때?
		대기큐에 있을때?
		그런데 SimCustomer type을 어디서 넣는가?
		LinkedQueue에 새로운 member로 추가할 필요는 있는가?
	*/
}

// 占쏙옙占?? 占쏙옙占쏙옙 占쏙옙占승몌옙 占쏙옙占??.
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
	/*
		대기열에 있는 고객들을 출력한다.
		고객들의 어떤 정보를 보여줘야하는가?
		그냥 리스트만 보여줘도 되는가
	*/
}

// 占쏙옙占쏙옙 占시뮬뤄옙占싱쇽옙 占쏙옙占??(占쏙옙占쏙옙?) 占쏙옙占??.
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
		report 함수는 무엇을 하는가?
		전체 결과를 보여주는 것이라 생각
		
		언제부터 시작이었는지
		고객은 언제부터 들어왔고
		서비스 시작은 언제부터 되었는지

		고객 1명당 처리 시간은 어떠했는지
		평균

		고객들의 평균 대기 시간은 어떠했는지?
	*/
}

// 占쏙옙占쏙옙 占쏙옙占쏙옙 처占쏙옙.
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
	/*
		뭘하는 함수인가?
		프로세스 자체가 종료되는 경우?
		그렇다면 종료이후 최종 시물레이션 결과를 출력한다.

		최종 시뮬레이션 결과로는 어떻게 필요한가?
		밑에 두 함수를 여기서 호출할거면
		processArrival 함수 자체는 의미가 있는가?
		어떤 의도로 이 함수가 있는가?
		printReport
	*/
	

}