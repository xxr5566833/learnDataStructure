#include "stdafx.h"

enum op{PLUS, MINUS, MULT, DIV, POW, FAC, LP, RP, END};

//几处错误：
/*
1.栈顶是^, 它的优先级小于当前是(
2.栈顶是^,它的优先级小于当前是!
3.为了方便处理我们一开始在符号栈里预先压入一个'\0'

*/
int privilege[9][9] = {
	0, 0, 2, 2, 2, 2, 2, 0, 0,
	0, 0, 2, 2, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 2, 2, 2, 0, 0,
	0, 0, 0, 0, 0, 2, 2, 0, 0,
	0, 0, 0, 0, 0, 0, -1, 0, 0,
	2, 2, 2, 2, 2, 2, 2, 1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	2, 2, 2, 2, 2, 2, 2, -1, 1,
};

op opstack[100] ;
int optop = 0;
float numstack[100];
int numtop = 0;

int compute(char* s)
{
	int result = 0;
	opstack[optop++] = END;
	while(*s != '\0' || opstack[optop - 1] != END)
	{
		op curop;
		switch(*s)
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
			break;
		}
	}
	return 0;
}