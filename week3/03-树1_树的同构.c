#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode
{
	char data;
	int left;
	int right;
};




int BuildTree(TreeNode *t);
int Judge(int r1, int r2, TreeNode *t1, TreeNode *t2);

int main(void)
{
	TreeNode *t1 = (TreeNode*)malloc(sizeof(TreeNode)*10);
	TreeNode *t2 = (TreeNode*)malloc(sizeof(TreeNode) * 10);
	int root1, root2;
	
	root1 = BuildTree(t1);
	root2 = BuildTree(t2);


	
	if (Judge(root1, root2, t1, t2))
	{
		printf("Yes");
	}
	else
	{
		printf("No");
	}


	return 0;
}

int BuildTree(TreeNode *t)
{
	int num, i, root;
	int *check = NULL;
	char data, left, right;

	root = -1;

	scanf("%d\n", &num);
	if (num)
	{
		//t = (TreeNode*)malloc(sizeof(TreeNode)*num);

		check = (int*)malloc(sizeof(int)*num);
		for (i = 0; i < num; i++)
		{
			check[i] = 0;
		}

		for (i = 0; i < num; i++)
		{
			scanf("%c %c %c\n", &data, &left, &right);
			t[i].data = data;
			if (left != '-')
			{
				t[i].left = left - '0';
				check[t[i].left] = 1;
			}
			else
			{
				t[i].left = -1;
			}

			if (right != '-')
			{
				t[i].right = right - '0';
				check[t[i].right] = 1;
			}
			else
			{
				t[i].right = -1;
			}
		}

		for (i = 0; i < num; i++)
		{
			if (check[i] == 0)
			{
				root = i;
				break;
			}
		}
	}
	

	return root;
}

int Judge(int r1, int r2, TreeNode *t1, TreeNode *t2)
{
	if (r1 == -1 && r2 == -1)
	{
		return 1;
	}
	if (( r1!=-1 && r2==-1 ) || ( r1==-1 && r2!=-1 ))
	{
		return 0;
	}
	if (t1[r1].data != t2[r2].data)
	{
		return 0;
	}
	if ((t1[r1].left == -1) && (t2[r2].left == -1))
	{
		return Judge(t1[r1].right, t2[r2].right, t1, t2);
	}
	if (((t1[r1].left != -1) && (t2[r2].left != -1)) &&
		((t1[t1[r1].left].data) == (t2[t2[r2].left].data)))
	{
		return Judge(t1[r1].left, t2[r2].left, t1, t2) &&
			Judge(t1[r1].right, t2[r2].right, t1, t2);
	}
	else
	{
		return (Judge(t1[r1].left, t2[r2].right, t1, t2) &&
			Judge(t1[r1].right, t2[r2].left, t1, t2));
	}
}