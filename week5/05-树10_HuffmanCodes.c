#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
��Ҫ˼·��
1��ͨ��С���ѹ���Huffman��
ʵ�֣�
Heap *CreateHeap(int capacity);
Tree *Huff(Heap *h);  //������������

2��ͨ��Huffman��������С���볤��
ʵ�֣�
int WPL(Tree *huff, int height);

3���ж�����ı����Ƿ����Ҫ��1�����볤����Huffman���볤����ͬ 2��ǰ׺���룩
ʵ�֣�
int Count(Code *codes, int *flu, int N);  //����Ȩ�أ���ڶ����õ���wpl�Ƚ�
int Judge(Code *codes, int N);  //ǰ׺����

*/

struct TreeNode 
{
	char c;
	int f;  //����Ƶ��
	struct TreeNode *left;
	struct TreeNode *right;
};
typedef struct TreeNode TreeNode;
typedef struct TreeNode Tree;

struct Heap
{
	TreeNode *data;
	int size;
	int capacity;
};
typedef struct Heap Heap;

struct Code
{
	char c;
	char *code;
};
typedef struct Code Code;

Heap *CreateHeap(int capacity);
void Insert(Heap *h, TreeNode *t);
Tree *Huff(Heap *h);  //������������
TreeNode *Delete(Heap *h);
int WPL(Tree *huff, int height);
int Count(Code *codes, int *flu, int N);
int Judge(Code *codes, int N);

int main(void)
{
	int i, j, N, M, f, wpl, stuWPL; 
	int *flu = NULL; //flu����Ƶ��
	char c;
	Heap *h = NULL;  //С����
	Tree *huff = NULL; //��������
	TreeNode *t = NULL; //���ڵ�
	Code *codes = NULL; //��Ź�������

	scanf("%d\n", &N);
	h = CreateHeap(N); //������С��
	flu = (int*)malloc(sizeof(int)*N); 
	for (i = 0; i < N; i++)
	{
		scanf("%c %d ", &c, &f);

		t = (TreeNode*)malloc(sizeof(TreeNode));
		t->c = c;
		t->f = f;
		t->left = NULL;
		t->right = NULL;

		flu[i] = f;
		Insert(h, t);
	}

	//������������
	huff = Huff(h);

	wpl = WPL(huff, 0); //�õ�wpl


	scanf("%d\n", &M); //M��ʾѧ������
	//��ʼ��codes
	codes = (Code*)malloc(sizeof(Code)*(N));
	for (i = 0; i < N; i++)
	{
		codes[i].code = (char*)malloc(sizeof(char)*(N+1));
	}
	//����M��ѧ��������
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%c %s\n", &codes[j].c, codes[j].code);
			//printf("%s", codes[j].code);
		}
		if (Count(codes, flu, N) == wpl) //���Ȩ����ͬ����Ƚ�ǰ׺��
		{
			if (Judge(codes, N))
			{
				if (i == M - 1)
				{
					printf("Yes");
				}
				else
				{
					printf("Yes\n");
				}
			}
			else
			{
				if (i == M - 1)
				{
					printf("No");
				}
				else
				{
					printf("No\n");
				}
			}
		}
		else
		{
			if (i == M - 1)
			{
				printf("No");
			}
			else
			{
				printf("No\n");
			}
		}
	}


	return 0;
}

Heap *CreateHeap(int capacity)
{
	Heap *h = NULL;

	h = (Heap*)malloc(sizeof(Heap));
	h->data = (TreeNode*)malloc(sizeof(TreeNode)*(capacity + 1));
	h->data[0].f = 0;
	h->capacity = capacity;
	h->size = 0;

	return h;
}

void Insert(Heap *h, TreeNode *t)
{
	int i;
	for (i = ++h->size; h->data[i / 2].f > t->f; i/=2)
	{
		h->data[i].f = h->data[i / 2].f;
		h->data[i].c = h->data[i / 2].c;
	}
	h->data[i] = *t;
}

TreeNode *Delete(Heap *h)
{
	int parent, child;
	TreeNode temp;
	TreeNode *item = NULL;

	item = (TreeNode*)malloc(sizeof(TreeNode));
	*item = h->data[1];
	temp = h->data[h->size--];

	for (parent = 1; parent * 2 <= h->size; parent = child)
	{
		child = parent * 2;
		if (child != h->size && h->data[child].f > h->data[child + 1].f)
		{
			child++;
		}
		if (temp.f < h->data[child].f)
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

Tree *Huff(Heap *h)
{
	TreeNode *huff = NULL;
	
	
	while (h->size > 1)
	{
		huff = (TreeNode *)malloc(sizeof(TreeNode));
		huff->left = Delete(h);
		huff->right = Delete(h);
		huff->f = huff->left->f + huff->right->f;

		Insert(h, huff);
	}
	huff = Delete(h);


	return huff;
}

int WPL(Tree *huff, int height)
{
	
	if (huff->left == NULL && huff->right == NULL)
	{
		return height*huff->f;
	}

	return WPL(huff->left, height + 1) + WPL(huff->right, height + 1);
}

int Count(Code *codes, int *flu, int N)
{
	int i, wpl;
	for (i = 0, wpl = 0; i < N; i++)
	{
		wpl += strlen(codes[i].code)*flu[i];
	}
	return wpl;
}

int Judge(Code *codes, int N)
{
	int i, j;
	char *big = NULL;
	char *small = NULL;
	for (i = 0; i < N-1; i++)
	{
		for (j = i + 1; j < N; j++)
		{
			if (strlen(codes[i].code) > strlen(codes[j].code))
			{
				big = codes[i].code;
				small = codes[j].code;
			}
			else
			{
				big = codes[j].code;
				small = codes[i].code;
			}
			if (strstr(big, small) == big)
			{
				return 0;
			}
			
		}
	}

	return 1;
}