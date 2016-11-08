#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 101
/*
�ؼ�·������



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
	
	/*����ͼ��Ϣ*/
	g = (Graph*)malloc(sizeof(Graph));
	scanf("%d %d", &N, &M);
	g->edgeNum = M;
	g->vertexNum = N;
	//��ʼ��ͼ
	for (i = 1; i < N+1; i++)
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
	
	/*���ؼ�·��*/
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
	result = 1; //������������
	/*��ʼ����ջ*/
	stack = (int*)malloc(sizeof(int)*g->vertexNum);
	top = -1;
	top2 = -1;
	for (i = 1; i < g->vertexNum+1; i++)
	{
		etv[i] = 0;
	}

	/*�����Ϊ0����ջ*/
	for (i = 1; i < g->vertexNum+1; i++)
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
		stack2[++top2] = v;
		//printf("%d -> ", v);
		count++; //��������Ķ�����
		
		//���ʸõ�������ڽӵ�
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
	int ete, lte; //������������ʱ��
	int v, result, earliest;
	EdgeNode *e = NULL;
	earliest = 0;
	/*����������õ��¼������緢��ʱ���stack2*/
	result = TopSort(g);
	if (result)
	{
		/*��ʼ��ltv*/
		for (int i = 1; i < g->vertexNum+1; i++)
		{
			ltv[i] = etv[g->vertexNum];
		}

		/*�����¼���������ʱ��ltv*/
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

		/*��ete��lte�Լ��ؼ��*/
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