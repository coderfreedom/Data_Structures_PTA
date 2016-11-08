#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 65535
#define MAXSIZE 1001

typedef struct Graph
{
	int graph[MAXSIZE][MAXSIZE];
	int vertexNum;
	int edgeNum;
}Graph;

int Prim(Graph *graph);
int FindMin(Graph *graph, int *dist);

int main(void)
{
	int N, M, i, v, w, weight, totalWeight;
	Graph *g = NULL;

	/*��������*/
	g = (Graph*)malloc(sizeof(Graph));
	//��ʼ��ͼ
	for (v = 0; v < MAXSIZE; v++)
	{
		for (w = 0; w < MAXSIZE; w++)
		{
			if (w == v)
			{
				g->graph[v][w] = 0;
			}
			else
			{
				g->graph[v][w] = INFINITY;
			}
		}
	}
	scanf("%d %d", &N, &M);
	g->vertexNum = N;
	g->edgeNum = M;
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &v, &w, &weight);
		g->graph[v][w] = weight;
		g->graph[w][v] = weight;
	}

	/*����*/
	totalWeight = Prim(g);
	if (totalWeight == -1)
	{
		printf("-1");
	}
	else
	{
		printf("%d", totalWeight);
	}

	return 0;
}

int Prim(Graph *graph)
{
	int parent[MAXSIZE];
	int dist[MAXSIZE];
	int totalWeight;
	int i, v, count;
	totalWeight = 0;
	count = 0;

	/*��ʼ������*/
	for (i = 2; i < graph->vertexNum + 1; i++)
	{
		dist[i] = graph->graph[1][i];
		parent[i] = 1;
	}

	parent[1] = -1;
	dist[1] = 0;
	count++; //��1��¼��mst��

	while (1)
	{
		v = FindMin(graph, dist);
		if (v == -1)  //v������
		{
			break;
		}

		totalWeight += dist[v];
		dist[v] = 0;
		count++;  //��v��¼��mst��
		for (i = 2; i < graph->vertexNum + 1; i++)
		{
			if (dist[i] != 0 && graph->graph[v][i] < dist[i]) 
			{
				dist[i] = graph->graph[v][i];
				parent[i] = v;
			}
		}
	}

	if (count != graph->vertexNum)
	{
		totalWeight = -1;
	}

	return totalWeight;
}

int FindMin(Graph *graph, int *dist)
{
	int i, v, min;
	min = INFINITY; //�洢�ҵ�����Сֵ
	
	for (i = 2; i < graph->vertexNum + 1; i++)
	{
		if (dist[i] != 0 && dist[i] < min)
		{
			min = dist[i];
			v = i;
		}
	}

	if (min == INFINITY)
	{
		v = -1;  //-1��ʾδ�ҵ���Сֵ
	}
	
	return v; 
}