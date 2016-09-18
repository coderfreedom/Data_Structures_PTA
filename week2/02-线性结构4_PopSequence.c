#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct Stack {
	int stack[MAX_SIZE+1];  //top指向stack[0]，初始化stack[0]为0，表示头结点
	int top;
	int capacity;
}Stack;


int Judge(int M, int N, int K); //判断函数
Stack *Create(int capacity);
void Push(int element, Stack *s);
int Pop(Stack *s);
int IsFull(Stack *s);

int main(void)
{
	int M, N, K, i, result;

	scanf("%d %d %d", &M, &N, &K);
	
	//读入K组数据
 	for (i = 0; i < K; i++)
	{
		//调用Judge函数判断
		result = Judge(M, N, K);

		if (result == 0)
		{
			if (i == K - 1)  //判断是否为最后一组
			{
				printf("NO");
			}
			else
			{
				printf("NO\n");
			}
		}
		else
		{
			if (i == K - 1)//判断是否为最后一组
			{
				printf("YES");
			}
			else
			{
				printf("YES\n");
			}
		}
	}

	
	
	return 0;
}

int Judge(int M, int N, int K)
{
	int i, j, num, index;  //num为要push的数, index为数组arr的索引
	int *arr = NULL;
	Stack *s = Create(M);  //M为现在堆栈大小


	arr = (int*)malloc(sizeof(int)*N);  //存储N个数的数组
	//读入N个数
	for (j = 0; j < N; j++)
	{
		scanf("%d", arr + j);
	}

	//进行判断
	num = 0; //num为要push的数
	for (index = 0; index < N; index++)
	{
		while (s->stack[s->top] < arr[index] && IsFull(s)==0)  //注意堆栈的大小
		{
			num++;

			Push(num, s);
		}

		if (s->stack[s->top] == arr[index])
		{
			Pop(s);
		}
		else
		{
			free(s);
			return 0;  //表示不可能的顺序
		}

	}
		


	free(s);
	return 1; //如果是可能的顺序，则返回1
}

Stack *Create(int capacity) //cap为栈的大小  
{
	//top指向stack[0]，初始化stack[0]为0，表示头结点
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->top = 0;
	s->stack[s->top] = 0;
	s->capacity = capacity;

	return s;
}

void Push(int element, Stack *s)
{
	s->stack[++s->top] = element;
}
int Pop(Stack *s)
{
	int element;
	element = s->stack[s->top--];

	return element;
}

int IsFull(Stack *s)
{
	if (s->top == s->capacity)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}