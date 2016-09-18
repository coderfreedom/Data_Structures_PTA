#include <stdio.h>
#include <stdlib.h>

/*
方法1 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int a;  //系数 
	int b;  //指数 
	struct Node *next;
}Node;
typedef struct Node List;

List *create(void);  //含有头结点 
void read(List *L);
List *sum(List *L1, List *L2);
List *multi(List *L1, List *L2);
List *m(Node *cur, List *L);
void myFree(List *L);  //释放多余的链表 
void print(List *L);

int main(void)
{
	List *L1 = NULL;
	List *L2 = NULL;
	List *multiList = NULL;
	List *sumList = NULL;

	L1 = create();
	L2 = create();
	read(L1);
	read(L2);
	multiList = multi(L1, L2);
	sumList = sum(L1, L2);
	print(multiList);
	printf("\n");
	print(sumList);
	return 0;
}

List *create(void)
{
	Node *head = NULL;

	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;

	return head;
}

void read(List *L)
{
	int n, a, b;
	Node *rear = NULL;
	Node *temp = NULL;
	rear = L;

	scanf("%d", &n);
	L->a = n;
	L->b = L->a;


	while (n)
	{


		scanf("%d%d", &a, &b);
		temp = (Node*)malloc(sizeof(Node));
		temp->a = a;
		temp->b = b;
		rear->next = temp;
		rear = temp;
		temp->next = NULL;




		n--;
	}

}

List *sum(List *L1, List *L2)
{
	int num;
	Node *head = (Node*)malloc(sizeof(Node));
	Node *rear = NULL;
	Node *temp = NULL;
	head->next = NULL;
	rear = head;

	L1 = L1->next;
	L2 = L2->next;
	while (L1 && L2)
	{
		if (L1->b == L2->b)
		{
			num = L1->a + L2->a;

			if (num)
			{
				temp = (Node*)malloc(sizeof(Node));
				temp->a = num;
				temp->b = L1->b;
				temp->next = NULL;

				rear->next = temp;
				rear = temp;
			}
			L1 = L1->next;
			L2 = L2->next;
		}
		else if (L1->b > L2->b)
		{
			if (L1->a) //改了这里加了一个判断a不为0
			{
				temp = (Node*)malloc(sizeof(Node));
				temp->a = L1->a;
				temp->b = L1->b;
				temp->next = NULL;

				rear->next = temp;
				rear = temp;
			}


			L1 = L1->next;
		}
		else
		{
			if (L2->a)//改了这里加了一个判断a不为0
			{
				temp = (Node*)malloc(sizeof(Node));
				temp->a = L2->a;
				temp->b = L2->b;
				temp->next = NULL;

				rear->next = temp;
				rear = temp;
			}


			L2 = L2->next;
		}
	}

	while (L1)  //这里改了，原来是if，后来发现错了。。。应该是while
	{
		if (L1->a)//改了这里加了一个判断a不为0
		{
			temp = (Node*)malloc(sizeof(Node));
			temp->a = L1->a;
			temp->b = L1->b;
			temp->next = NULL;

			rear->next = temp;
			rear = temp;
		}


		L1 = L1->next;
	}
	while (L2)  //这里改了，原来是if，后来发现错了。。。应该是while
	{
		if (L2->a)//改了这里加了一个判断a不为0
		{
			temp = (Node*)malloc(sizeof(Node));
			temp->a = L2->a;
			temp->b = L2->b;
			temp->next = NULL;

			rear->next = temp;
			rear = temp;
		}


		L2 = L2->next;
	}

	return head;
}

List *multi(List *L1, List *L2)
{
	Node *head = NULL;
	Node *temp1 = NULL;
	Node *temp2 = NULL;

	//先建立一个list
	//用L1的第一个节点与L2的每一个节点相乘（非头结点） 
	L1 = L1->next;
	head = m(L1, L2);
	if (L1 && L2->next)
	{
		

		while (L1 = L1->next)
		{
			temp1 = head;
			temp2 = m(L1, L2);
			head = sum(temp1, temp2);
			myFree(temp1);
			myFree(temp2);

		}
	}
	

	return head;
}
List *m(Node *cur, List *L)
{
	int b;
	Node *temp = NULL;
	Node *rear = NULL;
	List *head = create();
	rear = head;

	if (cur)
	{
		while (L = L->next)
		{
			/*
			b = cur->b + L->b;
			temp = (Node*)malloc(sizeof(Node));

			temp->a = cur->a * L->a;
			temp->b = b;
			temp->next = NULL;

			rear->next = temp;
			rear = temp;
			*/

			if (L->a && cur->a)  //改动，加了一个判断，只有a都不为0才会进入
			{
				b = cur->b + L->b;
				temp = (Node*)malloc(sizeof(Node));

				temp->a = cur->a * L->a;
				temp->b = b;
				temp->next = NULL;

				rear->next = temp;
				rear = temp;
			}

		}
	}
	

	return head;
}
void myFree(List *L)
{
	Node *temp = NULL;
	while (L)
	{
		temp = L;
		L = L->next;
		free(temp);
	}

}

