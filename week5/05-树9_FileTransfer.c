#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Find(int c1, int c2, int *data);
void Union(int c1, int c2, int *data);

int main(void)
{
	int c1, c2, i, N, count;
	int *data = NULL;
	char c;

	scanf("%d", &N);
	data = (int*)malloc(sizeof(int)*(N + 1));
	data[0] = N;
	for (i = 1; i <= N; i++)
	{
		data[i] = -1;
	}


	scanf("%c", &c);
	while (c != 'S')
	{
		scanf("%d%d\n", &c1, &c2);
		if (c == 'C')
		{
			if (Find(c1, c2, data))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
		}
		if (c == 'I')
		{
			Union(c1, c2, data);
		}

		scanf("%c", &c);
	}

	for (i = 1, count = 0; i <= N; i++)
	{
		if (data[i] < 0)
		{
			count++;
		}
	}
	if (count == 1)
	{
		printf("The network is connected.");
	}
	else
	{
		printf("There are %d components.", count);
	}

	return 0;
}

int Find(int c1, int c2, int *data)
{
	while (data[c1] > 0)
	{
		c1 = data[c1];
	}
	while (data[c2] > 0)
	{
		c2 = data[c2];
	}

	return c1 == c2;
}

void Union(int c1, int c2, int *data)
{
	while (data[c1] > 0)
	{
		c1 = data[c1];
	}
	while (data[c2] > 0)
	{
		c2 = data[c2];
	}

	//比较规模( 
	if (c1 != c2)
	{
		if (data[c1] < data[c2])
		{
			data[c1] = data[c1] + data[c2];
			data[c2] = c1;
		}
		else
		{
			data[c2] = data[c1] + data[c2];
			data[c1] = c2;
		}
	}

}