#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
主要思路：
1、通过小顶堆构建Huffman树
实现：
Heap *CreateHeap(int capacity);
Tree *Huff(Heap *h);  //建立哈夫曼树

2、通过Huffman树计算最小编码长度
实现：
int WPL(Tree *huff, int height);

3、判断输入的编码是否符合要求（1、编码长度与Huffman编码长度相同 2、前缀编码）
实现：
int Count(Code *codes, int *flu, int N);  //计算权重，与第二步得到的wpl比较
int Judge(Code *codes, int N);  //前缀编码

*/

struct TreeNode 
{
	char c;
	int f;  //保存频率
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
Tree *Huff(Heap *h);  //建立哈夫曼树
TreeNode *Delete(Heap *h);
int WPL(Tree *huff, int height);
int Count(Code *codes, int *flu, int N);
int Judge(Code *codes, int N);

int main(void)
{
	int i, j, N, M, f, wpl, stuWPL; 
	int *flu = NULL; //flu保存频率
	char c;
	Heap *h = NULL;  //小顶堆
	Tree *huff = NULL; //哈夫曼树
	TreeNode *t = NULL; //树节点
	Code *codes = NULL; //存放哈夫曼码

	scanf("%d\n", &N);
	h = CreateHeap(N); //建造最小堆
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

	//建立哈夫曼树
	huff = Huff(h);

	wpl = WPL(huff, 0); //得到wpl


	scanf("%d\n", &M); //M表示学生数量
	//初始化codes
	codes = (Code*)malloc(sizeof(Code)*(N));
	for (i = 0; i < N; i++)
	{
		codes[i].code = (char*)malloc(sizeof(char)*(N+1));
	}
	//读入M个学生的数据
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%c %s\n", &codes[j].c, codes[j].code);
			//printf("%s", codes[j].code);
		}
		if (Count(codes, flu, N) == wpl) //如果权重相同，则比较前缀码
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