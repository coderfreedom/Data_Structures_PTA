#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct HeapNode
{
	int *data;
	int size;
	int capacity;
};
typedef struct HeapNode HeapNode;
typedef HeapNode Heap;

Heap *CreateHeap(int capacity);
int IsFull(Heap *h);
int IsEmpty(Heap *h);
int Delete(Heap *h);
void BuildHeap(Heap *h);
void PercDown(Heap *h, int p);
void Insert(Heap *h, int temp);

int main(void)
{
	Heap *h = NULL;
	int *rote = NULL;
	int N, M, i, index, temp;
	scanf("%d%d", &N, &M);

	h = CreateHeap(N);
	h->size = 0;
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &temp);
		Insert(h, temp);
	}
	//BuildHeap(h);

	rote = (int*)malloc(sizeof(int)*M);
	for (i = 0; i < M; i++)
	{
		scanf("%d", &rote[i]);
	}

	for (i = 0; i < M; i++)
	{
		index = rote[i];
		printf("%d", h->data[index]);
		while (index = index / 2)
		{
			printf(" %d", h->data[index]);
		}
		if (i != M - 1)
		{
			printf("\n");
		}
	}

	return 0;
}

Heap *CreateHeap(int capacity)
{
	Heap *h = (Heap*)malloc(sizeof(HeapNode));

	h->data = (int*)malloc(sizeof(int)*(capacity+1));
	h->data[0] = -10001;
	h->size = 0;
	h->capacity = capacity;

	return h;
}

int IsFull(Heap *h)
{
	return h->size == h->capacity;
}

int IsEmpty(Heap *h)
{
	return h->size == 0;
}


int Delete(Heap *h)
{
	int parent, child;
	int item, temp;

	if (IsEmpty(h))
	{
		printf("ЮЊПе");
		return -1;
	}

	item = h->data[1];

	temp = h->data[h->size--];
	for (parent = 1; parent * 2 <= h->size; parent = child)
	{
		child = parent * 2;

		if (child < h->size && h->data[child] > h->data[child + 1])
		{
			child++;
		}

		if (temp < h->data[child])
		{
			break;
		}
		else
		{
			h->data[parent] = h->data[child];
		}
	}
	h->data[parent] = temp;

	return item;
}

void PercDown(Heap *h, int p)
{
	int parent, child;
	int temp;
	
	temp = h->data[p];

	for (parent = p; parent * 2 < h->size; parent = child)
	{
		child = parent * 2;
		if (child < h->size && h->data[child] > h->data[child + 1])
		{
			child++;
		}

		if (temp < h->data[child])
		{
			break;
		}
		else
		{
			h->data[parent] = h->data[child];
		}
	}
	h->data[parent] = temp;
}

void BuildHeap(Heap *h)
{
	int i;
	for (i = h->size / 2; i > 0; i--) 
	{
		PercDown(h, i);
	}
}

void Insert(Heap *h, int temp)
{
	int i;
	for (i = ++h->size; h->data[i / 2] > temp; i /= 2)
	{
		h->data[i] = h->data[i / 2];
	}
	h->data[i] = temp;
}