#include <stdio.h> 
#include <stdlib.h>


typedef int ElementType; 
typedef struct Node *PtrNode;
struct Node {
	ElementType Data;  //�洢�ڵ����� 
	PtrNode Next;		//ָ����һ���ڵ��ָ�� 
};
typedef PtrNode List;  //���嵥�������� 

List Read(); /* ϸ���ڴ˲��� */
void Print( List L ); /* ϸ���ڴ˲������������NULL */
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
	int n; //�ڵ����ݸ�����������ͷ��㣩 
	PtrNode head = NULL;
	PtrNode rear = NULL; //ָ�����һ���ڵ� 
	PtrNode temp = NULL;
	
	//��ʼ����������ͷ��㣬ͷ�����Data�洢���ݽڵ�ĸ�����������ͷ��㣩 
	head = (PtrNode)malloc(sizeof(struct Node));
	rear = head; //��ʼ��ʱrear��headͬʱָ��ͷ��� 
	scanf("%d", &n); //�ڵ����ݸ��� 
	head->Data = n; //ͷ���洢�ڵ���� 
	head->Next = NULL;
	  
	 //����ڵ�����
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
			if(L->Next) //���ж������������ʽ 
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
	
	//L��rear��ʼͬʱָ��L1��ͷ��� 
	L = (List)malloc(sizeof(struct Node)); 
	L->Next = NULL;
	rear = L;
	
	
	L1 = L1->Next; //��ͷ���ָ���һ���ڵ� 
	L2 = L2->Next; //��ͷ���ָ���һ���ڵ�
	
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










