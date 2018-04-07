#pragma once
#include "Vector.h"
#include "stdafx.h"

//stack.cpp里的函数声明
double evaluate(char* S, char *& RPN);

template <typename T>
bool checkStackPermu(T *B, int n);
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

//检验某一个序列是否为原序列的一个栈混洗，
//可以通过检验其中是否含有(k, i, j)或者检验其中是否含有(j+1, i, j)来判断，但那分别需要n3和n2
//最好的检验方法还是通过模拟这个过程来检验
//这里为了方便，设原来A序列是1-n
template <typename T>
bool checkStackPermu(T *B, int n)
{
	//B是栈底到栈顶的顺序
	int b = 0;
	Stack<T> S;
	int a = 1;
	while((a < n + 1 || !S.empty()) && b < n)
	{
		if(B[b] == a)
		{
			//相当于S连续两次push和pop
			a++;
			b++;
		}
		else{
			if(!S.empty() && S.top() == B[b])
			{
				//S栈顶是当前要弹出的元素
				S.pop();
				b++;
			}
			else{
				//这里如果不检测A已经到了尽头，那么会一直以为要弹出的数字在A的后面会一直push
				if(a >= n + 1)
					break;
				S.push(a++);
			}
		}
	}
	//循环结束时，S应该是空的，而且a为n + 1，b为n
	return a == n + 1 && b == n && S.empty();
}

//括号匹配算法

//递归实现
//删除exp[lo,hi]不含括号的最长前缀，后缀
void trim(const char exp[], int &lo, int &hi);
//切分exp[lo,hi]，使exp匹配仅当子表达式匹配
int divide(const char exp[], int lo, int hi);
//检查表达式exp[lo,hi]是否括号匹配，递归版
bool paren(const char exp[], int lo, int hi);
//最后lo的位置是①第一次出现了(或者)的位置②hi+1 最后hi的位置①从右往左第一次出现了(或者)的位置②lo - 1

void trim(const char exp[], int &lo, int &hi)
{
	//这里的“删除”是指通过调整lo,hi的指针，来缩小exp的范围
	while(lo <= hi && exp[lo] != '(' && exp[lo] != ')')
		lo++;
	while(lo <= hi && exp[hi] != ')' && exp[hi] != '(')
		hi--;
}
//这里思考了很多，注意这里招切分点时，一定找到的是第一次左右括号数目相等的地方
//因为如果不能保证第一次，那么就不能保证这个切分点左边的这个序列的最左括号一定和最右括号是匹配的
//比如()()()，如果找到的切分点把序列切分为 ()() 和 ()，那么对于左边这个序列，最左括号与最右括号并不是相互匹配的两个括号
//故证明时，可以建立这样的一个概念，对于一个匹配的括号序列，每一个左括号一定都有唯一一个对应的右括号，右括号也一样
//所以我们为了分治，即为了把S = (S1) S2 这样的序列括号匹配转化为S1和S2的括号都匹配，我们必须保证这各切分点是第一次左右括号匹配的地方
int divide(const char exp[], int lo, int hi)
{
	int lnum = 0;
	int rnum = 0;
	//这里lo最好返回前半序列的最后一个位置，不然无法区分越界和整个部分的左右括号相等这两种情况
	while(lo < hi)
	{
		if(exp[lo] == ')')
			rnum++;
		if(exp[lo] == '(')
			lnum++;
		if(rnum == lnum && rnum != 0)
			break;
		lo++;
	}
	return lo;
}

bool paren(const char exp[], int lo, int hi)
{
	//首先找到最左和最右括号的位置
	trim(exp, lo, hi);
	if(lo > hi)	return true;
	if(exp[lo] != '(')	return false;
	if(exp[hi] != ')')	return false;
	int mi = divide(exp, lo, hi);
	//判断mi的位置
	if(mi > hi)
		return false;
	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}
//上面代码和老师的基本差不多思路
//O(n2)的复杂度，因为divide()需要线性时间

//迭代实现括号匹配检查，这就用到了栈了
bool parenCheck(const char exp[], int lo, int hi);
bool parenCheck(const char exp[], int lo, int hi)
{
	//这里假定有三种括号，小，中，大
	Stack<char> S;
	for(int i = lo ; i <= hi ; i++)
	{
		switch(exp[i])
		{
		case '(':
		case '{':
		case '[':
			S.push(exp[i]);
			break;
		case ')':
		case ']':
		case '}':
			//这里没有检查S是否为空，每一次用到top的地方都要记得检查S的empty！
			if(!S.empty() && S.top() == exp[i])
				S.pop();
			else return false;
			break;
		default:
			break;
		}
	}
	return S.empty();
}

//表达式求值算法

enum op{PLUS, MINUS, MULT, DIV, POW, FAC, LP, RP, END};

//几处错误：
/*
1.栈顶是^, 它的优先级小于当前是(
2.栈顶是^,它的优先级小于当前是!
3.为了方便处理我们一开始在符号栈里预先压入一个'\0'

*/

