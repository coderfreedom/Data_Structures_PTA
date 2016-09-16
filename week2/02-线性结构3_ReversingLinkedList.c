#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE 100001

typedef struct Node {
	int addr;
	int data;
	int next;
	struct Node *nextAddr;
}Node;
typedef struct Node List;

List *reverse(List *head, int k);
void print(List *list);
int main(void)
{
	int firstAddr, num, k, temp, i;  //firstAddr：第一个节点的位置，num：节点的个数，k：要翻转的节点数量，temp临时存储数据
	int data[MAX_NODE], next[MAX_NODE];  //data数组为数据，索引为当前地址，next数组为下一个数据的位置，索引为当前的地址			
	Node *head = NULL;
	Node *reverseList = NULL;  //翻转后的链表
	
	scanf("%d %d %d", &firstAddr, &num, &k); //现在num读入的是input的节点数，包含了无效的节点
	List *list = (Node*)malloc(sizeof(Node)*(num + 1));//新建一个数组链表
	list[0].next = firstAddr;  //list的头结点中的next存储第一个数据节点的位置
	//读入数据
	while (num--)
	{
		scanf("%d", &temp);  //temp中存储的是当前节点的位置
		scanf("%d", &data[temp]);  //data中存储的是当前位置的数据
		scanf("%d", &next[temp]);  //next中存储的是当前节点的下一个节点的位置
	}
	
	//建立有序的list	
	i = 1; //使索引指向链表的第一个节点
	while (1)
	{
		if (list[i - 1].next == -1) //通过判断上一节点的next判断是否没有节点了
		{
			list[i - 1].nextAddr = NULL; //因为上一节点的next为-1，所以没有下一个节点了
			num = i-1; //num中存储的是真实有效的节点数
			break; //为最后一个节点就跳出循环
		}
		list[i].addr = list[i - 1].next;  //当前节点的地址，通过上一节点的next赋值
		list[i].data = data[list[i].addr]; //当前节点的数据，通过data数组，用当前节点的地址作为索引
		list[i].next = next[list[i].addr];//下一个节点的地址，通过next数组，用当前节点的地址作为索引
		list[i-1].nextAddr = list + i;  //上一个节点中存储的当前节点的真实的内存地址
		
		i++;
	}
	
	//翻转链表
	if (k <= num)
	{
		head = list; //head指向链表头结点
		for (i = 0; i < num / k; i++)   //i在这里是计算要翻转的次数 
		{
			head = reverse(head, k);  //head储存的是下一段要翻转链表的头结点
		}
	}
	

	//打印链表
	print(list);
	return 0;
}


List *reverse(List *head, int k)
{
	int count = 1;
	Node *pre = NULL;
	Node *next = NULL;
	Node *temp = NULL;
	pre = head->nextAddr; //head指向要翻转的那段链表的头结点（第一个节点的前一个节点）
	next = pre->nextAddr;
	while (count < k)
	{
		temp = next->nextAddr;
		next->nextAddr = pre;
		next->next = pre->addr;

		pre = next;
		next = temp;

		count++;
	}

	head->nextAddr->nextAddr = next; //头结点的下一个节点翻转后为最后一个节点，使其指向下一段链表的第一个节点
	if (next)  //如果next不为null
	{
		head->nextAddr->next = next->addr;
	}
	else  //next为null时，表示是pre整个链表的最后一个节点
	{
		head->nextAddr->next = -1;
	}

	temp = head->nextAddr;  //temp储存的是下一段要翻转的链表的头结点
	//改变头节点的数据
	head->nextAddr = pre;
	head->next = pre->addr;
	return temp; //返回翻转后的第一个节点，非头结点
}

void print(List *list)
{
	List *p = NULL;
	p = list->nextAddr; //指向第一个节点
	while (p)
	{
		if (p->nextAddr)  //控制输出，如果下一个节点不为null
		{
			printf("%.5d %d %.5d\n", p->addr, p->data, p->next);
		}
		else  //下一个节点为null
		{
			printf("%.5d %d %d", p->addr, p->data, p->next);
		}
		p = p->nextAddr;
	}
}