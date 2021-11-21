#include <stdlib.h>
#include "arraylist.h"


int main(int argc, int argv[])
{
	/*
		t_ArratList	arr_node;

		arr_node = createALElement(argv[1], argv[2]);
	*/
	ArrayList		*first_AList;

	first_AList = createArrayList(42);

	return (0);
}

ArrayList* createArrayList(int maxElementCount)
{
	/*
		element의 최대 개수를 넘겨받는다.
	*/
	ArrayList		*currentArrayList;	
	ArrayListNode	*pElement;
	int				currentElementCount;

	currentElementCount = 0;
	currentArrayList->maxElementCount = maxElementCount;
	currentArrayList->currentElementCount = currentElementCount;
	currentArrayList->pElement = malloc(pElement *maxElementCount);
	return (currentArrayList);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
	int tmp;

	tmp = pList->pElement[position].data
	pList->pElement[position].data = element.data;
	/*
		새로 할당 사이즈 2~3배

		이미 값이 있는 특정위치에 넣는 것을 가정
		그렇게되면 뒤로 다 밀려야한다.
		뒤에서부터 한칸씩 뒤로 민다.
		하지만 꽉 찬 경우에는 어떻게 처리할 것인가?
		기존 위치의 값에 대체할것인가?		
		-
		array full 일때
		보통 원소를 넣을떄
		100개 짜리를 쓰다가 101번재
		새로 realloc
		기존 것 free해주고서 원소를 추가하는 방법
		

		// isArrayListFull
		if currentElementCount < position
			return (FALSE);
	*/
}

int removeALElement(ArrayList* pList, int position)
{
	/*
		중간 것을 지우면 바로 뒤에것부터 하나씩 앞으로 당겨온다.
		비어있는지 확인해야할 필요가 있는지?
	*/
	// pList->currentElementCount == 0	
	// pList->pElement[position].data
	// if currentElementCount-1 < position
	// 


}

ArrayListNode* getALElement(ArrayList* pList, int position)
{
	/*
		특정  index값 반환
		비어있으면? 그래도 반환
	*/
	return (&(pList->pElement[position]));
}

void clearArrayList(ArrayList* pList)
{
	/*
		array list를 삭제
		모든 요소를 1개씩 삭제한다.
		마지막인지 어떻게 알 것인가?
		siseof를 이용한다.
		NULL을 넣을 것인지
		사이즈를 별도로 알 것인지
		파라미터로 사이즈를 넘겨받지 않으니까
		마지막 표시를 별도로 한다.

		clear와 다른점
		clear는 arraylist의 모든 요소를 null로 처리
        [12,3,45,6]
        => [NULL, NULL, NULL, NULL]
		delete는 모든 요소를 null로 하고서 free한다.
		댕글링 포인터

	*/
}

void deleteArrayList(ArrayList* pList)
{
	
	/*
		원소전체를 초기화
		free
	*/
	
	while()
	free(pList->pElement);
	free(pList);
}


int isArrayListFull(ArrayList* pList)
{
	/*
		array list에 대한 pointer만 넘겨받는다.
		즉 어디가 끝인지가 안나온다.
		마지막인지 어떻게 알 것인가?
		\n을 넣을 것인지
		사이즈를 별도로 알 것인지
		파라미터로 사이즈를 넘겨받지 않으니까
		마지막 표시를 별도로 한다.
	*/
	// malloc 10 * (4)
	// maxElementCount == currentElementCount
	siZeof(pList.pElement);
	
}


void displayArrayList(ArrayList* pList)
{
	/*
		첫 요소부터 끝 요소까지 display
	*/
	int	idx;

	idx = 0;
	// 문제점 중간에만 비어있는 경우
	// 초기화하는 부분이 없었다.
	while (pList->pElement[idx].data)
	{
		printf("%d\n", pList->pElement[idx].data);
		idx++;
	}

}


int getArrayListLength(ArrayList* pList)
{
	/*
		길이 확인
		어떻게? siZeof 연산자 사용?
		그러면 초기 할당된 크기가 나오게 되지 않는가?
	*/

}

// resizing

/*
array list
logic == physical order

- array list create
- element add
- element eliminate
- etc..
- example

*/

