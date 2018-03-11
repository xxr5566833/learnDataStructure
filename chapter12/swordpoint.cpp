#include"stdafx.h"


char *replaceSpace(char *s)
{
	char r[50] = {0};
	int index = 0;
	while(*s != '\0')
	{
		if(*s == ' ' || *s == '\t' || *s == '\n')
		{
			r[index++] = '%';
			r[index++] = '2';
			r[index++] = '0';
		}
		else{
			r[index++] = *s;
		}
		s++;
	}
	r[index] = '\0';
	std::cout << r << std::endl;
	return r;
}
//这就要求s本身申请了足够的空间！
char *replaceSpaceBetter(char *s)
{
	//注意对s=null的检查
	if(!s)
		return 0;
	int length = 0;
	char *p1 = s;
	while(*s)
	{
		if(*s == ' ' || *s == '\t' || *s == '\n')
		{
			length += 2;
		}
		length += 1;
		s++;
	}
	char *p2 = p1 + length;
	while(p2 != s)
	{
		if(*s == ' ' || *s == '\t' || *s == '\n')
		{
			//错误：这里因为是倒着赋值，所以要按照 0 2 %的顺序来
			*p2 = '0';
			p2 --;
			*p2 = '2';
			p2 --;
			*p2 = '%';
			p2 --;
		}
		else{
			*p2 = *s;
			p2 --;
		}
		s --;
	}
	//错误：注意最后不能直接用p2来输出，因为p2可能没有到最左端。最左端是没有变的，所以我们需要使用一开始的s
	std::cout << p1 << std::endl;
	return p1;
}




//待写：利用矩阵和乘方思想求斐波那契数列项

/*int main(int argc, char *argv[])
{
	int a[50] = {1, 3, 5, 7, 9};
	int b[] = {-2, -4, -6, -8, -10};
	merge(a, 5, 50, b, 5);
	//test replace
	char s[50] = "we are family";
	char *p1 = replaceSpaceBetter(s);
	std::cout << p1 << std::endl;
	return 0;
}*/
