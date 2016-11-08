#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
/*
这道题只要求出事件的最早发生时间就可以了。。。
注意：有可能有多个入口和多个出口，所以对etv要循环求出最大值。。。



*/
typedef struct EdgeNode
{
	int adj;
	int weight;
	struct EdgeNode *next;
}EdgeNode;
typedef struct VertexNode
{
	int in;
	EdgeNode *FirstEdge;
}VertexNode;
typedef struct Graph
{
	VertexNode graph[MAXSIZE];
	int vertexNum;
	int edgeNum;
}Graph;


int TopSort(Graph *g);


int etv[MAXSIZE];
int ltv[MAXSIZE];

int main(void)
{
	int N, M, i, v, w, weight;
	int result;
	Graph *g = NULL;
	EdgeNode *e = NULL;
	
	/*读入图信息*/
	g = (Graph*)malloc(sizeof(Graph));
	scanf("%d %d", &N, &M);
	g->edgeNum = M;
	g->vertexNum = N;
	//初始化图
	for (i = 0; i < N; i++)
	{
		g->graph[i].FirstEdge = NULL;
		g->graph[i].in = 0;
	}
	//读入信息
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &v, &w, &weight);
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adj = w;
		e->weight = weight;
		e->next = g->graph[v].FirstEdge;
		g->graph[v].FirstEdge = e;
		g->graph[w].in += 1;
	}
	
	
	result = TopSort(g);
	if (0 == result)
	{
		printf("Impossible");
	}
	else
	{
		result = etv[0];
		for (i = 0; i < g->vertexNum; i++)
		{
			if (result < etv[i])
			{
				result = etv[i];
			}
		}
		printf("%d", result);
	}


	return 0;
}

int TopSort(Graph *g)
{
	int top, i, count, v, earliest;
	int result;
	int *stack = NULL;
	EdgeNode *e = NULL;
	count = 0;
	earliest = 0;
	result = 1; //假设有拓扑序
	/*初始化堆栈*/
	stack = (int*)malloc(sizeof(int)*g->vertexNum);
	top = -1;
	for (i = 0; i < g->vertexNum; i++)
	{
		etv[i] = 0;
	}

	/*将入度为0的入栈*/
	for (i = 0; i < g->vertexNum; i++)
	{
		if (0 == g->graph[i].in)
		{
			stack[++top] = i;
		}
	}

	/*循环*/
	while (-1 != top)
	{
		v = stack[top--]; //出栈
		
		//printf("%d -> ", v);
		count++; //计算输出的顶点数
		
		//访问该点的所有邻接点
		for (e = g->graph[v].FirstEdge; e; e = e->next)
		{
			earliest += e->weight;
			if (0 == --g->graph[e->adj].in)
			{
				stack[++top] = e->adj;
			}
			if (etv[v] + e->weight > etv[e->adj])
			{
				etv[e->adj] = etv[v] + e->weight;
			}
		}
	}

	if (count != g->vertexNum)
	{
		earliest = -1;
		result = 0;
	}

	return result;

}
