#include <stdio.h>
#include <stdlib.h>
int MaxSubsequenceSum1(const int *a, int n);
int MaxSubsequenceSum2(const int *a, int n);
int MaxSubsequenceSum3(const int *a, int Left, int Right);
int MaxSubsequenceSum4(const int *a, int n);
int main(void)
{
	int i, n, MaxSum;
	int *a=NULL;
	
	//read datas
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int)*n);
	for(i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	
	//MaxSum = MaxSubsequenceSum1(a, n);
	//MaxSum = MaxSubsequenceSum2(a, n);
	//MaxSum = MaxSubsequenceSum3(a, 0, n-1);
	MaxSum = MaxSubsequenceSum4(a, n);
	
	
	//printf("%d", MaxSum);
		
}

int MaxSubsequenceSum1(const int *a, int n)  //T(N) = O(N^3)
{
	int i, j, k;
	int ThisSum;
	int MaxSum = 0;
	
	for(i=0; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			ThisSum = 0;
			for(k=i; k<=j; k++)
			{
				ThisSum += a[k];	
			}
			if(ThisSum > MaxSum)
			{
				MaxSum = ThisSum;
			}	
		}	
	}	
	
	return MaxSum;
} 

int MaxSubsequenceSum2(const int *a, int n)  //T(N) = O(N^2)
{
	int i, j, k;
	int ThisSum;
	int MaxSum = 0;
	
	for(i=0; i<n; i++)
	{
		ThisSum = 0;
		for(j=i; j<n; j++)
		{
			ThisSum += a[j];
			if(ThisSum>MaxSum)
			{
				MaxSum = ThisSum;
			}
		}	
		
	}	
	
	return MaxSum;
}

int MaxSubsequenceSum3(const int *a, int Left, int Right)  //T(N) = O(log N) 
{
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;
	
	if(Left==Right)
	{
		if(a[Left]>0)
		{
			return a[Left];
		}
		else
		{
			return 0;
		}
	}
	
	Center = (Left+Right) / 2;
	MaxLeftSum = MaxSubsequenceSum3(a, Left, Center);
	MaxRightSum = MaxSubsequenceSum3(a, Center+1, Right);
	
	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;
	for(i=Center; i>=Left; i--)
	{
		LeftBorderSum += a[i];
		if(LeftBorderSum>MaxLeftBorderSum)
		{
			MaxLeftBorderSum = LeftBorderSum;
		}
	}
	
	MaxRightBorderSum = 0;
	RightBorderSum = 0;
	for(i=Center+1; i<=Right; i++)
	{
		RightBorderSum += a[i];
		if(RightBorderSum>MaxRightBorderSum)
		{
			MaxRightBorderSum = RightBorderSum;
		}
	}
	
	return (i=(MaxLeftSum>MaxRightSum?MaxLeftSum:MaxRightSum)) > (MaxLeftBorderSum+MaxRightBorderSum) ? i:(MaxLeftBorderSum+MaxRightBorderSum);
}

int MaxSubsequenceSum4(const int *a, int n) //T(N) =O(N)
{
	int i;
	int ThisSum, MaxSum;
	int Left, Right;
	int MaxLeft, MaxRight;
	
	MaxSum = -1;  //����ĿҪ�󣬵ó�MaxSumҪ��Ϊ-1���ܼ���������ж� 
	ThisSum = 0;
	Left = Right = 0;
	MaxLeft = MaxRight = a[0];
	for(i=0; i<n; i++)
	{
		ThisSum += a[i];
		Right = i;
		if(ThisSum > MaxSum)
		{
			MaxSum = ThisSum;
			MaxRight = a[i];
			if(Left!=MaxLeft)
			{
				MaxLeft = a[Left];
			}
		}
		else if(ThisSum < 0)
		{
			ThisSum = 0;
			Left = i+1;
		}
	}
	if(MaxSum<0)   
	{
		MaxSum = 0; 
		printf("%d %d %d\n", MaxSum, a[0], a[n-1]);
	}
	else
	{
		printf("%d %d %d\n", MaxSum, MaxLeft, MaxRight);	
	}
	
	return MaxSum;
}


