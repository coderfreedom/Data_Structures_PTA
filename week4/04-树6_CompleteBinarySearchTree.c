#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h> 

//由二叉查找树性质可知，其中序遍历的结果一定为由小到大
//完全二叉树的性质可知，根结点为i，其左孩子结点2*i, 右孩子结点2*i+1（在数组中存放）
//根据这两种树的性质，可以解出该题
/*
读入节点的数据，再对其由小到大排序，得到中序遍历的结果
假设已经存在完全二叉树，用中序遍历的方法，递归遍历树，而根节点的下标假设为1，左孩子下标就为2*i，右孩子下标为2*i+1，下标又为层序遍历的次序
*/

//解法一
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
	inIndex = 0; //作为inOrder的索引

	//读入数据
	for (i = 0; i < N; i++)
	{
		scanf("%d", inOrder + i);
	}
	//由小到大排序，成为中序遍历
	MySort(inOrder, N);

	//递归解决该问题
	Solve(inOrder, &inIndex, N, levelOrder, 1);

	//打印数据
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

//解法二
/*
void MySort(int *arr, int num);
void Solve(int inLeft, int inRight, int *inOrder, int levelRoot, int *levelOrder);//inLeft：中序遍历数组的左下标，inRight：中序遍历数组的右下标，levelRoot：层序遍历数组的下标
int GetLeftLength(int num); //num为节点数量
int compare(const void * a, const void * b);

int main(void)
{
	
	int num, i;
	int *inOrder = NULL; //中序遍历的节点数组
	int *levelOrder = NULL; //层序遍历的节点数组

	scanf("%d", &num);
	inOrder = (int*)malloc(sizeof(int)*num);
	levelOrder = (int*)malloc(sizeof(int)*num);

	//由二叉查找树性质可知，其中序遍历的结果一定为由小到大
	//读入节点的数据，再对其由小到大排序
	for (i = 0; i < num; i++)
	{
		scanf("%d", inOrder + i);
	}
	//MySort(inOrder, num);  //由小到大排序
	qsort(inOrder, num, sizeof(int), compare);
 
	//开始递归解决该问题
	Solve(0, num - 1, inOrder, 0, levelOrder);
	
	//输出结果
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

void Solve(int inLeft, int inRight, int *inOrder, int levelRoot, int *levelOrder) //levelRoot指层序遍历数组的下标
{
	int num, leftLength;  //num为当前要解决的中序遍历的节点数，leftLength为左子树的长度
	
	num = inRight - inLeft + 1;  //num：当前数组的长度
	if (num == 0 ) //当前数组的长度
	{
		return;
	}
	leftLength = GetLeftLength(num); //获取左子树的长度
	levelOrder[levelRoot] = inOrder[inLeft + leftLength];

	//递归解决左右子树

	Solve(inLeft, inLeft + leftLength - 1, inOrder, levelRoot * 2 + 1, levelOrder);
	Solve(inLeft + leftLength+1, inRight, inOrder, levelRoot * 2 + 2, levelOrder);


}

int GetLeftLength(int num)
{
	int length, level;//length为左子树的长度（左子树节点数量），level为层数
	int tempLevel, tempNum, large;

	//得出层数level
	for (level=0, tempNum = num; tempNum > 0; level++)
	{
		tempNum /= 2;
	}

	
	if (level != 1)
	{
		//得出最底层的节点数
		for (tempLevel = 1, tempNum=1; tempLevel < level; tempLevel++)
		{
			tempNum *= 2;
		}
		tempNum = num - (tempNum - 1); //tempNum为最底层的节点数

		//左子树最底层的节点数
		//先计算出左子树最底层最大的节点数
		for (tempLevel = 1, large=1; tempLevel < level-1; tempLevel++)
		{
			large *= 2;
		}
		//然后计算左子树最底层节点数
		large = large < tempNum ? large : tempNum;

		//计算左子树长度
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

//解法三（该解法与解法一类似）
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