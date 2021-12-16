#include <stdio.h>
#include <stdlib.h>
#include "binsearchtree.h"

BinSearchTree* createBinSearchTree()
{
	BinSearchTree* newBinSearchTree;

	newBinSearchTree = (BinSearchTree*)malloc(sizeof(newBinSearchTree));
	if (newBinSearchTree == NULL)
		return (NULL);
	newBinSearchTree->pRootNode = NULL;
	return (newBinSearchTree);
}

int insertElementBST(BinSearchTree* pBinSearchTree, BinSearchTreeNode* element)
{
	/*
		#basic
		        5
			4      6
	     2     

		#1
		 		5
		    3       6
	     2     4 
		#2
					5
				4       6
			3     
		2
	  	#3
		 		5
		    4       6
	     2
			3
		C언어로 쉽게 풀어쓴 자료구조
		#3
	*/
	BinSearchTreeNode*	newBinSearchTreeNode;
	BinSearchTreeNode*	compareBinSearchTreeNode;

	if (pBinSearchTree == NULL)
		return (NULL);
	newBinSearchTreeNode = (BinSearchTreeNode*)malloc(sizeof(BinSearchTreeNode));
	if (newBinSearchTreeNode == NULL)
		return (NULL);
	newBinSearchTreeNode = element;
	// pointer로 넘어올떄 밖에서 동적할당한다는 가정이어야하는가?
	// 그냥 element만 넘겨주더라도 pointer로 해야 
	// 밖에서는 포인터로 넘겨줄뿐 동적할당은 안되어있다는 가정으로 간다. 즉, 스택영역에 존재하는 값
	compareBinSearchTreeNode = pBinSearchTree->pRootNode;
	while (compareBinSearchTreeNode->pRightChild || compareBinSearchTreeNode->pLeftChild)
	{
		// 이미 있는 key값
		if (compareBinSearchTreeNode->key == newBinSearchTreeNode->key)
		{
			free(newBinSearchTreeNode);
			// 현재 이 함수에서 동적할당하고 free하니까 지금 이 메모리 영역을 차후에 가리킬 일은 없다고 보고
			// NULL로 초기화 하지 않아도 될것인가?
			// 그래도 혹시나 가리킬수도 있으니까 dangling pointer를 방지하기 위해 NULL로 한다?
			// newBinSearchTreeNode 자체를 잃으니까 접근할 방법이 없으므로(모르는 영역에 막 임의 접근 아닌이상) 
			// 여기서는 NULL을 가리킬 필요가 없어보인다. (또한 이후 바로 NULL return이라 더더욱 필요없을 것으로 생각)
			return (NULL);
		}
		// 새로 들어온 노드의 키값이 현재 비교대상이 되는 노드가 키값이 보다 큰 경우
		else if (compareBinSearchTreeNode->key > newBinSearchTreeNode->key)
			compareBinSearchTreeNode = compareBinSearchTreeNode->pLeftChild;
		// 새로 들어온 노드가 비교대상의 노드보다 작은 경우
		else
			compareBinSearchTreeNode = compareBinSearchTreeNode->pRightChild;
	}
}

int deleteElementBST(BinSearchTree* pBinSearchTree, int key)
{
	BinSearchTreeNode*	newBinSearchTreeNode;
	if (pBinSearchTree == NULL)
		return (NULL);
	/*
		밑에 애들은 다 날림
		순회하면서 제거 
	*/
	
}

BinSearchTreeNode* searchRecursiveBST(BinSearchTree* pBinSearchTree, int key)
{
	/*
		post-order
		다른 순회도 다 쓴다?
		다른 순회도 다 구현해서 써야하는가?
	*/
}

BinSearchTreeNode* searchInternalRecursiveBST(BinSearchTreeNode* pTreeNode, int key)
{
	/*
		단말 노드는 냅둔다.
		밑에 자식노드가 있는 애들만 서치
		그런데 한쪽 자식만 있으면?
		1개만 있어도 있는거니까 걔까지는 포함

	*/

}

BinSearchTreeNode* searchBST(BinSearchTree* pBinSearchTree, int key)
{
	/*
		loop?
	*/
}

void deleteBinSearchTree(BinSearchTree* pBinSearchTree)
{
	/*
		순회하면서 다 제거하고 마지막에 가리키던 tree pointer도 free시키고 NULL을 가리킨다.
	*/

}

void deleteBinSearchTreeInternal(BinSearchTreeNode* pTreeNode)
{
	/*
		Internal의 의미가 

		Definition: A node of a tree that has one or more child nodes, 
		equivalently, one that is not a leaf.

		자식이 있는 노드들이다.
		그러면 부모노드들인데 그들을 삭제하면 단말노드들을 부모노드로 올려야한다.
		어떻게 가능하게 할 것인가?
		위에 것들을 삭제하니까 똑같이 다 삭제하는 것과 같은가?

		https://xlinux.nist.gov/dads/HTML/internalnode.html
	*/
}
