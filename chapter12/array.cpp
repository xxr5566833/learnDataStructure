#include "stdafx.h"

int minimumInArray(int a[], int left, int right)
{
	int min = 0x7fffffff;
	for(int i = left ; i <= right ; i++)
	{
		if(a[i] < min)
		{
			min = a[i];
		}
	}
	return min;
}

//一开始一直在想，如何通过比较中间的元素与它相邻的元素的大小关系来判断最小元素的位置
//但是其实应该比较中间的元素与两端的元素之间的大小关系才对哎
int findMinInRotate(int a[], int size)
{
	if(size < 1)
		return 0x80000001;
	if(size == 1)
		return a[0];
	int left = 0;
	int right = size - 1;
	//为了防止对方直接把已排好序的数组书进来，所以这里要检查，如果a[left] < a[right] 那么需要直接输出a[left]
	while(left + 1 != right && a[left] >= a[right])
	{
		int mid = (left + right) / 2;
		int leftvalue = a[left];
		int midvalue = a[mid];
		int rightvalue = a[right];
		//当左端，右端，中间的值是一样的时候，我们需要使用顺序查找，因为此时无法确定该往哪边找
		if(leftvalue >= midvalue)
		{
			if(leftvalue == midvalue && midvalue == rightvalue)
			{
				return minimumInArray(a, left, right);
			}
			right = mid;
		}
		else{
			left = mid;
		}
	}
	if(a[left] >= a[right])
	{
		return a[right];
	}
	else{
		return a[left];
	}
}

//一开始想的是仿照快排的partition的写法，现在很疑惑为什么快排不一个指针从前走，一个指针从后走呢？（快排partition已经修改）
//数组分成两部分这个问题是可以扩展的，即不一定是按奇偶分，还可能是其他的判断依据，这时可以通过函数指针来支持不同的判断依据
void oddFirst(int a[], int size)
{
	if(size <= 1)
		return ;
	int i = 0;
	int j = size - 1;
	while(i < j)
	{
		while(i < size && (a[i] & 1))
		{
			i++;
		}
		while(j < size && !(a[j] & 1))
		{
			j--;
		}
		if(i < j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;;
		}

	}
	for(int i = 0 ; i < size ; i ++)
	{
		std::cout << a[i] << std::endl;
	}
}
//将a中所有非零元素一次移动到数组的前端，清华数据结构2.7
void notZeroFirst(int a[], int size)
{
	int i = 0;
	int j = size - 1;
	while(i < j)
	{
		while(i < j && a[i] != 0)
		{
			i++;
		}
		while(i < j && a[j] == 0)
		{
			j--;
		}
		if(i != j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		i++;
		j--;
	}
}

//从外向里顺时针顺序打印数字，需要检查二维数组是否合格，但是不好检查，因为C++对于越界不报错,那我现在就直接用了
//思路：每一次都是打印一个“长方形”的一条边
void clockWisePrint(int **a, int size)
{
	if(!a)
		return ;
	int left = 0;
	int right = size - 1;
	int top = 0;
	int bottom = size - 1;
	while(left <= right && top <= bottom)
	{
		if(left <= right && top <= bottom)
		{
			for(int i = left ; i <= right ; i++)
			{
				std::cout << a[top][i] << std::endl;
			}
			top++;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = top ; i <= bottom ; i++)
			{
				std::cout << a[i][right] << std::endl;
			}
			right --;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = right ; i >= left ; i--)
			{
				std::cout << a[bottom][i] << std::endl;
			}
			bottom --;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = bottom ; i >= top ; i--)
			{
				std::cout << a[i][left] << std::endl;
			}
			left ++;
		}
	}
}
//在一个排好序的数组中，给一个数字s，在这个数组中求和为s的两个数
//一开始我的思路是，首先求 s/2然后把数组分成大于s/2和小于s/2，然后左半部分指针向左移动，右半部分向右移动，但是这样其实是没有必要的，即没必要从中间开始找
//直接从两端开始找就好了

//在一个给了长度length，而且知道了里面每个元素都在（0， length-1）之间的数组中查找是否有重复的元素，如果有，那么输出一个出来
//简单的想法就是另外开辟一个空间统计
//但是实际上可以通过在原数组上做一些修改来实现，每次遇到一个数字，就把以它为下标的元素加上length，如果下一次遇到了一个数字在给相应元素加length时
//发现已经加过了，那么说明这个数字是重复的


//把一个数组逆置，清华大学数据结构2.6
//书上的做法和算法导论里的快排的partition一样
void reverseArray(int a[], int size)
{
	//数组逆序，交换就行了
	for(int i = 0 ; i < size / 2 ; i ++)
	{
		int temp = a[i];
		a[i] = a[size - i - 1];
		a[size - i - 1] = temp;
	}
}
//不多于3n/2次的平均比较次数，找到最大值和最小值
//记得在大二第一次看这个算法的时候都看不懂。。
void findMaxAndMin(int a[], int size)
{
	if(size <= 0)
		return ;
	int min = 0x7fffffff;
	int max = 0x80000000;
	for(int i = 0 ; i < size ; i = i + 2)
	{
		int num1 = a[i];
		if(i + 1 < size)
		{
			//即下一个元素存在
			int num2 = a[i + 1];
			int tempmin;
			int tempmax;
			if(num1 < num2)
			{
				tempmin = num1;
				tempmax = num2;
			}
			else{
				tempmax = num1;
				tempmin = num2;
			}
			if(tempmax > max)
			{
				max = tempmax;
			}
			if(tempmin < min)
				min = tempmin;
		}
		else{
			if(num1 > max)
				max = num1;
			if(num1 < min)
				min = num1;
		}
	}
	std::cout << max << std::endl;
	std::cout << min << std::endl;
}

//两个顺序表比较大小，清华数据结构2.13，定义在这里
//a < b返回-1 a==b 返回0 a > b返回1
int compare2Array(char *a, char *b)
{
	//不如说这个就是strcmp函数的实现
	//现在约定a和b都是以\0为结束符的字符串，现在比较这两个字符串
	//如果a或b为null
	if(!a || !b)
		return -2;
	while(*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	if(!(*a))
	{
		//a结束了
		if(!(*b))
		{
			//b也结束了
			return 0;
		}
		else{
			return -1;
		}
	}
	else{
		if(!(*b))
			return 1;
		else{
			int result;
			*a > *b ? result = 1 : result = -1;
			return result;
		}
	}
}

/*int main(int argc, char* argv[])
{
	char *a = " 2";
	char *b = "  ";
	std::cout << compare2Array(a, b) << std::endl;

	return 0;
}*/