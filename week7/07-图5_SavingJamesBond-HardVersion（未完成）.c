#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxSize 100

typedef struct Pos
{
	int x;
	int y;
}Pos;

int FirstJump(int v);
int BFS(int v);
int IsSafe(int v);
int Jump(int v, int w);
int Judge(int tempV, int v);
int Not(int x, int y);


Pos pos[MaxSize];
int record[2];
int N, D;
int path1[MaxSize];
int path2[MaxSize];
int main(void)
{
	int i, j, result, tempDepth, tempV, x, y;
	tempDepth = 65535;
	result = 0;
	x = y = 0;
	/*∂¡»Î ˝æ›*/
	scanf("%d %d", &N, &D);
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &x, &y);
		if (abs(x)*abs(y) >= 2500 || Not(x, y)==0)
		{
			N--;
			i--;
		}
		else
		{
			pos[i].x = x;
			pos[i].y = y;
		}
		
	}
	if (D >= 42.5)
	{
		result = 1;
		printf("1");
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			if (FirstJump(i))
			{
				result = BFS(i);
			}
			if (1 == result)
			{
				if (tempDepth > record[1])
				{
					tempDepth = record[1];
					tempV = i;
					for (j = 0; j < MaxSize; j++)
					{
						path2[j] = path1[j];
					}
				}
				else if (tempDepth == record[1] && Judge(tempV, i))
				{
					tempV = i;
					for (j = 0; j < MaxSize; j++)
					{
						path2[j] = path1[j];
					}
				}
			}
		}
		if (result == 0)
		{
			printf("0");

		}
		else
		{
			printf("%d\n", tempDepth + 2);
			i = record[0];
			j = 0;
			while (path2[i] != -1)
			{
				path1[j] = i;
				i = path2[i];
				j++;
			}
			path1[j] = i;
			while (j >= 0)
			{
				printf("%d %d\n", pos[path1[j]].x, pos[path1[j]].y);
				j--;
			}
		}
		
	}
	

	return 0;
}

int FirstJump(int v)
{
	return (pos[v].x*pos[v].x + pos[v].y*pos[v].y) <= ((D + 7.5)*(D + 7.5));
}



int BFS(int s)
{
	int depth, cur, last, tail, v, w, result, i;
	int visited[MaxSize] = { 0 };
	int queue[MaxSize];
	int front, rear;
	front = rear = 0;
	depth = 1;
	visited[s] = 1;
	cur = last = s;
	queue[rear++] = s;
	result = 0;

	for (i = 0; i < MaxSize; i++)
	{
		path1[i] = -1;
	}

	while (front != rear)
	{
		v = queue[front++];
		if (IsSafe(v))
		{
			record[0] = v;
			record[1] = depth;
			result = 1;
			break;
		}
		for (w = 0; w < N; w++)
		{
			if (Jump(v, w) && visited[w]!=1)
			{
				queue[rear++] = w;
				visited[w] = 1;
				tail = w;
				path1[w] = v;
			}
		}
		if (cur == last)
		{
			depth++;
			last = tail;
		}
	}


	return result;
}

int IsSafe(int v)
{
	int result;
	result = 0;
	if (pos[v].x + D >= 50 || pos[v].y + D >= 50 || pos[v].x - D <= -50 || pos[v].y - D <= -50)
	{
		result = 1;
	}
	return result;
}

int Jump(int v, int w)
{
	return ((pos[v].x - pos[w].x)*(pos[v].x - pos[w].x) + (pos[v].y - pos[w].y)*(pos[v].y - pos[w].y)) <= (D*D);
}

int Judge(int tempV, int v)
{
	return (pos[tempV].x*pos[tempV].x + pos[tempV].y*pos[tempV].y) > (pos[v].x*pos[v].x + pos[v].y*pos[v].y);
}


int Not(int x, int y)
{
	return (x*x+y*y) > (7.5*7.5);
}