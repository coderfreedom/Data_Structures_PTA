#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10000

typedef struct EdgeNode
{
	int adj;
	int weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VerNode
{
	EdgeNode *FirstEdge;
}Graph;

void UnWeighted(Graph *g, int *dist, int *path, int v);

int main(void)
{

	return 0;
}

void UnWeighted(Graph *g, int *dist, int *path, int v)
{
	int Queue[MaxSize];
	int front, rear;
	EdgeNode *w = NULL;
	front = rear = 0;

	dist[v] = 0;
	Queue[rear++] = v;

	while (front != rear)
	{
		v = Queue[front++];

		for (w = g[v].FirstEdge; w; w = w->next)
		{
			if (-1 == dist[w->adj])
			{
				Queue[rear++] = w->adj;
				dist[w->adj] = dist[v] + 1;
				path[w->adj] = v;
			}
			
		}
	}
}
