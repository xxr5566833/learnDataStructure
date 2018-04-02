// mocc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//两个栈实现插入排序
//33 - 47 14min
void insertionSort(int R[], int topR)
{
	int S[100];
	int topS = 0;
	while(topR)
	{
		int v = R[--topR];
		//这里条件错误了 原来是||
		while(topS && v < S[topS - 1])
		{
			R[topR++] = S[--topS];
		}
		S[topS++] = v;
	}
	for(int i = 0 ; i < topS ; i++)
	{
		std::cout << S[i] << std::endl;
	}
}

//14.21 - 34  13min
//直方图中最大面积矩形确定

int maximalRect(int height[], int n)
{
	if(n <= 0)	return 0;
	int *stack = new int[n + 2];
	int top = 0;
	int k = 1;
	stack[top++] = 0;
	int result = 0;
	//这里加这个是因为OJ上要求的输入是第0和第n+1是0，那么如果第一项是0时，栈会越界，所以这里设置它们俩为-1
	height[0] = -1;
	height[n + 1] = -1;
	while(top != 1 || k != n + 1)
	{
		int v = height[k];
		//这里一开始忘了加a[]，应该是值之间的比较，但是加入栈的是下标，这个要注意
		if(height[stack[top - 1]] < v)
		{
			stack[top++] = k;
			k++;
		}
		else{
			int h = height[stack[--top]];
			int square = h * (k - stack[top - 1] - 1 );
			result = result > square ? result : square;
		}
	}
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {0, 0, 0};
	int size = 1;
	std::cout << maximalRect(a, size) << std::endl;
	return 0;
}

