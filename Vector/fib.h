#pragma once
#include "stdafx.h"

class Fib{
public:
	Fib(int n);
	int get();
	int next();
	int prev();
private:
	int f, g;
};

//初始化为不小于n的最小Fibonacci项
Fib::Fib(int n)
{
	//这个处理很妙啊，fib(-1) = 1
	//如果一开始f = 0, g = 1，那么当n = 1时就不是返回1了，而是返回0，就不符合语义了
	f = 1, g = 0;
	while(g < n)
	{
		g = f + g;
		f = g - f;
	}
}

int Fib::get()
{
	return g;
}

int Fib::next()
{
	g = f + g;
	f = g - f;
	return g;
}

int Fib::prev()
{
	f = g - f;
	g = g - f;
	return g;
}