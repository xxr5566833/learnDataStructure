#pragma once
#include "Bitmap.h"

//返回不小于n的素数
int Eratosthenes(int n);

int Eratosthenes(int n)
{
	/*
	对小于7.263x10^13的所有相邻素数的间隔作了统计，确定了最小的间隔是1，最大是777
	所以这里我们设置最大长度为n + 777
	*/
	Bitmap  m = Bitmap(n + 778);
	for(int i = 2 ; i * i <= n ; i++)
	{
		//对于素数才需要设置它的倍数的标志位，如果已经被设置标志位，那么不需要遍历了！
		if(!m.test(i))
		{
			//这里j完全可以从i 开始
			for(int j = i ; i * j <= n ; j += 1)
			{
				m.set(i * j);
			}
		}
	}
	for(int i = n ; i < n + 777 ; i++)
	{
		if(!m.test(i))
			return i;
	}
	//失败是不可能失败的，这里失败统一返回n - 1
	return n - 1;
}