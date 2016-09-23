#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
*参考：http://blog.csdn.net/shinanhualiu/article/details/49279051
该题是对二叉树非递归遍历实现的理解，通过栈实现非递归遍历，每次Push则为前序遍历的结果，Pop则为后序遍历的结果，由前序和中序遍历可以得到后序遍历
例如：
由
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop

可得出：
前序遍历为：1 2 3 4 5 6
中序遍历为：3 2 4 1 6 5
可推出后序遍历：3 4 2 6 5 1

解法：
*该解法中要先递归右子树，再左子树
该题解法通过找到前序找到根节点，再从中序遍历中递归遍历右子树和左子树
将前序和中序遍历的结果入栈，将后序遍历的节点入栈，最后出栈的顺序则为后序遍历的顺序

*/




typedef struct Stack Stack;
struct Stack
{
	int *data;
	int top;
};

Stack *Create(int num);
void Push(int data, Stack *s);
int Pop(Stack *s);
void PostOrderTraveral(int pLeft,Stack *preOrder, int iLeft,  Stack *inOrder, Stack *postOrder, int length);
void Print(Stack *s);
int main(void)
{
	/*
	通过前序和中序遍历，可以得到二叉树
	在本题目中Push为前序遍历，Pop为后序遍历
	*/
	int num, i, data;
	char s[5];
	Stack *preOrder = NULL;
	Stack *tempPreOrder = NULL; //用于Pop出节点
	Stack *inOrder = NULL;
	Stack *postOrder = NULL;

	scanf("%d\n", &num);

	preOrder = Create(num);
	tempPreOrder = Create(num);
	inOrder = Create(num);
	postOrder = Create(num);

	//读取数据
	for (i = 0; i<2*num; i++)
	{
		scanf("%s", s);
		if (!strcmp("Push", s))  //Push为前序遍历
		{
			scanf("%d\n", &data);
			Push(data, preOrder);
			Push(data, tempPreOrder);
		}
		else
		{
			data = Pop(tempPreOrder);
			Push(data, inOrder);
		}
	}

	//后序遍历
	PostOrderTraveral(0, preOrder, 0, inOrder, postOrder, num);
	Print(postOrder);
	return 0;
}

Stack *Create(int num)
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->data = (int*)malloc(sizeof(int)*num);
	s->top = -1;
	return s;
}

void Push(int data, Stack *s)
{
	s->data[++s->top] = data;
}

int Pop(Stack *s)
{
	return s->data[s->top--];
}

void PostOrderTraveral(int pLeft, Stack *preOrder, int iLeft, Stack *inOrder, Stack *postOrder, int length)
{
	int root, i, L, R;  //L：左子树长度， R：有子树长度
	if (length == 0)
	{
		return 0;
	}
	if (length == 1)
	{
		root = preOrder->data[pLeft];
		Push(root, postOrder);
		return;
	}

	//找到根节点的下标
	root = preOrder->data[pLeft];
	Push(root, postOrder);
	i = 0;
	while (i<length)
	{
		if (inOrder->data[iLeft + i] == root)
		{
			break;
		}
		i++;
	}
	//计算root节点左右子树的长度
	L = i ;
	R = length - i - 1;
	//往右遍历
	PostOrderTraveral(pLeft + L + 1, preOrder, iLeft + L + 1, inOrder, postOrder, R);
	//往左遍历
	PostOrderTraveral(pLeft + 1, preOrder, iLeft, inOrder, postOrder, L);
	
}

void Print(Stack *s)
{
	int data;
	while (1)
	{
		data = Pop(s);
		if (s->top == -1)
		{
			printf("%d", data);
			break;
		}
		else
		{
			printf("%d ", data);
		}
	}
}