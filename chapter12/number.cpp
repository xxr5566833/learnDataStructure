#include "stdafx.h"

//��ô�򵥵�һ������Ҳ�кܶ�ӣ�numΪ����ʱ���ƻ������ѭ�����������ǲ�������num�����ǿ�������һ����־λ
int count1InBinary(int num)
{
	int count = 0;
	unsigned int flag = 1;
	/*while(num)
	{
		//ȡ��Ҳֱ���ú�1���ҵ�λ����
		count += num % 2;
		//����2�����ƣ���������ע��ֻ��1λ������
		num = num >> 1;
	}*/
	while(flag)
	{
		if(num & flag)
			count ++;
		flag = flag << 1;
	}
	return count;
}
//����һ���� �� ����1�Ľ�� ��λ��������ԭ�����ֵ����ұߵ�1���0�������ܽ��ж��ٴ������Ĳ�������ô���м���1
//һ��ʼ�뵽���ļ�һ��Ҳ�����˼�һ������ұߵ�1���0Ȼ���ұߵ�λ���1������û���뵽��ԭ������������ԭ����1ȥ��
int count1InBinaryBetter(int num)
{
	int count = 0;
	while(num)
	{
		count += 1;
		num = num & (num - 1);
	}
	return count;
}
//�ж�һ������Ƿ���2�������η�������������ʣ��������-1�Ľ�������Ժ�����0����ô˵��ԭ��ֻ��һ��1����ô˵�����������2�������η�

bool doubleEqual(double a, double b)
{
	const double e = 0.0000001;
	//�������ֵ��ʽ�������˰� |a| < e -> a < e �� a > -e (e��һ������)
	return a - b > -e && a - b < e;
}

double computePow(double base, unsigned int pow)
{
	//��ʱpow�Ѿ���һ���������ݴ���
	double result = 1.;
	unsigned int flag = 1;
	while(flag)
	{
		if(pow & flag)
		{
			result = result * base;
		}
		flag = flag << 1;
		base = base * base;
	}
	return result;
}

//��base��exponent�η�
//����Ҳ���Եݹ�ʵ��
double power(double base, int exponent)
{
	if(exponent > 0)
	{
		return computePow(base, exponent);
	}
	else if(exponent < 0)
	{
		//double���͵ıȽϲ�Ҫ��==�������oo���Ͻ���
		if(doubleEqual(base, 0.))
		{
			std::cout << "���ܼ���0�ĸ����η�" << std::endl;
			return 0.;
		}
		double result = computePow(base, -exponent);
		//�����ݴ��и���ķ�������
		result = 1.0 / result;
		return result;
	}
	else{
		if(doubleEqual(base, 0.))
		{
			std::cout << "���ܼ���0��0�η�" << std::endl;
			return 0;
		}
		else{
			return 1.;
		}
	}
}
//�ҵ�˼·������n+1���ȵ��ַ����飬��n+1λ��ʼ��Ϊ\0 �������ʼ��Ϊ��0��
//Ȼ���������ָ�룬���ָ��ָ����Ч�����λ��
void printNBit10baseNumber(int n)
{
	if(n <= 0)
	{
		std::cout << "n�������0" << std::endl;
		return ;
	}
	char *number = new char[n + 1];
	for(int i = 0 ; i < n ; i ++)
	{
		number[i] = '0';
	}
	number[n] = '\0';
	int length = 1;
	while(1)
	{
		char *pos = number + n - 1;
		while(pos >= number && *pos == '9')
		{
			*pos = '0';
			if(pos == number + n - length)
			{
				length ++;
			}
			if(pos == number)
			{
				delete[] number;
				return ;
			}
			pos --;
		}
		*pos = *pos + 1;
		
		std::cout << number + n - length << std::endl;
	}
	//ע��������ڴ�Ҫ���ͷţ���
}

//ȫ����Ҳ����ʵ�ְ�!!
//�ݹ�ʵ��ȫ����

void quanpailiePrint(int size, char *a, int index)
{
	if(size <= 0)
		return ;
	if(!a)
	{
		//a�Ǵ洢���ֵ��ַ����飬��Ϊ��֪���Է�Ҫ���������������һ��ʼ��null
		//����⵽��null���Ǿͳ�ʼ��������null�Ǿ�ֱ��������
		//���ҿ��Կ϶�����ֻ��n�����û������nʱ�ſ��ܻ��ʼ��
		a = new char[size + 1];
		for(int i = 0 ; i < size ; i ++)
		{
			a[i] = '0';
		}
		a[size] = '\0';
	}
	if(index == size - 1)
	{
		//˵��ǰ���λ���϶��Ѿ����ú������֣���ʱ����Ҫ�ӷ�0λ��ʼ�������
		char *p = a;
		while(*p == '0')
			p++;
		if(p == a + size)
			p--;
		for(int i = 1 ; i < 10 ; i++)
		{
			//����һ�����һ��
			a[index] = '0' + i;
			std::cout << p << std::endl;
		}
	}
	else{
		for(int i = 0 ; i < 10 ; i++)
		{
			//����λ���϶���0 - 9
			a[index] = i + '0';
			quanpailiePrint(size, a, index + 1);
		}
	}
}

//����һ�����֣������е��������������к�Ϊ������ֵ�����
//�ҵ�˼·�������ģ� ������һ�����ɣ��г���Ϊ2�����У���ô��ֻ��Ҫ����2��1���г���Ϊ3�����У���ôֻ��Ҫ������3���г���Ϊ2a�����У�ֻ��Ҫ����2a��a���г���Ϊ2a+1�����У�ֻ��Ҫ��
//����2a+1 ��
//���ϵ�˼·��ά��һ�� (begin, end)���ֵΪend����СֵΪbegin�����У����˾�����begin�������ָ�����Ц�˾�����end���������ָ���


//�������飬�����������־�ʵ��쳲�����������ʦ��Ƶ��
//��fib(0) = 0
int fib(int n)
{
	if(n < 0)
		return -1;
	int f = 0, g = 1;
	while(n--)
	{
		g = f + g;
		f = g - f;
	}
	return f;
}
int main(int argc, char* argv[])
{
	quanpailiePrint(2, 0, 0);
	return 0;
}

