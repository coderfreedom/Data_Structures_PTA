#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 101
/*
关键路径问题



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
void CriticalPath(Graph *g);

int stack2[MAXSIZE];
int top2;
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
	for (i = 1; i < N+1; i++)
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
	
	/*求解关键路径*/
	CriticalPath(g);


	return 0;
}

int TopSort(Graph *g)
{
	int top, i, count, v;
	int result;
	int *stack = NULL;
	EdgeNode *e = NULL;
	count = 0;
	result = 1; //假设有拓扑序
	/*初始化堆栈*/
	stack = (int*)malloc(sizeof(int)*g->vertexNum);
	top = -1;
	top2 = -1;
	for (i = 1; i < g->vertexNum+1; i++)
	{
		etv[i] = 0;
	}

	/*将入度为0的入栈*/
	for (i = 1; i < g->vertexNum+1; i++)
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
		stack2[++top2] = v;
		//printf("%d -> ", v);
		count++; //计算输出的顶点数
		
		//访问该点的所有邻接点
		for (e = g->graph[v].FirstEdge; e; e = e->next)
		{
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
		result = 0;
	}
	else
	{
		printf("%d\n", etv[g->vertexNum]);
	}

	return result;

}

void CriticalPath(Graph *g)
{
	int ete, lte; //活动最早和最晚发生时间
	int v, result, earliest;
	EdgeNode *e = NULL;
	earliest = 0;
	/*用拓扑排序得到事件的最早发生时间和stack2*/
	result = TopSort(g);
	if (result)
	{
		/*初始化ltv*/
		for (int i = 1; i < g->vertexNum+1; i++)
		{
			ltv[i] = etv[g->vertexNum];
		}

		/*计算事件的最晚发生时间ltv*/
		while (-1 != top2)
		{
			v = stack2[top2--];
			for (e = g->graph[v].FirstEdge; e; e = e->next)
			{
				if (ltv[e->adj] - e->weight < ltv[v])
				{
					ltv[v] = ltv[e->adj] - e->weight;
				}
			}
		}

		/*求ete和lte以及关键活动*/
		for (int i = 1; i < g->vertexNum+1; i++)
		{
			for (e = g->graph[i].FirstEdge; e; e = e->next)
			{
				ete = etv[i];
				lte = ltv[e->adj] - e->weight;
				if (ete == lte)
				{
					printf("%d->%d\n", i, e->adj);

				}
			}
		}
	}
	else
	{
		printf("0");
	}
	

}