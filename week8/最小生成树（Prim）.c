#include <stdio.h>
#include <stdlib.h>

#define INFINITY 65535
#define MAXSIZE 10000

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
	Graph *g = NULL;
	Prim(g);
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

	/*初始化数据*/
	for (i = 0; i < graph->vertexNum; i++)
	{
		dist[i] = graph->graph[0][i];
		parent[i] = 0;
	}

	parent[0] = -1;
	dist[0] = 0;

	while (1)
	{
		v = FindMin(graph, dist);
		if (v == -1)  //v不存在
		{
			break;
		}

		totalWeight += dist[v];
		dist[v] = 0;
		count++;
		for (i = 0; i < graph->vertexNum; i++)
		{
			if (dist[i] != 0 && graph->graph[v][i] < dist[i])
			{
				dist[i] = graph->graph[v][i];
				parent[i] = v;
			}
		}
	}
}

int FindMin(Graph *graph, int *dist)
{
	int i, v, min;
	min = INFINITY; //存储找到的最小值
	
	for (i = 0; i < graph->vertexNum; i++)
	{
		if (dist[i] != 0 && dist[i] < min)
		{
			min = dist[i];
			v = i;
		}
	}

	if (min == INFINITY)
	{
		v = -1;  //-1表示未找到最小值
	}
	
	return v; 
}