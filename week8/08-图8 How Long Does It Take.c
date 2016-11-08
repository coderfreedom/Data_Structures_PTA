#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
/*
�����ֻҪ����¼������緢��ʱ��Ϳ����ˡ�����
ע�⣺�п����ж����ںͶ�����ڣ����Զ�etvҪѭ��������ֵ������



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
	
	/*����ͼ��Ϣ*/
	g = (Graph*)malloc(sizeof(Graph));
	scanf("%d %d", &N, &M);
	g->edgeNum = M;
	g->vertexNum = N;
	//��ʼ��ͼ
	for (i = 0; i < N; i++)
	{
		g->graph[i].FirstEdge = NULL;
		g->graph[i].in = 0;
	}
	//������Ϣ
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
	result = 1; //������������
	/*��ʼ����ջ*/
	stack = (int*)malloc(sizeof(int)*g->vertexNum);
	top = -1;
	for (i = 0; i < g->vertexNum; i++)
	{
		etv[i] = 0;
	}

	/*�����Ϊ0����ջ*/
	for (i = 0; i < g->vertexNum; i++)
	{
		if (0 == g->graph[i].in)
		{
			stack[++top] = i;
		}
	}

	/*ѭ��*/
	while (-1 != top)
	{
		v = stack[top--]; //��ջ
		
		//printf("%d -> ", v);
		count++; //��������Ķ�����
		
		//���ʸõ�������ڽӵ�
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
