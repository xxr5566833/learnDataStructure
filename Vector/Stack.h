#pragma once
#include "Vector.h"
#include "stdafx.h"

//stack.cpp��ĺ�������
double evaluate(char* S, char *& RPN);

template <typename T>
bool checkStackPermu(T *B, int n);
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

//����ĳһ�������Ƿ�Ϊԭ���е�һ��ջ��ϴ��
//����ͨ�����������Ƿ���(k, i, j)���߼��������Ƿ���(j+1, i, j)���жϣ����Ƿֱ���Ҫn3��n2
//��õļ��鷽������ͨ��ģ���������������
//����Ϊ�˷��㣬��ԭ��A������1-n
template <typename T>
bool checkStackPermu(T *B, int n)
{
	//B��ջ�׵�ջ����˳��
	int b = 0;
	Stack<T> S;
	int a = 1;
	while((a < n + 1 || !S.empty()) && b < n)
	{
		if(B[b] == a)
		{
			//�൱��S��������push��pop
			a++;
			b++;
		}
		else{
			if(!S.empty() && S.top() == B[b])
			{
				//Sջ���ǵ�ǰҪ������Ԫ��
				S.pop();
				b++;
			}
			else{
				//������������A�Ѿ����˾�ͷ����ô��һֱ��ΪҪ������������A�ĺ����һֱpush
				if(a >= n + 1)
					break;
				S.push(a++);
			}
		}
	}
	//ѭ������ʱ��SӦ���ǿյģ�����aΪn + 1��bΪn
	return a == n + 1 && b == n && S.empty();
}

//����ƥ���㷨

//�ݹ�ʵ��
//ɾ��exp[lo,hi]�������ŵ��ǰ׺����׺
void trim(const char exp[], int &lo, int &hi);
//�з�exp[lo,hi]��ʹexpƥ������ӱ��ʽƥ��
int divide(const char exp[], int lo, int hi);
//�����ʽexp[lo,hi]�Ƿ�����ƥ�䣬�ݹ��
bool paren(const char exp[], int lo, int hi);
//���lo��λ���Ǣٵ�һ�γ�����(����)��λ�â�hi+1 ���hi��λ�âٴ��������һ�γ�����(����)��λ�â�lo - 1

void trim(const char exp[], int &lo, int &hi)
{
	//����ġ�ɾ������ָͨ������lo,hi��ָ�룬����Сexp�ķ�Χ
	while(lo <= hi && exp[lo] != '(' && exp[lo] != ')')
		lo++;
	while(lo <= hi && exp[hi] != ')' && exp[hi] != '(')
		hi--;
}
//����˼���˺ܶ࣬ע���������зֵ�ʱ��һ���ҵ����ǵ�һ������������Ŀ��ȵĵط�
//��Ϊ������ܱ�֤��һ�Σ���ô�Ͳ��ܱ�֤����зֵ���ߵ�������е���������һ��������������ƥ���
//����()()()������ҵ����зֵ�������з�Ϊ ()() �� ()����ô�������������У������������������Ų������໥ƥ�����������
//��֤��ʱ�����Խ���������һ���������һ��ƥ����������У�ÿһ��������һ������Ψһһ����Ӧ�������ţ�������Ҳһ��
//��������Ϊ�˷��Σ���Ϊ�˰�S = (S1) S2 ��������������ƥ��ת��ΪS1��S2�����Ŷ�ƥ�䣬���Ǳ��뱣֤����зֵ��ǵ�һ����������ƥ��ĵط�
int divide(const char exp[], int lo, int hi)
{
	int lnum = 0;
	int rnum = 0;
	//����lo��÷���ǰ�����е����һ��λ�ã���Ȼ�޷�����Խ����������ֵ���������������������
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
	//�����ҵ�������������ŵ�λ��
	trim(exp, lo, hi);
	if(lo > hi)	return true;
	if(exp[lo] != '(')	return false;
	if(exp[hi] != ')')	return false;
	int mi = divide(exp, lo, hi);
	//�ж�mi��λ��
	if(mi > hi)
		return false;
	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}
