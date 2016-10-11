#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

void PreorderTraversal(BinTree BST);
void InorderTraversal(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}

void PreorderTraversal(BinTree BST)
{
	if (!BST)
	{
		return;
	}
	printf(" %d", BST->Data);
	PreorderTraversal(BST->Left);
	PreorderTraversal(BST->Right);
}
void InorderTraversal(BinTree BST)
{
	if (!BST)
	{
		return;
	}
	InorderTraversal(BST->Left);
	printf(" %d", BST->Data);
	InorderTraversal(BST->Right);

}

/* 你的代码将被嵌在这里 */

BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST)
	{
		BST = (BinTree*)malloc(sizeof(struct TNode));
		BST->Left = BST->Right = NULL;
		BST->Data = X;
	}
	if (X > BST->Data)
	{
		BST->Right = Insert(BST->Right, X);
	}
	else if(X < BST->Data)
	{ 
		BST->Left = Insert(BST->Left, X);
	}
	
	return BST;
}




BinTree Delete(BinTree BST, ElementType X)
{
	Position temp = NULL;
	if (!BST)
	{
		printf("Not Found\n");
		return NULL;
	}

	if (X > BST->Data)
	{
		BST->Right = Delete(BST->Right, X);
	}
	else if (X < BST->Data)
	{
		BST->Left = Delete(BST->Left, X);
	}
	else if (BST->Left && BST->Right)
	{
		temp = FindMin(BST->Right);
		BST->Data = temp->Data;
		BST->Right = Delete(BST->Right, temp->Data);
	}
	else
	{
		temp = BST;
		if (BST->Left==NULL)
		{
			BST = BST->Right;
		}
		else if(BST->Right == NULL)
		{
			BST = BST->Left;
		}
		free(temp);
	}

	return BST;
}

Position Find(BinTree BST, ElementType X)
{
	if (!BST)
	{
		return NULL;
	}

	if (X > BST->Data)
	{
		return Find(BST->Right, X);
	}
	else if (X < BST->Data)
	{
		return Find(BST->Left, X);
	}
	else
	{
		return BST;
	}


}

Position FindMin(BinTree BST)
{
	if (!BST)
	{
		return NULL;
	}

	if (BST->Left == NULL)
	{
		return BST;
	}
	else
	{
		return FindMin(BST->Left);
	}
}

Position FindMax(BinTree BST)
{
	if (!BST)
	{
		return NULL;
	}
	if (BST->Right == NULL)
	{
		return BST;
	}
	else
	{
		return FindMax(BST->Right);
	}
}