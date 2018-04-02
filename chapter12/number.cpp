#include "stdafx.h"

//这么简单的一个函数也有很多坑，num为负数时右移会出现死循环，所以我们不能右移num，我们可以左移一个标志位
int count1InBinary(int num)
{
	int count = 0;
	unsigned int flag = 1;
	/*while(num)
	{
		//取余也直接用和1做且的位运算
		count += num % 2;
		//除以2用右移！！！而且注意只移1位！！！
		num = num >> 1;
	}*/
	while(flag)
	{
		if(num & flag)
			count ++;
		flag = flag << 1;
	}
	return count;
}
//利用一个数 与 它减1的结果 按位与后结果会把原来数字的最右边的1变成0，所以能进行多少次这样的操作，那么就有几个1
//一开始想到它的减一，也发现了减一会把最右边的1变成0然后右边的位变成1，但是没有想到和原来做与运算会把原来的1去掉
int count1InBinaryBetter(int num)
{
	int count = 0;
	while(num)
	{
		count += 1;
		num = num & (num - 1);
	}
	return count;
}
//判断一个语句是否是2的整数次方，用上面的性质，如果和它-1的结果相与以后变成了0，那么说明原来只有一个1，那么说明这个数字是2的整数次方

bool doubleEqual(double a, double b)
{
	const double e = 0.0000001;
	//这里绝对值公式不能忘了啊 |a| < e -> a < e 且 a > -e (e是一个正数)
	return a - b > -e && a - b < e;
}

double computePow(double base, unsigned int pow)
{
	//此时pow已经是一个正整数幂次了
	double result = 1.;
	unsigned int flag = 1;
	while(flag)
	{
		if(pow & flag)
		{
			result = result * base;
		}
		flag = flag << 1;
		base = base * base;
	}
	return result;
}

//求base的exponent次方
//这里也可以递归实现
double power(double base, int exponent)
{
	if(exponent > 0)
	{
		return computePow(base, exponent);
	}
	else if(exponent < 0)
	{
		//double类型的比较不要用==！这个在oo课上讲过
		if(doubleEqual(base, 0.))
		{
			std::cout << "不能计算0的负数次方" << std::endl;
			return 0.;
		}
		double result = computePow(base, -exponent);
		//计算幂次有更快的方法。。
		result = 1.0 / result;
		return result;
	}
	else{
		if(doubleEqual(base, 0.))
		{
			std::cout << "不能计算0的0次方" << std::endl;
			return 0;
		}
		else{
			return 1.;
		}
	}
}
//我的思路：申请n+1长度的字符数组，第n+1位初始化为\0 ，其余初始化为‘0’
//然后输出利用指针，这个指针指向有效的最高位上
void printNBit10baseNumber(int n)
{
	if(n <= 0)
	{
		std::cout << "n必须大于0" << std::endl;
		return ;
	}
	char *number = new char[n + 1];
	for(int i = 0 ; i < n ; i ++)
	{
		number[i] = '0';
	}
	number[n] = '\0';
	int length = 1;
	while(1)
	{
		char *pos = number + n - 1;
		while(pos >= number && *pos == '9')
		{
			*pos = '0';
			if(pos == number + n - length)
			{
				length ++;
			}
			if(pos == number)
			{
				delete[] number;
				return ;
			}
			pos --;
		}
		*pos = *pos + 1;
		
		std::cout << number + n - length << std::endl;
	}
	//注意申请的内存要被释放！！
}

//全排列也可以实现啊!!
//递归实现全排列

void quanpailiePrint(int size, char *a, int index)
{
	if(size <= 0)
		return ;
	if(!a)
	{
		//a是存储数字的字符数组，因为不知道对方要输出多大的数组所以一开始是null
		//当检测到是null，那就初始化，不是null那就直接拿来用
		//而且可以肯定的是只有n等于用户输入的n时才可能会初始化
		a = new char[size + 1];
		for(int i = 0 ; i < size ; i ++)
		{
			a[i] = '0';
		}
		a[size] = '\0';
	}
	if(index == size - 1)
	{
		//说明前面的位置上都已经设置好了数字，此时仅需要从非0位开始输出即可
		char *p = a;
		while(*p == '0')
			p++;
		if(p == a + size)
			p--;
		for(int i = 1 ; i < 10 ; i++)
		{
			//设置一下输出一下
			a[index] = '0' + i;
			std::cout << p << std::endl;
		}
	}
	else{
		for(int i = 0 ; i < 10 ; i++)
		{
			//其他位置上都是0 - 9
			a[index] = i + '0';
			quanpailiePrint(size, a, index + 1);
		}
	}
}

//给定一个数字，求所有的连续正整数序列和为这个数字的序列
//我的思路是这样的： 发现了一个规律，有长度为2的序列，那么你只需要除以2余1，有长度为3的序列，那么只需要能整除3，有长度为2a的序列，只需要除以2a余a，有长度为2a+1的序列，只需要能
//整除2a+1 ，
//书上的思路是维护一个 (begin, end)最大值为end，最小值为begin的序列，大了就增加begin减少数字个数，笑了就增大end，增加数字个数


//不用数组，仅需两个数字就实现斐波那契（邓老师视频）
//设fib(0) = 0
int fib(int n)
{
	if(n < 0)
		return -1;
	int f = 0, g = 1;
	while(n--)
	{
		g = f + g;
		f = g - f;
	}
	return f;
}
int main(int argc, char* argv[])
{
	quanpailiePrint(2, 0, 0);
	return 0;
}