//����������ʦ�Ļ������˼·
//O(n2)�ĸ��Ӷȣ���Ϊdivide()��Ҫ����ʱ��

//����ʵ������ƥ���飬����õ���ջ��
bool parenCheck(const char exp[], int lo, int hi);
bool parenCheck(const char exp[], int lo, int hi)
{
	//����ٶ����������ţ�С���У���
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
			//����û�м��S�Ƿ�Ϊ�գ�ÿһ���õ�top�ĵط���Ҫ�ǵü��S��empty��
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

//���ʽ��ֵ�㷨

enum op{PLUS, MINUS, MULT, DIV, POW, FAC, LP, RP, END};

//��������
/*
1.ջ����^, �������ȼ�С�ڵ�ǰ��(
2.ջ����^,�������ȼ�С�ڵ�ǰ��!
3.Ϊ�˷��㴦������һ��ʼ�ڷ���ջ��Ԥ��ѹ��һ��'\0'

*/

//һ��ʼȫ��-1��һ����д��һ��-1����
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
//��֪��ǰָ��ָ��һ�����ֵĿ�ʼ������������������ת��Ϊfloat�����������ջ�У�ͬʱ�ƶ�Sָ��
//ͬʱΪ�˷��㴦���������ҲҪ�������ַ�������ӵ����Ĳ�����׺�ַ�����
void readNumber(char *&S, Stack<double> &opndstack, char *&RPN)
{
	//����Ϊ��׼ȷֱ�����ֳɵĺ���atof
	//�涨����char��λ�����ܴ���100��
	char num[100] = {0};
	int p = 0;
	while((*S >= '0' && *S <= '9') || *S == '.')
	{
		num[p++] = *S;
		*RPN = *S;
		RPN++;
		S++;
	}
	//ÿ��������׺���ʽ���Ҫ���Ͽո񣬱�ʾ�����������֮��ķָ�
	*RPN = ' ';
	RPN++;

	opndstack.push(atof(num));
}

void append(char *&RPN, double );

//�Ա��ʽS��ֵ����ת��Ϊ�沨�����ʽ,����ٶ������Ѿ���ɾ���ո�
double evaluate(char* S, char *& RPN)
{
	//����ģ���಻��ʵ����Ϊö��?
	Stack<int> opstack;
	opstack.push(END);
	//����������Ҫһ��ջ��
	Stack<double> opndstack;
	//��ʼɨ��
	//ԭ��ѭ����������ֹ�����������ڱ�������break���������������ᷢ������Ϊwhile�������*S!='\0'����Ȼ���ܲ�Ӱ������������߼��ϻ������©��
	//��������ʹ�������ջ�Ƿ�Ϊ�����Ψһ���ж�������ȷ��ʲôʱ����ֹ
	//while(*S != '\0' || opstack.top() != END)
	while(!opstack.empty())
	{
		op curop;
		if(*S >= '0' && *S <= '9')
		{
			//�����ж��ǲ���һ������
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
		//����˵�ǰ��op�Ϳ��Ժ�ջ��op�Ƚ���
		//��̫�����֮ǰ���뷨����֮ǰ��Ȼ������2��ʾջ��С�ڵ�ǰ����0��ʾջ�����ڵ�ǰ
		if(privilege[opstack.top()][curop] == 2)
		{
			//˵��ջ�������С�ڵ�ǰ���������ô�����ѹջ
			opstack.push(curop);
			S++;
		}
		else if(privilege[opstack.top()][curop] == 0)
		{
			//˵��ջ����������ڵ�ǰ�����������ջ�������
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
			//���ǵ��������кϷ�����ô����һ���������������ȵ����
			//����ͳһ�������������ź������ڱ����������һ�������ǵ�����ǰջ�����������
			S++;
			opstack.pop();
		}
		
	}
	//����RPN���Ӹ�'\0'
	*RPN = '\0';
	return opndstack.pop();
}

//��rpn���ʽ����ֵ
double rpnEvaluate(char *rpn)
{
	//���ﲻд�ˣ������������־���ջ������������Ͱ���Ӧ�Ĳ�������ջ��Ȼ����㲢����ѹ�������ջ����ʱ����Ҫ�����ջ��
	return 0;
}