#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h> 

//�ɶ�����������ʿ�֪������������Ľ��һ��Ϊ��С����
//��ȫ�����������ʿ�֪�������Ϊi�������ӽ��2*i, �Һ��ӽ��2*i+1���������д�ţ�
//�����������������ʣ����Խ������
/*
����ڵ�����ݣ��ٶ�����С�������򣬵õ���������Ľ��
�����Ѿ�������ȫ������������������ķ������ݹ�������������ڵ���±����Ϊ1�������±��Ϊ2*i���Һ����±�Ϊ2*i+1���±���Ϊ��������Ĵ���
*/

//�ⷨһ
void MySort(int *arr, int num);
void Solve(int *inOrder, int *pInIndex, int N, int *levelOrder, int levelIndex);
int main(void)
{
	int N, i, inIndex;
	int *inOrder;
	int *levelOrder;
	
	scanf("%d", &N);
	inOrder = (int*)malloc(sizeof(int)*N);
	levelOrder = (int*)malloc(sizeof(int)*(N + 1));
	inIndex = 0; //��ΪinOrder������

	//��������
	for (i = 0; i < N; i++)
	{
		scanf("%d", inOrder + i);
	}
	//��С�������򣬳�Ϊ�������
	MySort(inOrder, N);

	//�ݹ���������
	Solve(inOrder, &inIndex, N, levelOrder, 1);

	//��ӡ����
	printf("%d", levelOrder[1]);
	for (i = 2; i < N + 1; i++)
	{
		printf(" %d", levelOrder[i]);
	}

	return 0;
}

void MySort(int *arr, int num)
{
	int i, j, temp;
	for (i = 0; i < num; i++)
	{
		for (j = i + 1; j < num; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void Solve(int *inOrder, int *pInIndex, int N, int *levelOrder, int levelIndex)
{
	if (levelIndex > N)
	{
		return;
	}
	Solve(inOrder, pInIndex, N, levelOrder, levelIndex * 2);
	levelOrder[levelIndex] = inOrder[(*pInIndex)++];
	Solve(inOrder, pInIndex, N, levelOrder, levelIndex * 2+1);
}

//�ⷨ��
/*
void MySort(int *arr, int num);
void Solve(int inLeft, int inRight, int *inOrder, int levelRoot, int *levelOrder);//inLeft�����������������±꣬inRight�����������������±꣬levelRoot���������������±�
int GetLeftLength(int num); //numΪ�ڵ�����
int compare(const void * a, const void * b);

int main(void)
{
	
	int num, i;
	int *inOrder = NULL; //��������Ľڵ�����
	int *levelOrder = NULL; //��������Ľڵ�����

	scanf("%d", &num);
	inOrder = (int*)malloc(sizeof(int)*num);
	levelOrder = (int*)malloc(sizeof(int)*num);

	//�ɶ�����������ʿ�֪������������Ľ��һ��Ϊ��С����
	//����ڵ�����ݣ��ٶ�����С��������
	for (i = 0; i < num; i++)
	{
		scanf("%d", inOrder + i);
	}
	//MySort(inOrder, num);  //��С��������
	qsort(inOrder, num, sizeof(int), compare);
 
	//��ʼ�ݹ���������
	Solve(0, num - 1, inOrder, 0, levelOrder);
	
	//������
	if (num)
	{
		printf("%d", levelOrder[0]);
		for (i = 1; i < num; i++)
		{
			printf(" %d", levelOrder[i]);
		}
	}
	else
	{
		printf("0");
	}
	
	
	return 0;
}

void MySort(int *arr, int num)
{
	int i, j, temp;
	for (i = 0; i < num; i++)
	{
		for (j = i + 1; j < num; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void Solve(int inLeft, int inRight, int *inOrder, int levelRoot, int *levelOrder) //levelRootָ�������������±�
{
	int num, leftLength;  //numΪ��ǰҪ�������������Ľڵ�����leftLengthΪ�������ĳ���
	
	num = inRight - inLeft + 1;  //num����ǰ����ĳ���
	if (num == 0 ) //��ǰ����ĳ���
	{
		return;
	}
	leftLength = GetLeftLength(num); //��ȡ�������ĳ���
	levelOrder[levelRoot] = inOrder[inLeft + leftLength];

	//�ݹ�����������

	Solve(inLeft, inLeft + leftLength - 1, inOrder, levelRoot * 2 + 1, levelOrder);
	Solve(inLeft + leftLength+1, inRight, inOrder, levelRoot * 2 + 2, levelOrder);


}

int GetLeftLength(int num)
{
	int length, level;//lengthΪ�������ĳ��ȣ��������ڵ���������levelΪ����
	int tempLevel, tempNum, large;

	//�ó�����level
	for (level=0, tempNum = num; tempNum > 0; level++)
	{
		tempNum /= 2;
	}

	
	if (level != 1)
	{
		//�ó���ײ�Ľڵ���
		for (tempLevel = 1, tempNum=1; tempLevel < level; tempLevel++)
		{
			tempNum *= 2;
		}
		tempNum = num - (tempNum - 1); //tempNumΪ��ײ�Ľڵ���

		//��������ײ�Ľڵ���
		//�ȼ������������ײ����Ľڵ���
		for (tempLevel = 1, large=1; tempLevel < level-1; tempLevel++)
		{
			large *= 2;
		}
		//Ȼ�������������ײ�ڵ���
		large = large < tempNum ? large : tempNum;

		//��������������
		if (level != 2)
		{
			for (tempLevel = 1, length=1; tempLevel < level - 1; tempLevel++)
			{
				length *= 2;
			}
			length = length - 1 + large;
		}
		else
		{
			length = 1;
		}

	}
	else
	{
		length = 0;
	}

	return length;
}
int compare(const void * a, const void * b)
{
return *(int *)a - *(int *)b;
}
*/

//�ⷨ�����ýⷨ��ⷨһ���ƣ�
/*
int b[1005];
int j = 0;

int compare(const void * a, const void * b);
void mid_tre(int root, int N, int a[]);

int main() {
	int N;
	int i = 0;
	scanf("%d", &N);
	int a[N];
	for (i = 0; i<N; i++) {
		scanf("%d", &a[i]);
	}
	qsort(a, N, sizeof(int), compare);
	mid_tre(1, N, a);
	printf("%d", b[1]);
	for (i = 2; i <= N; i++) {
		printf(" %d", b[i]);
	}

	return 0;
}

int compare(const void * a, const void * b)
{
	return *(int *)a - *(int *)b;
}

void mid_tre(int root, int N, int a[]) {
	if (root <= N) {
		mid_tre(2 * root, N, a);
		b[root] = a[j++];
		mid_tre(2 * root + 1, N, a);
	}
}
*/