#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
*�ο���http://blog.csdn.net/shinanhualiu/article/details/49279051
�����ǶԶ������ǵݹ����ʵ�ֵ���⣬ͨ��ջʵ�ַǵݹ������ÿ��Push��Ϊǰ������Ľ����Pop��Ϊ��������Ľ������ǰ�������������Եõ��������
���磺
��
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

�ɵó���
ǰ�����Ϊ��1 2 3 4 5 6
�������Ϊ��3 2 4 1 6 5
���Ƴ����������3 4 2 6 5 1

�ⷨ��
*�ýⷨ��Ҫ�ȵݹ�����������������
����ⷨͨ���ҵ�ǰ���ҵ����ڵ㣬�ٴ���������еݹ������������������
��ǰ�����������Ľ����ջ������������Ľڵ���ջ������ջ��˳����Ϊ���������˳��

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
	ͨ��ǰ���������������Եõ�������
	�ڱ���Ŀ��PushΪǰ�������PopΪ�������
	*/
	int num, i, data;
	char s[5];
	Stack *preOrder = NULL;
	Stack *tempPreOrder = NULL; //����Pop���ڵ�
	Stack *inOrder = NULL;
	Stack *postOrder = NULL;

	scanf("%d\n", &num);

	preOrder = Create(num);
	tempPreOrder = Create(num);
	inOrder = Create(num);
	postOrder = Create(num);

	//��ȡ����
	for (i = 0; i<2*num; i++)
	{
		scanf("%s", s);
		if (!strcmp("Push", s))  //PushΪǰ�����
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

	//�������
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
	int root, i, L, R;  //L�����������ȣ� R������������
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

	//�ҵ����ڵ���±�
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
	//����root�ڵ����������ĳ���
	L = i ;
	R = length - i - 1;
	//���ұ���
	PostOrderTraveral(pLeft + L + 1, preOrder, iLeft + L + 1, inOrder, postOrder, R);
	//�������
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