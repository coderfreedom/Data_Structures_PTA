#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10001

/*
/注意为无向图，所以初始化图要赋值两次
/
/
*/

/*使用邻接表存储图*/
typedef struct AdjNode  //邻接结点
{
	int iAdj;  //下标
	struct AdjNode *next;
}AdjNode;
typedef struct VertexNode //头结点
{
	AdjNode *FirstEdge;  //第一个邻接点
}VertexNode;
typedef struct Queue
{
	int queue[MaxSize];
	int rear;
	int front;
}Queue;

int BFS(int i, int N);
void EnQueue(int i);
int DeQueue(void);

VertexNode tGraph[MaxSize]; //图的全局变量
int iVisited[MaxSize];  //标记已访问结点全局变量
Queue tQueue; //队列全局变量


int main(void)
{
	int N, M, i, j, v, w, count;
	AdjNode *tAdj = NULL;

	/*读入数据*/
	scanf("%d %d", &N, &M);
	//初始化图
	for (i = 1; i < N + 1; i++)
	{
		tGraph[i].FirstEdge = NULL;
	}
	//读入结点数据
	for (i = 0; i < M; i++)
	{
		scanf("%d %d", &v, &w); //相连的节点
		tAdj = (AdjNode*)malloc(sizeof(AdjNode)); //新建邻接点
		tAdj->iAdj = w;  //邻接点下标
		tAdj->next = tGraph[v].FirstEdge;
		tGraph[v].FirstEdge = tAdj;
		//对于无向图，还要<w, v>插入
		tAdj = (AdjNode*)malloc(sizeof(AdjNode));
		tAdj->iAdj = v; //邻接点下标
		tAdj->next = tGraph[w].FirstEdge;
		tGraph[w].FirstEdge = tAdj;
	}

	/*进行BFS*/
	for (i = 1; i < N + 1; i++)
	{
		//将iVisited数组初始化
		for (j = 1; j < N + 1; j++)
		{
			iVisited[j] = 0;
		}
		//BFS
		count = BFS(i, N);  //返回有联系的节点数量
		printf("%d: %.2f%%\n", i, (count*1.0) / N * 100);
	}

	return 0;
}

int BFS(int i, int N)
{
	int count, level, last, tail, v;
	AdjNode *adj = NULL;
	count = 1;
	level = 0;
	last = i;
	

	/*初始化队列*/
	tQueue.front = tQueue.rear = 0;

	iVisited[i] = 1;
	EnQueue(i);
	while (tQueue.front != tQueue.rear)
	{
		i = DeQueue();
		for (adj = tGraph[i].FirstEdge; adj; adj = adj->next)
		{
			if (iVisited[adj->iAdj] == 0)
			{
				iVisited[adj->iAdj] = 1;
				EnQueue(adj->iAdj);
				count++;
				tail = adj->iAdj;
			}
			
		}
		if (i == last)
		{
			level++;
			last = tail;
		}
		if (level == 6)
		{
			break;
		}
	}

	return count;
}

void EnQueue(int i)
{
	tQueue.queue[tQueue.rear++] = i;
}

int DeQueue(void)
{
	return tQueue.queue[tQueue.front++];
}