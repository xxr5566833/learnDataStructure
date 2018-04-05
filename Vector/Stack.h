#include "Vector.h"
#include "stdafx.h"


//�����б�ʵ�ֿ��ܻ���ã���Ϊջ������һ�˽���������vector��ѭ�ȷ���ûʲô�ã����һ���Ҫ��̬����
template <typename T>
class Stack:public Vector<T>
{
public:
	//�����������Ϊջ�����޴�����Ϊ
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

//����ȷ���㷨�� ���ǽ�����������е���ʽ��������������ǵݹ黹�ǵ���ʵ�֣����ж���������������Ȼ�����������Ĺ�ģ��ȷ������������ȷ�������������С
//��һ������Ϳ�����ջ
/*
//����ת��
void convert(Stack<char> &S, __int64 n, int base)
{
	//ʮ������n��base���Ƶ�ת��
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

//����ʵ��
void convert(Stack<char> &S, __int64 n, int base)
{
	//ʮ������n��base���Ƶ�ת��
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