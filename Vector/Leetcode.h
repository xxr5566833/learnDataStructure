#include "Vector.h"

//下面是关于OJ上题目的整理
//leetcode 11 最大面积，这个题目还是要用动态规划，但是这个动态规划为啥我就想不到呢？
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