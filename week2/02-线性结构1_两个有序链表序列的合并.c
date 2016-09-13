#include <stdio.h> 
#include <stdlib.h>


typedef int ElementType; 
typedef struct Node *PtrNode;
struct Node {
	ElementType Data;  //存储节点数据 
	PtrNode Next;		//指向下一个节点的指针 
};
typedef PtrNode List;  //定义单链表类型 

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */
List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
	int n; //节点数据个数（不包括头结点） 
	PtrNode head = NULL;
	PtrNode rear = NULL; //指向最后一个节点 
	PtrNode temp = NULL;
	
	//初始化空链表，有头结点，头结点中Data存储数据节点的个数（不包括头结点） 
	head = (PtrNode)malloc(sizeof(struct Node));
	rear = head; //初始化时rear和head同时指向头结点 
	scanf("%d", &n); //节点数据个数 
	head->Data = n; //头结点存储节点个数 
	head->Next = NULL;
	  
	 //读入节点数据
	while(n)
	{
		temp = (PtrNode)malloc(sizeof(struct Node));
		scanf("%d", &temp->Data);
		temp->Next = NULL;
		
		rear->Next = temp;
		rear = temp;
		
		n--; 	
	} 
	
	return head;
	 
}

void Print( List L )
{
	L = L->Next;
	if(L)
	{
		do
		{
			if(L->Next) //用判断来控制输出格式 
			{
				printf("%d ", L->Data);
			}
			else
			{
				printf("%d\n", L->Data);
			}
		}while(L=L->Next);
	}
	else
	{
		printf("NULL\n");
	}
}

List Merge( List L1, List L2 )
{
	List L = NULL;
	List rear = NULL;
	List temp1 = L1;
	List temp2 = L2;
	
	//L和rear开始同时指向L1的头结点 
	L = (List)malloc(sizeof(struct Node)); 
	L->Next = NULL;
	rear = L;
	
	
	L1 = L1->Next; //从头结点指向第一个节点 
	L2 = L2->Next; //从头结点指向第一个节点
	
	while(L1 && L2)
	{
		if(L1->Data < L2->Data)
		{
			rear->Next = L1;
			rear = L1;
			L1 = L1->Next;
		}
		else
		{
			rear->Next = L2;
			rear = L2;
			L2 = L2->Next;
		}
	}
	if(L1)
	{
		rear->Next = L1;
	}
	if(L2)
	{
		rear->Next = L2;
	}
	
	temp1->Next = NULL;
	temp2->Next = NULL;
	return L;
}










