#pragma once
#include "Vector.h"
#include "Queue.h"
#include "stdafx.h"

//测试用的声明
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
	void reverse();
};

void readNumber(char *&p, Stack<double> &opndstack);

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

//在只有一种括号时，只需要保证一下两个原则即可保证整个表达式合法
//1. 在表达式任意前缀中，左括号数量都大于等于右括号数量
//2.整个表达式的左右括号数量相等，
//所以在只有一种括号时，完全可以用一个数字来记录左右括号数目之差，如果这个数目能在扫描过程中一直保持大于等于0，且最后等于0，那么说明这个表达式的括号合法

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

//上面的readNumber是通过atof实现的，下面自己手写课后题4-6自己实现一个readNumber
//语义：将起始为p的数字字串解析为double，并存入stack操作数栈中
void readNumber(char *&p, Stack<double> &opndstack)
{
	double result = 0;
	while(*p >= '0' && *p <= '9')
	{
		result = result *10.0 + (*p - '0');
		p++;
	}
	if(*p == '.')
	{
		p++;
		//那么还需要处理小数位
		double tail = 0;
		double fraction = 0.1;
		while(*p >= '0' && *p <= '9')
		{
			tail = tail + (*p - '0') * fraction;
			fraction /= 10;
			p++;
		}
		result += tail;
	}
	opndstack.push(result);
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

//习题4-18费马-拉格朗日定理
//对于任意一个自然数n，找出所有费马-拉格朗日的解并输出
void findAnswer(int n);

void findAnswer(int n)
{
	//answer表示已经有的前k个数字
	Stack<int> answer;
	int count = 0;
	answer.push(0);
	while(1)
	{	
		int sum = 0;
		for(int i = 0 ; i < answer.size() ; i++)
		{
			int s = answer[i];
			sum += answer[i] * answer[i];
		}
		if(answer.size() < 4)
		{
			//现在数字还不够
			if(sum <= n)
			{
				//和也没达到要求，sum <= n，那么把当前栈顶的这个数字加入到解答栈中，因为要遵循四个数字非减的次序，所以直接把栈顶元素再次入栈
				//注意answer.top返回的是一个引用，这里不要直接把top()继续入栈，这就相当于一个元素重复入栈，而这四个元素应该是互相独立的，所以这里加0让它形成一个新的变量
				//如果直接把top()入栈，那么在某次vector扩容时，会delete掉之前的数组_elem，即_elem的原来的元素都失效了，
				//而push是调用了insert，top获得的是最后一个元素的引用，所以如果在某次调用push(top())时，top()的元素，即原来_elem的最后一个元素失效了
				//那么之后insert的可能是一个错误的元素值
				answer.push( answer.top() + 0);
			}
			else{
				//数字不够，但是sum>n ，这说明，接下来再加数字一定还是sum >n ，那么我们必须要撤出数字
				//说明栈顶元素这个位置上的数字已经没有解了，此时我们必须要把栈顶元素pop，然后把之后的栈顶元素加1，表示下一次搜索
				//如果栈规模只有一个，那么说明搜索到了仅仅一个元素的平方就比n大，那么没有搜索的必要了，break
				if(answer.size() == 1)
				{
					break;
				}
				else{
					answer.pop();
					answer.top() += 1;
				}
			}
		}
		else{
			//数字已经足够了，那么看当前的sum
			if(sum < n)
			{
				//和比n小，那么很简单最后一个数字继续搜索
				answer.top() += 1;
			}
			else if(sum == n)
			{
				//找到了一个解！
				std::cout << "第" << count++ << "个解:" << std::endl;
				for(int i = 0 ; i < answer.size() ; i++)
				{
					std::cout << answer[i] << " " ;
				}
				std::cout << std::endl;
				//找到解以后，如果再增加最后一个数，那么最后sum一定会大于n，故这里还是需要回溯
				answer.pop();
				answer.top() += 1;
			}
			else{
				//sum比n大了，那么此时再增加最后一个元素没有意义，所以就回溯
				answer.pop();
				answer.top() += 1;
			}
		}
	}
}

//暂且约定按照自然优先级，并且不使用括号，考察在数字0-9之间加入 + * 后构成的合法算数表达式
//编写一个程序，对于任意一个给定的整数S，给出所有值为S的表达式
//利用以及写好的表达式求值，我们最重要的任务是枚举出所有的可能的表达式和数字的组合情况
//对于一个数字序列，我们可以选择一个切分点，这个切分点上放上操作符，
//对于被切分的两个序列， 我们可以获得他们可能的所有情况以及对应的值
void getExpression(int S)
{
	
}

//栈的reverse
template <typename T>
void Stack<T>::reverse()
{
	Queue<T> q;
	while(!empty())
		q.enqueue(pop());
	while(!q.empty())
		push(q.dequeue());
}