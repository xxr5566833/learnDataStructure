#include "stdafx.h"

int minimumInArray(int a[], int left, int right)
{
	int min = 0x7fffffff;
	for(int i = left ; i <= right ; i++)
	{
		if(a[i] < min)
		{
			min = a[i];
		}
	}
	return min;
}

//һ��ʼһֱ���룬���ͨ���Ƚ��м��Ԫ���������ڵ�Ԫ�صĴ�С��ϵ���ж���СԪ�ص�λ��
//������ʵӦ�ñȽ��м��Ԫ�������˵�Ԫ��֮��Ĵ�С��ϵ�Ŷ԰�
int findMinInRotate(int a[], int size)
{
	if(size < 1)
		return 0x80000001;
	if(size == 1)
		return a[0];
	int left = 0;
	int right = size - 1;
	//Ϊ�˷�ֹ�Է�ֱ�Ӱ����ź�����������������������Ҫ��飬���a[left] < a[right] ��ô��Ҫֱ�����a[left]
	while(left + 1 != right && a[left] >= a[right])
	{
		int mid = (left + right) / 2;
		int leftvalue = a[left];
		int midvalue = a[mid];
		int rightvalue = a[right];
		//����ˣ��Ҷˣ��м��ֵ��һ����ʱ��������Ҫʹ��˳����ң���Ϊ��ʱ�޷�ȷ�������ı���
		if(leftvalue >= midvalue)
		{
			if(leftvalue == midvalue && midvalue == rightvalue)
			{
				return minimumInArray(a, left, right);
			}
			right = mid;
		}
		else{
			left = mid;
		}
	}
	if(a[left] >= a[right])
	{
		return a[right];
	}
	else{
		return a[left];
	}
}

//һ��ʼ����Ƿ��տ��ŵ�partition��д�������ں��ɻ�Ϊʲô���Ų�һ��ָ���ǰ�ߣ�һ��ָ��Ӻ����أ�������partition�Ѿ��޸ģ�
//����ֳ���������������ǿ�����չ�ģ�����һ���ǰ���ż�֣����������������ж����ݣ���ʱ����ͨ������ָ����֧�ֲ�ͬ���ж�����
void oddFirst(int a[], int size)
{
	if(size <= 1)
		return ;
	int i = 0;
	int j = size - 1;
	while(i < j)
	{
		while(i < size && (a[i] & 1))
		{
			i++;
		}
		while(j < size && !(a[j] & 1))
		{
			j--;
		}
		if(i < j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;;
		}

	}
	for(int i = 0 ; i < size ; i ++)
	{
		std::cout << a[i] << std::endl;
	}
}
//��a�����з���Ԫ��һ���ƶ��������ǰ�ˣ��廪���ݽṹ2.7
void notZeroFirst(int a[], int size)
{
	int i = 0;
	int j = size - 1;
	while(i < j)
	{
		while(i < j && a[i] != 0)
		{
			i++;
		}
		while(i < j && a[j] == 0)
		{
			j--;
		}
		if(i != j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		i++;
		j--;
	}
}

//��������˳ʱ��˳���ӡ���֣���Ҫ����ά�����Ƿ�ϸ񣬵��ǲ��ü�飬��ΪC++����Խ�粻����,�������ھ�ֱ������
//˼·��ÿһ�ζ��Ǵ�ӡһ���������Ρ���һ����
void clockWisePrint(int **a, int size)
{
	if(!a)
		return ;
	int left = 0;
	int right = size - 1;
	int top = 0;
	int bottom = size - 1;
	while(left <= right && top <= bottom)
	{
		if(left <= right && top <= bottom)
		{
			for(int i = left ; i <= right ; i++)
			{
				std::cout << a[top][i] << std::endl;
			}
			top++;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = top ; i <= bottom ; i++)
			{
				std::cout << a[i][right] << std::endl;
			}
			right --;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = right ; i >= left ; i--)
			{
				std::cout << a[bottom][i] << std::endl;
			}
			bottom --;
		}
		if(top <= bottom && left <= right)
		{
			for(int i = bottom ; i >= top ; i--)
			{
				std::cout << a[i][left] << std::endl;
			}
			left ++;
		}
	}
}
//��һ���ź���������У���һ������s����������������Ϊs��������
//һ��ʼ�ҵ�˼·�ǣ������� s/2Ȼ�������ֳɴ���s/2��С��s/2��Ȼ����벿��ָ�������ƶ����Ұ벿�������ƶ�������������ʵ��û�б�Ҫ�ģ���û��Ҫ���м俪ʼ��
//ֱ�Ӵ����˿�ʼ�Ҿͺ���

//��һ�����˳���length������֪��������ÿ��Ԫ�ض��ڣ�0�� length-1��֮��������в����Ƿ����ظ���Ԫ�أ�����У���ô���һ������
//�򵥵��뷨�������⿪��һ���ռ�ͳ��
//����ʵ���Ͽ���ͨ����ԭ��������һЩ�޸���ʵ�֣�ÿ������һ�����֣��Ͱ�����Ϊ�±��Ԫ�ؼ���length�������һ��������һ�������ڸ���ӦԪ�ؼ�lengthʱ
//�����Ѿ��ӹ��ˣ���ô˵������������ظ���


//��һ���������ã��廪��ѧ���ݽṹ2.6
//���ϵ��������㷨������Ŀ��ŵ�partitionһ��
void reverseArray(int a[], int size)
{
	//�������򣬽���������
	for(int i = 0 ; i < size / 2 ; i ++)
	{
		int temp = a[i];
		a[i] = a[size - i - 1];
		a[size - i - 1] = temp;
	}
}
//������3n/2�ε�ƽ���Ƚϴ������ҵ����ֵ����Сֵ
//�ǵ��ڴ����һ�ο�����㷨��ʱ�򶼿���������
void findMaxAndMin(int a[], int size)
{
	if(size <= 0)
		return ;
	int min = 0x7fffffff;
	int max = 0x80000000;
	for(int i = 0 ; i < size ; i = i + 2)
	{
		int num1 = a[i];
		if(i + 1 < size)
		{
			//����һ��Ԫ�ش���
			int num2 = a[i + 1];
			int tempmin;
			int tempmax;
			if(num1 < num2)
			{
				tempmin = num1;
				tempmax = num2;
			}
			else{
				tempmax = num1;
				tempmin = num2;
			}
			if(tempmax > max)
			{
				max = tempmax;
			}
			if(tempmin < min)
				min = tempmin;
		}
		else{
			if(num1 > max)
				max = num1;
			if(num1 < min)
				min = num1;
		}
	}
	std::cout << max << std::endl;
	std::cout << min << std::endl;
}

//����˳���Ƚϴ�С���廪���ݽṹ2.13������������
//a < b����-1 a==b ����0 a > b����1
int compare2Array(char *a, char *b)
{
	//����˵�������strcmp������ʵ��
	//����Լ��a��b������\0Ϊ���������ַ��������ڱȽ��������ַ���
	//���a��bΪnull
	if(!a || !b)
		return -2;
	while(*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	if(!(*a))
	{
		//a������
		if(!(*b))
		{
			//bҲ������
			return 0;
		}
		else{
			return -1;
		}
	}
	else{
		if(!(*b))
			return 1;
		else{
			int result;
			*a > *b ? result = 1 : result = -1;
			return result;
		}
	}
}

/*int main(int argc, char* argv[])
{
	char *a = " 2";
	char *b = "  ";
	std::cout << compare2Array(a, b) << std::endl;

	return 0;
}*/