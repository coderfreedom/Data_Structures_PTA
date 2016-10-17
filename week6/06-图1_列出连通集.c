#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{
	int queue[11];
	int top;
	int rear;
}Queue;

int iGraph[10][10] = { 0 };
int visited[10] = {0};
void DFS(int i, int num);
void BFS(int i, int num, Queue *q);
void InitQueue(Queue *q);
void EnQueue(Queue *q, int i);
int DeQueue(Queue *q);
int main(void)
{
	int N, E, i, v1, v2;
	Queue *q = NULL;

	scanf("%d %d", &N, &E);

	for (i = 0; i < E; i++)
	{
		scanf("%d %d", &v1, &v2);
		iGraph[v1][v2] = 1;
		iGraph[v2][v1] = 1;
	}

	//深度优先遍历
	for (i = 0; i < N; i++)
	{
		if (visited[i] == 0)
		{
			printf("{");
			DFS(i, N);
			printf(" }\n");

		}
		
	}

	/*BFS*/
	//create queue
	q = (Queue*)malloc(sizeof(Queue));
	for (i = 0; i < N; i++)
	{
		visited[i] = 0;
	}
	//BFS
	for (i = 0; i < N; i++)
	{
		
		if (visited[i] == 0)
		{
			InitQueue(q);
			printf("{");
			BFS(i, N, q);
			if (i == N - 1)
			{
				printf(" }");
			}
			else
			{
				printf(" }\n");
			}
			
		}
	}

	return 0;
}

void DFS(int i, int num)
{
	int j;
	visited[i] = 1;
	printf(" %d", i);
	for (j = 0; j < num; j++)
	{
		if (visited[j] == 0 && iGraph[i][j] == 1)
		{
			DFS(j, num);
		}
	}
}

void BFS(int i, int num, Queue *q)
{
	int v, w;
	printf(" %d", i);
	visited[i] = 1;
	//入队
	EnQueue(q, i);
	while (q->top != q->rear) //队列不为空
	{
		v = DeQueue(q);
		for (w = 0;  w < num; w++)
		{
			if (visited[w] == 0 && iGraph[v][w] == 1)
			{
				visited[w] = 1;
				printf(" %d", w);
				EnQueue(q, w);
			}
		}
	}
}

void InitQueue(Queue *q)
{
	q->top = q->rear = 0;
}
void EnQueue(Queue *q, int i)
{
	q->queue[q->rear] = i;
	q->rear = (q->rear + 1) % 11;
}
int DeQueue(Queue *q)
{
	int i;
	i = q->queue[q->top];
	q->top = q->top + 1 % 11;
	return i;
}