//一开始全是-1那一行少写了一个-1。。
int privilege[9][9] = {
	0, 0, 2, 2, 2, 2, 2, 0, 0,
	0, 0, 2, 2, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 0, 2, 2, 0, 0,
	0, 0, 0, 0, 0, 0, -1, 0, 0,
	2, 2, 2, 2, 2, 2, 2, 1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1,
	2, 2, 2, 2, 2, 2, 2, -1, 1,
};
//已知当前指针指向一个数字的开始，这个方法把这个数字转化为float并放入操作数栈中，同时移动S指针
//同时为了方便处理，这个方法也要把数字字符数组给加到最后的波兰后缀字符串里
void readNumber(char *&S, Stack<double> &opndstack, char *&RPN)
{
	//这里为了准确直接用现成的函数atof
	//规定数字char的位数不能大于100个
	char num[100] = {0};
	int p = 0;
	while((*S >= '0' && *S <= '9') || *S == '.')
	{
		num[p++] = *S;
		*RPN = *S;
		RPN++;
		S++;
	}
	//每个波兰后缀表达式最后要加上空格，表示运算符和数字之间的分隔
	*RPN = ' ';
	RPN++;

	opndstack.push(atof(num));
}

void append(char *&RPN, double );

//对表达式S求值，并转换为逆波兰表达式,这里假定输入已经被删除空格
double evaluate(char* S, char *& RPN)
{
	//这里模板类不能实例化为枚举?
	Stack<int> opstack;
	opstack.push(END);
	//操作数必须要一个栈的
	Stack<double> opndstack;
	//开始扫描
	//原来循环结束的终止条件：左右哨兵相遇就break，但是这个情况不会发生，因为while条件里的*S!='\0'，虽然可能不影响最后结果但是逻辑上还是有纰漏的
	//所以我们使用运算符栈是否为空这个唯一的判断条件来确定什么时候终止
	//while(*S != '\0' || opstack.top() != END)
	while(!opstack.empty())
	{
		op curop;
		if(*S >= '0' && *S <= '9')
		{
			//首先判断是不是一个数字
			readNumber(S, opndstack, RPN);

			continue;
		}
		switch(*S)
		{
		case '+':
			curop = PLUS;
			break;
		case '-':
			curop = MINUS;
			break;
		case '*':
			curop = MULT;
			break;
		case '/':
			curop = DIV;
			break;
		case '^':
			curop = POW;
			break;
		case '!':
			curop = FAC;
			break;
		case '(':
			curop = LP;
			break;
		case ')':
			curop = RP;
			break;
		case '\0':
			curop = END;
		}
		//获得了当前的op就可以和栈顶op比较了
		//不太理解我之前的想法：我之前竟然想着让2表示栈顶小于当前，用0表示栈顶大于当前
		if(privilege[opstack.top()][curop] == 2)
		{
			//说明栈顶运算符小于当前运算符，那么运算符压栈
			opstack.push(curop);
			S++;
		}
		else if(privilege[opstack.top()][curop] == 0)
		{
			//说明栈顶运算符大于当前运算符，计算栈顶运算符
			curop = (op)opstack.pop();
			if(curop == FAC)
			{
				double opnd1 = opndstack.pop();
				int result = 1;
				while((int)opnd1--)
				{
					result *= (opnd1 + 1);
				}
				opndstack.push(result);
				*RPN = '!';
				RPN++;
				*RPN = ' ';
				RPN++;
				continue;
			}
			double opnd2 = opndstack.pop();
			double opnd1 = opndstack.pop();
			double result = 0;
			switch(curop)
			{
			case PLUS:
					result = opnd2 + opnd1;
					*RPN = '+';
					RPN++;
					*RPN = ' ';
					RPN++;
					break;
			case MINUS:
					result = opnd1 - opnd2;
					*RPN = '-';
					RPN++;
					*RPN = ' ';
					RPN++;
					break;
			case MULT:
					result = opnd1 * opnd2;
					*RPN = '*';
					RPN++;
					*RPN = ' ';
					RPN++;
					break;
			case DIV:
					result = opnd1 / opnd2;
					*RPN = '/';
					RPN++;
					*RPN = ' ';
					RPN++;

					break;
			case POW:
					result = pow(opnd1, opnd2);
					*RPN = '^';
					RPN++;
					*RPN = ' ';
					RPN++;
					break;
			}
			opndstack.push(result);

		}
		else {
			//考虑到输入序列合法，那么这里一定是两个运算符相等的情况
			//这里统一处理，即左右括号和两个哨兵相遇的情况一起处理，都是弹出当前栈顶运算符即可
			S++;
			opstack.pop();
		}
		
	}
	//最后把RPN最后加个'\0'
	*RPN = '\0';
	return opndstack.pop();
}

//对rpn表达式的求值
double rpnEvaluate(char *rpn)
{
	//这里不写了，就是遇到数字就入栈，遇到运算符就把相应的操作数出栈，然后计算并重新压入操作数栈，此时不需要运算符栈了
	return 0;
}