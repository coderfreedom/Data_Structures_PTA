#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct AvlNode AvlNode;
typedef struct AvlNode AvlTree;
struct AvlNode
{
	int data;
	int height;
	AvlNode *left;
	AvlNode *right;
};

AvlTree *Insert(int data, AvlTree *t);
int GetHeight(AvlTree *t);
AvlTree *SingleRotateWithLeft(AvlTree *t);
AvlTree *SingleRotateWithRight(AvlTree *t);
AvlTree *DoubleRotateWithLeft(AvlTree *t);
AvlTree *DoubleRotateWithRight(AvlTree *t);

int main(void)
{
	int num, data;
	AvlTree *t = NULL;
	scanf("%d", &num);
	if (num)
	{
		while (num--)
		{
			scanf("%d", &data);
			t = Insert(data, t);
		}
	}
	printf("%d", t->data);
	return 0;
}

AvlTree *Insert(int data, AvlTree *t)
{
	if (!t)
	{
		t = (AvlNode*)malloc(sizeof(AvlNode));
		t->data = data;
		t->left = NULL;
		t->right = NULL;
		t->height = 0;
	}
	else
	{
		if (data < t->data)  //往左
		{
			t->left = Insert(data, t->left);
			if (GetHeight(t->left) - GetHeight(t->right) == 2)
			{
				if (data < t->left->data)
				{
					t = SingleRotateWithLeft(t);  //左左单旋转
				}
				else
				{
					t = DoubleRotateWithLeft(t); //左右双旋转
				}
			}

		}
		else //往右
		{
			t->right = Insert(data, t->right);
			if (GetHeight(t->right) - GetHeight(t->left) == 2)
			{
				if (data > t->right->data)
				{
					t = SingleRotateWithRight(t); //右右单旋转
				}
				else
				{
					t = DoubleRotateWithRight(t); //右左双旋转
				}
			}
		}
	}
	
	
	t->height = (GetHeight(t->right) > GetHeight(t->left)? GetHeight(t->right) : GetHeight(t->left)) + 1;
	return t;
}

int GetHeight(AvlTree *t)
{
	if (!t)
	{
		return -1;
	}

	return t->height;
}

AvlTree *SingleRotateWithLeft(AvlTree *t)
{
	AvlNode *temp = t->left;
	t->left = temp->right;
	temp->right = t;
	//更新高度
	t->height = (GetHeight(t->left) > GetHeight(t->right) ? GetHeight(t->left) : GetHeight(t->right)) + 1;
	temp->height = (GetHeight(temp->left) > GetHeight(temp->right) ? GetHeight(temp->left) : GetHeight(t->right)) + 1;


	return temp;
}
AvlTree *SingleRotateWithRight(AvlTree *t)
{
	AvlNode *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	//更新高度
	t->height = (GetHeight(t->left) > GetHeight(t->right) ? GetHeight(t->left) : GetHeight(t->right)) + 1;
	temp->height = (GetHeight(temp->left) > GetHeight(temp->right) ? GetHeight(temp->left) : GetHeight(t->right)) + 1;
	return temp;
}
AvlTree *DoubleRotateWithLeft(AvlTree *t)
{
	t->left = SingleRotateWithRight(t->left);
	t = SingleRotateWithLeft(t);

	return t;
}
AvlTree *DoubleRotateWithRight(AvlTree *t)
{
	t->right = SingleRotateWithLeft(t->right);
	t = SingleRotateWithRight(t);

	return t;
}