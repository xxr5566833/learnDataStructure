#include "stdafx.h"
//20 - 
// n, m����������
// matrix��һ���ַ������飬������¼�������Σ�matrix[i][j]��ʾ�������ε�i�е�j�е��ַ����±����0��ʼ��
// ����ֵ����Ŀ����𰸣������������
int getAnswer(int n, int m, std::string *matrix) {
	if(n <= 0 || m <= 0)	return 0;
	int *stack = new int[m + 1];
	int top = 0;
	stack[top++] = -1;
	int result = 0;
	int *height = new int[m];
	for(int i = 0 ; i < m ; height[i] = 0, i++);
	for(int i = 0 ; i < n ; i++)
	{
		//1.����Ե�ǰ��Ϊ����е�ֱ��ͼ�ĸ߶�����
		for(int j = 0 ; j < m ; j++)
		{
			if(matrix[i][j] == '.')
				height[j] += 1;
			else	height[j] = 0;
		}
		//2.����֮ǰ���㷨��������ֱ��ͼ�����������
		int k = 0;
		while(top != 1 || k != m)
		{
			int v = k < m ? height[k] : -1;
			if((top == 1 ? -1 : height[stack[top - 1]]) < v)
			{
				stack[top++] = k;
				k++;
			}
			else{
				int square = height[stack[--top]] * (k - stack[top - 1] - 1);
				result = result > square ? result : square;
			}
		}
	}
	return result;
}

/*int main() {
    std::ios::sync_with_stdio(false);  // �����Ż�
    
    int n, m;
    std::cin >> n >> m;
    
    std::string *matrix = new std::string[n]();
    
    for (int i = 0; i < n; ++i)
        std::cin >> matrix[i];
    
    std::cout << getAnswer(n, m, matrix) << std::endl;
    
    delete[] matrix;
    return 0;
}*/