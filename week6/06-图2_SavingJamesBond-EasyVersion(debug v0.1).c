#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef int WeightType;
typedef struct DataType
{
	int x;
	int y;
}DataType;
typedef struct Graph
{
	int iVertexNum;
	DataType tData[MaxSize];
}Graph;

int IsSafe(Graph *g, int v, int M);
int Compute(Graph *g, int v, int w, int M);
int DFS(Graph *g, int i, int N, int M);
int FirstJump(Graph *g, int i, int M);

int iVisited[MaxSize] = { 0 };

int main(void)
{
	int N, M, i, result;
	Graph *g = NULL;

	/*读入数据*/
	scanf("%d %d", &N, &M);
	g = (Graph*)malloc(sizeof(Graph)); //建立图
	g->iVertexNum = N;
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &g->tData[i].x, &g->tData[i].y); //读入鳄鱼的坐标
	}

	/*深度优先搜索*/
	result = 0;
	for (i = 0; i < N; i++)
	{
		if (iVisited[i] == 0 && FirstJump(g, i, M))
		{
			result = DFS(g, i, N, M);
			if (result == 1)
			{
				break;
			}
		}
	}

	if (result == 1)
	{
		printf("Yse\n");
	}
	else
	{
		printf("No\n");
	}

	return 0;
}

int IsSafe(Graph *g, int v, int M)
{
	int result;
	result = 0;
	/*
	if (g->tData[v].x > 0)
	{
		result = (50 - g->tData[v].x) <= M;
	}
	if (g->tData[v].y > 0 && result == 0)
	{
		result = (50 - g->tData[v].y) <= M;
	}
	if (g->tData[v].x < 0 && result == 0)
	{
		result = (50 + g->tData[v].x) <= M;
	}
	if (g->tData[v].y < 0 && result == 0)
	{
		result = (50 + g->tData[v].y) <= M;
	}
	*/
	if (g->tData[v].x + M >= 50 || g->tData[v].y + M >= 50 || g->tData[v].x - M <= -50 || g->tData[v].y - M <= -50)
	{
		result = 1;
	}

	return result;
}
int Compute(Graph *g, int v, int w, int M)
{
	int x, y;
	x = g->tData[v].x - g->tData[w].x;
	y = g->tData[v].y - g->tData[w].y;

	return (x*x + y*y) <= M*M;
}

int DFS(Graph *g, int i, int N, int M)
{
	int result, j;
	
	iVisited[i] = 1;
	result = 0;
	if (IsSafe(g, i, M))
	{
		result = 1;
	}
	else
	{
		for (j = 0; j < N; j++)
		{
			if (iVisited[j] == 0 && Compute(g, i, j, M)) //如果未被访问，且
			{
				result = DFS(g, j, N, M);
				if (result == 1)
				{
					break;
				}
			}
		}
	}


	return result;
}

int FirstJump(Graph *g, int i, int M)
{
	return (g->tData[i].x*g->tData[i].x + g->tData[i].y * g->tData[i].y) <= (7.5+M)*(7.5 + M);
}