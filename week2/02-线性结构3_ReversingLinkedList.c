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
	int firstAddr, num, k, temp, i;  //firstAddr����һ���ڵ��λ�ã�num���ڵ�ĸ�����k��Ҫ��ת�Ľڵ�������temp��ʱ�洢����
	int data[MAX_NODE], next[MAX_NODE];  //data����Ϊ���ݣ�����Ϊ��ǰ��ַ��next����Ϊ��һ�����ݵ�λ�ã�����Ϊ��ǰ�ĵ�ַ			
	Node *head = NULL;
	Node *reverseList = NULL;  //��ת�������
	
	scanf("%d %d %d", &firstAddr, &num, &k); //����num�������input�Ľڵ�������������Ч�Ľڵ�
	List *list = (Node*)malloc(sizeof(Node)*(num + 1));//�½�һ����������
	list[0].next = firstAddr;  //list��ͷ����е�next�洢��һ�����ݽڵ��λ��
	//��������
	while (num--)
	{
		scanf("%d", &temp);  //temp�д洢���ǵ�ǰ�ڵ��λ��
		scanf("%d", &data[temp]);  //data�д洢���ǵ�ǰλ�õ�����
		scanf("%d", &next[temp]);  //next�д洢���ǵ�ǰ�ڵ����һ���ڵ��λ��
	}
	
	//���������list	
	i = 1; //ʹ����ָ������ĵ�һ���ڵ�
	while (1)
	{
		if (list[i - 1].next == -1) //ͨ���ж���һ�ڵ��next�ж��Ƿ�û�нڵ���
		{
			list[i - 1].nextAddr = NULL; //��Ϊ��һ�ڵ��nextΪ-1������û����һ���ڵ���
			num = i-1; //num�д洢������ʵ��Ч�Ľڵ���
			break; //Ϊ���һ���ڵ������ѭ��
		}
		list[i].addr = list[i - 1].next;  //��ǰ�ڵ�ĵ�ַ��ͨ����һ�ڵ��next��ֵ
		list[i].data = data[list[i].addr]; //��ǰ�ڵ�����ݣ�ͨ��data���飬�õ�ǰ�ڵ�ĵ�ַ��Ϊ����
		list[i].next = next[list[i].addr];//��һ���ڵ�ĵ�ַ��ͨ��next���飬�õ�ǰ�ڵ�ĵ�ַ��Ϊ����
		list[i-1].nextAddr = list + i;  //��һ���ڵ��д洢�ĵ�ǰ�ڵ����ʵ���ڴ��ַ
		
		i++;
	}
	
	//��ת����
	if (k <= num)
	{
		head = list; //headָ������ͷ���
		for (i = 0; i < num / k; i++)   //i�������Ǽ���Ҫ��ת�Ĵ��� 
		{
			head = reverse(head, k);  //head���������һ��Ҫ��ת�����ͷ���
		}
	}
	

	//��ӡ����
	print(list);
	return 0;
}


List *reverse(List *head, int k)
{
	int count = 1;
	Node *pre = NULL;
	Node *next = NULL;
	Node *temp = NULL;
	pre = head->nextAddr; //headָ��Ҫ��ת���Ƕ������ͷ��㣨��һ���ڵ��ǰһ���ڵ㣩
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

	head->nextAddr->nextAddr = next; //ͷ������һ���ڵ㷭ת��Ϊ���һ���ڵ㣬ʹ��ָ����һ������ĵ�һ���ڵ�
	if (next)  //���next��Ϊnull
	{
		head->nextAddr->next = next->addr;
	}
	else  //nextΪnullʱ����ʾ��pre������������һ���ڵ�
	{
		head->nextAddr->next = -1;
	}

	temp = head->nextAddr;  //temp���������һ��Ҫ��ת�������ͷ���
	//�ı�ͷ�ڵ������
	head->nextAddr = pre;
	head->next = pre->addr;
	return temp; //���ط�ת��ĵ�һ���ڵ㣬��ͷ���
}

void print(List *list)
{
	List *p = NULL;
	p = list->nextAddr; //ָ���һ���ڵ�
	while (p)
	{
		if (p->nextAddr)  //��������������һ���ڵ㲻Ϊnull
		{
			printf("%.5d %d %.5d\n", p->addr, p->data, p->next);
		}
		else  //��һ���ڵ�Ϊnull
		{
			printf("%.5d %d %d", p->addr, p->data, p->next);
		}
		p = p->nextAddr;
	}
}