#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct Stack {
	int stack[MAX_SIZE+1];  //topָ��stack[0]����ʼ��stack[0]Ϊ0����ʾͷ���
	int top;
	int capacity;
}Stack;


int Judge(int M, int N, int K); //�жϺ���
Stack *Create(int capacity);
void Push(int element, Stack *s);
int Pop(Stack *s);
int IsFull(Stack *s);

int main(void)
{
	int M, N, K, i, result;

	scanf("%d %d %d", &M, &N, &K);
	
	//����K������
 	for (i = 0; i < K; i++)
	{
		//����Judge�����ж�
		result = Judge(M, N, K);

		if (result == 0)
		{
			if (i == K - 1)  //�ж��Ƿ�Ϊ���һ��
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
			if (i == K - 1)//�ж��Ƿ�Ϊ���һ��
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
	int i, j, num, index;  //numΪҪpush����, indexΪ����arr������
	int *arr = NULL;
	Stack *s = Create(M);  //MΪ���ڶ�ջ��С


	arr = (int*)malloc(sizeof(int)*N);  //�洢N����������
	//����N����
	for (j = 0; j < N; j++)
	{
		scanf("%d", arr + j);
	}

	//�����ж�
	num = 0; //numΪҪpush����
	for (index = 0; index < N; index++)
	{
		while (s->stack[s->top] < arr[index] && IsFull(s)==0)  //ע���ջ�Ĵ�С
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
			return 0;  //��ʾ�����ܵ�˳��
		}

	}
		


	free(s);
	return 1; //����ǿ��ܵ�˳���򷵻�1
}

Stack *Create(int capacity) //capΪջ�Ĵ�С  
{
	//topָ��stack[0]����ʼ��stack[0]Ϊ0����ʾͷ���
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