// mocc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//����ջʵ�ֲ�������
//33 - 47 14min
void insertionSort(int R[], int topR)
{
	int S[100];
	int topS = 0;
	while(topR)
	{
		int v = R[--topR];
		//�������������� ԭ����||
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
//ֱ��ͼ������������ȷ��

int maximalRect(int height[], int n)
{
	if(n <= 0)	return 0;
	int *stack = new int[n + 2];
	int top = 0;
	int k = 1;
	stack[top++] = 0;
	int result = 0;
	//������������ΪOJ��Ҫ��������ǵ�0�͵�n+1��0����ô�����һ����0ʱ��ջ��Խ�磬������������������Ϊ-1
	height[0] = -1;
	height[n + 1] = -1;
	while(top != 1 || k != n + 1)
	{
		int v = height[k];
		//����һ��ʼ���˼�a[]��Ӧ����ֵ֮��ıȽϣ����Ǽ���ջ�����±꣬���Ҫע��
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

