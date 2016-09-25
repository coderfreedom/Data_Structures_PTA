#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct AvlTreeNode AvlTreeNode;
typedef AvlTreeNode AvlTree;
struct AvlTreeNode
{
	int data;
	int flag;  //flagΪ0��δ�����ʣ�1Ϊ�����ʹ���
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

		if (!t) //�����������ڵ�
		{
			t = node;
		}
		else
		{
			temp = t;
			while (temp)
			{
				if (data > temp->data) //���ұ�
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
				else //�����
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
	int N, L, i, data, flag;  //flag�������ж��Ƿ�ͬһ�ö�����
	AvlTree *t = NULL;
	AvlTree *temp = NULL;
	while (1)
	{
		scanf("%d", &N);  //��ȡ��N
		if (!N)
		{
			break;   //NΪ0�����ʾ�������
		}

		scanf("%d", &L);
		
		//����һ��AVL tree
		t = BuildTree(N);
		//�ж�
		while (L--)
		{
			i = N;
			//����N����
			flag = 1;  //�ȼ�����ͬһ�ö�����
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
						flag = 0;  //��ǰ�ڵ㲢δ�����ʣ����ʾ����ͬһ�ö�����
						break;
					}
				}
				
			}

			//�ж�
			if (flag)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}

			//��AVL tree��flag������Ϊ0��
			Flag2Zeor(t);
		}
	}
	return 0;
}
