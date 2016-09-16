#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
typedef Node List; //双向链表
struct Node {
	int info[3];
	Node *next;
	Node *pre;
};

List *create(void); //创建包含头结点的空链表
void read(List *L);
/*

注意：设置了几个不在链表中的节点
在sort函数中对原list进行排序，并将不相干的节点去掉，并且重新计算节点数

*/
List *sort(List *L); //先将list排序
void myFree(List *L); //释放list
List *reverse(List *L);
void print(List *L);

int main(void)
{
	List *L = NULL;
	List *newList = NULL;
	List *reverseList = NULL;

	L = create();
	read(L);
	newList = sort(L);
	myFree(L);
	reverseList = reverse(newList);
	print(reverseList);
	return 0;
}

List *create(void) //创建包含头结点的空链表
{
	Node *head = NULL;

	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->pre = NULL;

	return head;
}

void read(List *L)
{
	int firstAddr, n, rev;
	Node *temp = NULL;
	Node *rear = NULL;
	rear = L;
	
	scanf("%d%d%d", &firstAddr, &n, &rev);
	L->info[0] = firstAddr;
	L->info[1] = n;
	L->info[2] = rev;

	while (n--)
	{
		temp = (Node*)malloc(sizeof(Node));

		scanf("%d%d%d", &temp->info[0], &temp->info[1], &temp->info[2]);
		temp->pre = rear;
		temp->next = NULL;

		rear->next = temp;
		rear = temp;
	}

}

List *reverse(List *L)
{
	int K, num, tempK;
	Node *head = NULL;
	Node *rear = NULL;
	Node *newHead = NULL;
	Node *newRear = NULL;
	Node *temp = NULL;

	head = newHead= newRear = L;
	head = head->next;  //head指向头结点
	tempK = K = L->info[2];

	num = L->info[1] / L->info[2]; //reverse的次数
	while (num--)
	{
		while (--tempK)
		{
			head = head->next;
		}
		rear = head;
		head = head->next;

		newRear->pre = rear;
		tempK = K;
		while (tempK--)
		{
			//temp = newRear->next;
			newRear->next = newRear->pre;  //翻转后将pre和next调换
			newRear = newRear->next;
		}
	}
	newRear->next = head;

	//对addr和next进行排序
	rear = newHead->next;
	while (rear->next)
	{
		
		rear->info[2] = rear->next->info[0];
		rear = rear->next;
		
	}
	rear->info[2] = -1;

	return newHead;
}

List *sort(List *L) //先将list排序，在sort函数中对原list进行排序，并将不相干的节点去掉，并且重新计算节点数
{
	int count, addr, realK;  //realK为重新计算节点数的值
	Node *head = NULL;
	Node *temp = NULL;
	Node *find = NULL;
	Node *rear = NULL;
	head = (Node*)malloc(sizeof(Node));
	head->info[0] = L->info[0];
	head->info[1] = L->info[1];
	head->info[2] = L->info[2];
	head->next = NULL;
	head->pre = NULL;
	rear = head;
	
	realK = 0;
	addr = L->info[0];
	count = L->info[1];
	find = L->next;
	while (count-- && addr!=-1)  //将不相干的节点去掉
	{
		while (find->info[0] != addr && find)
		{
			find = find->next;
		}
		if (find)
		{
			addr = find->info[2];
			temp = (Node*)malloc(sizeof(Node));
			temp->info[0] = find->info[0];
			temp->info[1] = find->info[1];
			temp->info[2] = find->info[2];
			temp->pre = rear;
			temp->next = NULL;

			find = L->next;

			rear->next = temp;
			rear = temp;

			realK++;
		}
		

	}

	//realK为重新计算节点数的值
	head->info[1] = realK;

	
	return head;
}
void myFree(List *L) //释放list
{
	Node *cur = NULL;
	Node *temp = NULL;
	cur = L;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		free(temp);
	}

}
void print(List *L)
{
	Node *cur = L->next;
	while (cur->next)
	{
		printf("%05d %d %05d\n", cur->info[0], cur->info[1], cur->info[2]);
		cur = cur->next;
	}
	printf("%05d %d %d", cur->info[0], cur->info[1], cur->info[2]);
}