void print(List *L)
{
	L = L->next;
	if (L)
	{
		while (L)
		{

			if (L->next)   //控制输出格式 
			{
				printf("%d %d ", L->a, L->b);
			}
			else
			{
				printf("%d %d", L->a, L->b);
			}


			L = L->next;
		}

	}
	else
	{
		printf("0 0");
	}

}

/*
方法2 
*/ 
/* 
typedef struct node{
	int coefficient;
	int exponent;
	struct node * next;
} PolyNode, *Polynomial;

Polynomial ReadPoly();
void Attach(int c, int e, Polynomial * Rear);
Polynomial MultPoly(Polynomial P1, Polynomial P2);
Polynomial AddPoly(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);

int main(int argc, char const *argv[])
{
	Polynomial Poly1, Poly2, PolySum, PolyMul;

	Poly1 = ReadPoly();
	Poly2 = ReadPoly();
	PolyMul = MultPoly(Poly1, Poly2);
	PrintPoly(PolyMul);
	PolySum = AddPoly(Poly1, Poly2);
	PrintPoly(PolySum);

	return 0;
}

Polynomial ReadPoly()
{
	Polynomial P, Rear, temp;
	P = (PolyNode*)malloc(sizeof(PolyNode));
	P->next = NULL;
	Rear = P;
	int N, c, e;
	scanf("%d", &N);
	while(N--){
		scanf("%d %d", &c, &e);
		Attach(c, e, &Rear);
	}
	temp = P;
	P = P->next; 
	free(temp);
	return P;
}

void Attach(int c, int e, Polynomial * pRear)
{
	Polynomial P;
	P = (PolyNode*)malloc(sizeof(PolyNode));
	P->coefficient = c;
	P->exponent = e;
	P->next = NULL;
	(*pRear)->next = P;
	*pRear = P;
}

Polynomial MultPoly(Polynomial P1, Polynomial P2)
{
	Polynomial P, temp1, temp2, Rear, temp;
	int c, e;
	if(!P1 || !P2)
		return NULL;
	temp1 = P1;
	temp2 = P2;
	P = (PolyNode*)malloc(sizeof(PolyNode));
	P->next = NULL;
	Rear = P;
	while(temp2){
		c = temp1->coefficient * temp2->coefficient;
		e = temp1->exponent + temp2->exponent;
		if(c != 0){
			Attach(c, e, &Rear);
			temp2 = temp2->next;
		}
	}
	temp1 = temp1->next;
	while(temp1){
		temp2 = P2, Rear = P;
		while(temp2){
			c = temp1->coefficient * temp2->coefficient;
			e = temp1->exponent + temp2->exponent;
			if(c != 0){
				while(Rear->next && Rear->next->exponent > e)
					Rear = Rear->next;
				if(Rear->next && Rear->next->exponent == e){
					if(Rear->next->coefficient + c)
						Rear->next->coefficient += c;
					else{
						temp = Rear->next;
						Rear->next = temp->next;
						free(temp);
					}
				}
				else{
					temp = (PolyNode*)malloc(sizeof(PolyNode));
					temp->coefficient = c;
					temp->exponent = e;
					temp->next = Rear->next;
					Rear->next = temp;
					Rear = Rear->next;
				}
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
	}
	temp = P;
	P = P->next;
	free(temp);
	return P;
}

Polynomial AddPoly(Polynomial P1, Polynomial P2)
{
	Polynomial P, temp1, temp2, Rear, temp;
	if(!P1 && !P2){
		if(!P1)
			return P2;
		else
			return P1;
	}
	P = (PolyNode*)malloc(sizeof(PolyNode));
	P->next = NULL;
	Rear = P;
	temp1 = P1;
	temp2 = P2;
	while(temp1 && temp2){
		if(temp1->exponent > temp2->exponent){
			if(temp1->coefficient){
				Attach(temp1->coefficient, temp1->exponent, &Rear);				
			}
			temp1 = temp1->next;
		}
		else if(temp1->exponent == temp2->exponent){
			if(temp1->coefficient + temp2->coefficient){
				Attach(temp1->coefficient + temp2->coefficient, temp1->exponent, &Rear);
			}
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else{
			if(temp2->coefficient){
				Attach(temp2->coefficient, temp2->exponent, &Rear);				
			}
			temp2 = temp2->next;
		}
	}
	while(temp1){
		Attach(temp1->coefficient, temp1->exponent, &Rear);
		temp1 = temp1->next;
	}
	while(temp2){
		Attach(temp2->coefficient, temp2->exponent, &Rear);
		temp2 = temp2->next;
	}
	temp = P;
	P = P->next;
	free(temp);
	return P;
}

void PrintPoly(Polynomial P)
{
	int flag = 0;
	if(!P){
		printf("0 0");
	}
	while(P){
		if (!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d", P->coefficient, P->exponent);
		P = P->next;
	}
	printf("\n");
}
*/
