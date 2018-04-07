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

//��ʼ��Ϊ��С��n����СFibonacci��
Fib::Fib(int n)
{
	//�����������fib(-1) = 1
	//���һ��ʼf = 0, g = 1����ô��n = 1ʱ�Ͳ��Ƿ���1�ˣ����Ƿ���0���Ͳ�����������
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