#include "Vector.h"

//�����ǹ���OJ����Ŀ������
//leetcode 11 �������������Ŀ����Ҫ�ö�̬�滮�����������̬�滮Ϊɶ�Ҿ��벻���أ�
/*

*/
int maxArea(Vector<int>& height) {
        
        int left = 0;
        int right = height.size() - 1;
        int result = 0;
        while(left < right)
        {
            result = max(result, (right - left) * min(height[left], height[right]));
            if(height[left] > height[right])
            {
                right --;
            }
            else{
                left++;
            }
        }
        return result;
    }
    
    
int min(int const &a, int const &b)
    {
        return a > b ? b : a;
    }
    int max(int const &a, int const &b)
    {
        return a > b ? a : b;
    }