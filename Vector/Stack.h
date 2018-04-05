#include "Vector.h"
#include "stdafx.h"


//觉得列表实现可能会更好，因为栈总是在一端进出，所以vector的循秩访问没什么用，而且还需要动态扩容
template <typename T>
class Stack:public Vector<T>
{
public:
	//拿向量左端作为栈顶是愚蠢的行为
	void push(T const&e) {insert(size(), e);}
	T pop()
	{
		return remove(size() - 1);
	}
	T &top()
	{
		return _elem[size() - 1];
	}
};

//有明确的算法， 但是解答以线性序列的形式给出，其次无论是递归还是迭代实现，序列都是逆序计算输出，然后输入和输出的规模不确定，难以事先确定所需的容量大小
//这一类问题就可以用栈
/*
//进制转换
void convert(Stack<char> &S, __int64 n, int base)
{
	//十进制数n到base进制的转换
	static char digit[] = 
	{'0', '1', '2', '3', '4', '5', '6', '7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int result = n / base;
	int remain = n % base;
	S.push(digit[remain]);
	if(result)
	{
		convert(S, result, base);
	}
}
*/

//迭代实现
void convert(Stack<char> &S, __int64 n, int base)
{
	//十进制数n到base进制的转换
	static char digit[] = 
	{'0', '1', '2', '3', '4', '5', '6', '7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'};
	S.push(digit[n % base]);
	n = n / base;
	while(n)
	{
		S.push(digit[n % base]);
		n = n / base;
	}
}