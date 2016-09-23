#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode
{
	int data;
	TreeNode *left;
	TreeNode *right;
};

typedef struct StackNode StackNode;
struct StackNode 
{
	TreeNode *data;
	StackNode *next;
};
typedef struct Stack Stack;
struct Stack
{
	StackNode *top;
};

typedef struct QueueNode QueueNode;
struct QueueNode
{
	TreeNode *data;
	QueueNode *next;
};
typedef struct Queue Queue;
struct Queue
{
	
	QueueNode *pre;
	QueueNode *rear;
};

//Stack
Stack *CreateStack(void);
void Push(TreeNode *t, Stack *s);
TreeNode *Pop(Stack *s);
int StackIsEmpty(Stack *s);
void InOrderTraversal(TreeNode *t);
void PostOrderTraversal(TreeNode *t);
void PreOrderTraversal(TreeNode *t);

//Queue
Queue *CreateQueue(void);
void EnQueue(TreeNode *t, Queue *q);
TreeNode *DeQueue(Queue *q);
int QueueIsEmpty(Queue *q);
void LevelOrderTraversal(TreeNode *t);

int main(void)
{
	
	return 0;
}

Stack *CreateStack(void)
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->top = NULL;

	return s;
}

void Push(TreeNode *t, Stack *s)
{
	StackNode *node = (StackNode*)malloc(sizeof(StackNode));
	node->data = (TreeNode*)malloc(sizeof(TreeNode));
	node->data->data = t->data;
	node->data->left = t->left;
	node->data->right = t->right;
	node->next = s->top;
	s->top = node;
}
TreeNode *Pop(Stack *s)
{
	TreeNode *t = NULL;
	StackNode *temp = NULL;

	t = s->top->data;
	temp = s->top;
	s->top = s->top->next;
	free(temp);

	return t;

}
int StackIsEmpty(Stack *s)
{
	if (s->top)
	{
		return 0;
	}

	return 1;
}

void InOrderTraversal(TreeNode *t, Stack *s)
{



	while (0 == StackIsEmpty(s) || t != NULL)
	{
		while (t)
		{
			Push(t, s);
			t = t->left;
		}
		if (0 == StackIsEmpty(s))
		{
			t = Pop(s);
			printf("%d", t->data);
			t = t->right;
		}
	}
}

void PreOrderTraversal(TreeNode *t)
{
	Stack *s = Create();


	while (0 == StackIsEmpty(s) || t != NULL)
	{
		while (t)
		{
			Push(t, s);
			printf("%d", t->data);
			t = t->left;
		}
		if (0 == StackIsEmpty(s))
		{
			t = Pop(s);
			
			t = t->right;
		}
	}
}

void PostOrderTraversal(TreeNode *t)  
{
	Stack *s1 = Create();
	Stack *s2 = Create();

	while (t || !StackIsEmpty(s1))
	{
		while (t)
		{
			Push(t, s1);
			Push(t, s2);
			t = t->right;
		}

		if (!StackIsEmpty(s1))
		{
			t = Pop(s1);
			t = t->left;
		}
	}

	//s2中得到了前序遍历的顺序，因此将它逆序输出就是后序遍历的顺序
	while (!StackIsEmpty(s2))
	{
		t = Pop(s2);
		printf("%d", t->data);
	}
	
}

Queue *CreateQueue(void)
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->pre = q->rear = NULL;

	return q;
}

void EnQueue(TreeNode *t, Queue *q)
{
	QueueNode *qn = (QueueNode*)malloc(sizeof(QueueNode));
	TreeNode *sn = (TreeNode*)malloc(sizeof(TreeNode));
	sn->data = t->data;
	sn->left = t->left;
	sn->right = t->right;

	qn->data = sn;
	qn->next = NULL;

	if (QueueIsEmpty(q))
	{
		q->pre = qn;
		q->rear = qn;
	}
	else
	{
		q->rear->next = qn;
		q->rear = qn;
	}
}

TreeNode *DeQueue(Queue *q)
{
	TreeNode *node = q->pre->data;
	q->pre = q->pre->next;

	if (q->pre == NULL)
	{
		q->rear = q->pre;
	}
	
}
int QueueIsEmpty(Queue *q)
{
	return q->pre == NULL;
}

void LevelOrderTraversal(TreeNode *t)
{
	Queue *q = CreateQueue();

	EnQueue(t, q);

	while (!IsEmpty(q))
	{
		t = DeQueue(q);

		printf("%d", t->data);
		if (t->left)
		{
			
			EnQueue(t->left,q);
		}
		if (t->right)
		{
			EnQueue(t->right, q);
		}
	}
}
