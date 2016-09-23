#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode
{
	int left;
	int right;
};

typedef struct QueueNode QueueNode;
struct QueueNode
{
	int data;
	int left;
	int right;
	QueueNode *next;
};
typedef struct Queue Queue;
struct Queue
{
	QueueNode *pre;
	QueueNode *rear;
};

void EnQueue(int root, TreeNode *t, Queue *q);
Queue *CreateQueue(void);
QueueNode *DeQueue(Queue *q);
int QueueIsEmpty(Queue *q);

int main(void)
{
	int num, i, root;
	int *check = NULL;
	char left, right;
	TreeNode *t = NULL;
	Queue *q = NULL;
	QueueNode *qn = NULL;

	root = -1;

	//读入数据
	scanf("%d\n", &num);
	if (num)
	{
		t = (TreeNode*)malloc(sizeof(TreeNode)*num);
		
		//check数组用于匹配根节点
		check = (int*)malloc(sizeof(int)*num);
		for (i = 0; i < num; i++)
		{
			check[i] = 0;
		}

		for (i = 0; i < num; i++)
		{
			scanf("%c %c\n", &left, &right);
			if (left != '-')
			{
				t[i].left = left - '0';
				check[t[i].left] = 1;
			}
			else
			{
				t[i].left = -1;
			}

			if (right != '-')
			{
				t[i].right = right - '0';
				check[t[i].right] = 1;
			}
			else
			{
				t[i].right = -1;
			}
		}

		//找到根节点
		for (i = 0; i < num; i++)
		{
			if (check[i] == 0)
			{
				root = i;
				break;
			}
		}

		//创建队列
		q = CreateQueue();
		EnQueue(root, t, q);
		while (0 == QueueIsEmpty(q))
		{
			qn = DeQueue(q);
			/*
			if (QueueIsEmpty(q)==0)
			{
				if (qn->left == -1 && qn->right == -1)
				{
					printf("%d ", qn->data);
				}
				if (qn->left != -1)
				{
					EnQueue(qn->left, t, q);
				}
				if (qn->right != -1)
				{
					EnQueue(qn->right, t, q);
				}
				
			}
			else
			{
				printf("%d", qn->data);
			}
			*/

			if (qn->left != -1)
			{
				EnQueue(qn->left, t, q);
			}
			if (qn->right != -1)
			{
				EnQueue(qn->right, t, q);
			}
			if (qn->left == -1 && qn->right == -1)
			{
				if (QueueIsEmpty(q))
				{
					printf("%d", qn->data);
				}
				else
				{
					printf("%d ", qn->data);
				}
			}
		}
		
			


	}
	

	return 0;
}

Queue *CreateQueue(void)
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->pre = q->rear = NULL;

	return q;
}

void EnQueue(int root, TreeNode *t, Queue *q)
{
	if (q->pre == NULL)
	{
		q->pre = (QueueNode*)malloc(sizeof(QueueNode));
		q->pre->data = root;
		q->pre->left = t[root].left;
		q->pre->right = t[root].right;
		q->pre->next = NULL;

		q->rear = q->pre;
	}
	else
	{
		q->rear->next = (QueueNode*)malloc(sizeof(QueueNode));
		q->rear->next->data = root;
		q->rear->next->left = t[root].left;
		q->rear->next->right = t[root].right;
		q->rear->next->next = NULL;

		q->rear = q->rear->next;
	}
}
QueueNode *DeQueue(Queue *q)
{
	QueueNode *temp = NULL;
	if (q->pre == q->rear)
	{
		temp = q->pre;
		q->pre = q->rear = NULL;
	}
	else
	{
		temp = q->pre;
		q->pre = temp->next;
	}
	return temp;
}
int QueueIsEmpty(Queue *q)
{
	if (q->pre == NULL)
	{
		return 1;
	}

	return 0;
}