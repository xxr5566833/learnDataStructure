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
//���Ҫ��s�����������㹻�Ŀռ䣡
char *replaceSpaceBetter(char *s)
{
	//ע���s=null�ļ��
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
			//����������Ϊ�ǵ��Ÿ�ֵ������Ҫ���� 0 2 %��˳����
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
	//����ע�������ֱ����p2���������Ϊp2����û�е�����ˡ��������û�б�ģ�����������Ҫʹ��һ��ʼ��s
	std::cout << p1 << std::endl;
	return p1;
}




//��д�����þ���ͳ˷�˼����쳲�����������

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
