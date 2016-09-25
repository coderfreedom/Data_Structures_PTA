#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct AvlTreeNode AvlTreeNode;
typedef AvlTreeNode AvlTree;
struct AvlTreeNode
{
	int data;
	int flag;  //flag为0则未被访问，1为被访问过了
	AvlTreeNode *left;
	AvlTreeNode *right;
};

AvlTree *BuildTree(int N)
{
	int data;
	AvlTree *t = NULL;
	AvlTree *temp = NULL;
	AvlTreeNode *node = NULL;

	while (N--)
	{
		scanf("%d", &data);

		node = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));
		node->data = data;
		node->flag = 0;
		node->left = NULL;
		node->right = NULL;

		if (!t) //空树则建立根节点
		{
			t = node;
		}
		else
		{
			temp = t;
			while (temp)
			{
				if (data > temp->data) //往右边
				{
					if (temp->right)
					{
						temp = temp->right;
					}
					else
					{
						temp->right = node;
						temp = NULL;
					}
				}
				else //往左边
				{
					if (temp->left)
					{
						temp = temp->left;
					}
					else
					{
						temp->left = node;
						temp = NULL;
					}
				}
			}
		}
		
	}

	return t;
}

void Flag2Zeor(AvlTree *t)
{
	if (!t)
	{
		return;
	}
	t->flag = 0;
	Flag2Zeor(t->left);
	Flag2Zeor(t->right);
}

int main(void)
{
	int N, L, i, data, flag;  //flag在这里判断是否同一棵二叉树
	AvlTree *t = NULL;
	AvlTree *temp = NULL;
	while (1)
	{
		scanf("%d", &N);  //先取得N
		if (!N)
		{
			break;   //N为0，则表示输入结束
		}

		scanf("%d", &L);
		
		//建立一课AVL tree
		t = BuildTree(N);
		//判断
		while (L--)
		{
			i = N;
			//读入N个数
			flag = 1;  //先假设是同一棵二叉树
			while (i--)
			{
				temp = t;
				scanf("%d", &data);
				while (temp)
				{
					if (data == temp->data)
					{
						temp->flag = 1;
						temp = NULL;
					}
					else if(data > temp->data && temp->flag==1)
					{
						temp = temp->right;
					}
					else if (data < temp->data && temp->flag == 1)
					{
						temp = temp->left;
					}
					else
					{
						flag = 0;  //当前节点并未被访问，则表示不是同一棵二叉树
						break;
					}
				}
				
			}

			//判断
			if (flag)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}

			//将AVL tree的flag重新设为0；
			Flag2Zeor(t);
		}
	}
	return 0;
}
