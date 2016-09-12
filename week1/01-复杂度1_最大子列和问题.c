#include <stdio.h>
#include <stdlib.h>
int MaxSubsequenceSum1(const int *a, int n);
int MaxSubsequenceSum2(const int *a, int n);
int MaxSubsequenceSum3(const int *a, int n);
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
	MaxSum = MaxSubsequenceSum4(a, n);
	
	printf("%d", MaxSum);
		
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

int MaxSubsequenceSum3(const int *a, int n)
{
	
}

int MaxSubsequenceSum4(const int *a, int n) //T(N) =O(N)
{
	int i;
	int ThisSum, MaxSum;
	
	MaxSum = ThisSum = 0;
	for(i=0; i<n; i++)
	{
		ThisSum += a[i];
		if(ThisSum > MaxSum)
		{
			MaxSum = ThisSum;
		}
		else if(ThisSum < 0)
		{
			ThisSum = 0;
		}
	}
	
	return MaxSum;
}


