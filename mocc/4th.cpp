#include "stdafx.h"
//20 - 
// n, m：意义如题
// matrix：一个字符串数组，用来记录所给矩形，matrix[i][j]表示所给矩形第i行第j列的字符（下标均从0开始）
// 返回值：题目所求答案，即最大矩形面积
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
		//1.获得以当前行为最低行的直方图的高度数组
		for(int j = 0 ; j < m ; j++)
		{
			if(matrix[i][j] == '.')
				height[j] += 1;
			else	height[j] = 0;
		}
		//2.利用之前的算法，求出这个直方图的最大矩形面积
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
    std::ios::sync_with_stdio(false);  // 读入优化
    
    int n, m;
    std::cin >> n >> m;
    
    std::string *matrix = new std::string[n]();
    
    for (int i = 0; i < n; ++i)
        std::cin >> matrix[i];
    
    std::cout << getAnswer(n, m, matrix) << std::endl;
    
    delete[] matrix;
    return 0;
}*/