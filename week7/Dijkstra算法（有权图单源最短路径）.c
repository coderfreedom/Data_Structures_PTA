#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10000
#define INFINITY 65535

typedef struct Graph
{
	int g[MaxSize][MaxSize];
	int vertexNum;
	int edgeNum;
}Graph;

void Dijkstra(Graph *g, int *path, int *dist, int v);
int FindMin(Graph *g, int *dist, int *collected);

int main(void)
{

	return 0;
}

void Dijkstra(Graph *g, int *path, int *dist, int s) 
{
	int collected[MaxSize];
	int i, v, w;
	/*初始化数据*/
	for (w = 0; w < g->vertexNum; w++)
	{
		dist[w] = g->g[s][w];
		path[w] = -1;
		collected[w] = 0;
	}
	dist[s] = 0;
	collected[s] = 1;

	while (1)
	{
		v = FindMin(g, dist, collected);
		if (-1 == v)
		{
			break;
		}

		collected[v] = 1; //收录v
		for (w = 0; w < g->vertexNum; w++)
		{
			if (-1 == collected[w] && g->g[v][w] < INFINITY)
			{
				if (g->g[v][w] < 0) //有负值圈，无法解决，返回
				{
					return;
				}
				if ((dist[v] + g->g[v][w]) < dist[w])
				{
					dist[w] = dist[v] + g->g[v][w]; //更新dist[w]
					path[w] = v; //更新s->w的距离
				}
			}
		}
	}
}

int FindMin(Graph *g, int *dist, int *collected)
{
	int v, w, min;
	min = INFINITY;
	for (w = 0; w < g->vertexNum; w++)  //找dist里面的最小值
	{
		if (-1 == collected[w] && dist[w] < min) //没有被访问
		{
			min = dist[w]; //将最小值存在min里
			v = w;
		}
	}
	if (min == INFINITY)
	{
		return -1; //没有最小值了
	}

	return v;  //返回最小值
}