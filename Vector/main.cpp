// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Vector.h"
#include <stdint.h>
unsigned long int next = 1;
int myrand2(void)
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void mysrand(unsigned int seed)
{
	next = seed;
}

int myrand(void)
{
	int result = next;
	next = (65539 * next) % 2147483648;
	return result;
}

uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;
inline static uint64_t msws()
{
	x *= x;
	x += (w += s);
	return (x >> 32) | (x << 32);
}

int binS(int a[], int size, int e)
{
	int i = 0 ;
	int j = size;
	int count = 0;
	while(j - i > 1)
	{
		int mid = (i + j) >> 1;
		if(e < a[mid])	j = mid;
		else			i = mid;
		count++;
	}
	int result = a[i] == e ? i : -1;
	count++;
	std::cout << "��������Ϊ" << count << std::endl;
	return result;
}

int *generateArray(int size)
{
	srand(time(0));
	//һ��ʼ����һֱ������ͬ��������У������ŷ�������Ϊrand���������Լ�д��rand��������
	int *a = new int[size];
	for(int i = 0 ; i < size ; i++)
	{
		a[i] = rand() % 100000;
	}
	return a;
}

template <typename T>
void quickSort(T *a, int lo, int hi)
{
	//��д��һ����ţ���Ȼ����ô������TVT
	if(lo < hi - 1)
	{
		srand(time(0));
		//���ڷ��ִ����ˣ�������lo��hi�綨�ģ����ҵ�����±������ʱ����[0, hi - lo)��Χ�ģ�..
		//ע�ⲻ��ͨ��a = a + lo��ʵ�֣���Ϊlo �� hi ��ֱ�ӵ��±�
		int sel = rand() % (hi - lo) + lo;
		T key = a[sel];
		a[sel] = a[hi - 1];

		int i = lo - 1;
		int j = lo;
		while(j < hi - 1)
		{
			if(a[j] < key)
			{
				i++;
				if(i != j)
				{
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
			j++;
		}
		//�������㷨�Ĳ������Ǳ�ʾ[0, i]һ������С��key����Ҫ��i + 1��λ�÷�key
		a[hi - 1] = a[i + 1];
		a[i + 1] = key;

		quickSort(a, lo, i + 1);
		quickSort(a, i + 2, hi);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*const int a[] = {8, 1, 4, 2, 3, 5, 6, 7};
	Vector<int> myvector = Vector<int>(a, 8);
	myvector.mergeSort(0, myvector.size());
	myvector.print();*/
	/*int size = 5;
	int a[] = {1, 3, 5, 7, 5};
	for(int i = 0 ; i <= size << 1 ; i++)
	{
		std::cout << "����Ϊ" << i << std::endl;
		std::cout << binS(a, size, i) << std::endl;
	}*/

	/*
	for(int j = 1 ; j < 10 ; j++)
	{
		int size = j;
		int *a = new int[size];
		for(int i = 0 ; i < size ; i++)
			a[i] = 2 * i + 1;

		int S = 0;
		int F = 0;
		for(int i = 0 ; i <= size * 2 ; i++)
		{
			fibSearch(a, i, 0, size, (i & 1 ? &S : &F));
		}
		std::cout << "�ܳɹ����ҳ���" << S << std::endl;
		std::cout << "��ʧ�ܲ��ҳ���" << F << std::endl;
		std::cout << "ʧ�ܼ��ɹ� " << F - S << std::endl;
	}*/

	int size = 100;
	int *a = generateArray(size);
	quickSort(a, 0, size);
	std::cout << "����Ϊ" << std::endl;
	for(int i = 0 ; i < size ; i ++)
		std::cout << a[i] << std::endl;
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	for(int i = 0 ; i < size ; i++)
	{
		std::cout << "����" << a[i] << std::endl;
		binSearch(a, a[i] + 5, 0, size, &sum1);
		binSearchB(a, a[i] + 5, 0, size, &sum2);
		fibSearch(a, a[i] + 5, 0, size, &sum3);
		interpolationSearch(a, a[i], 0, size, &sum4);
		
	}
	std::cout << "����A �ܳɹ����ҳ���Ϊ" << sum1 << std::endl;
	std::cout << "����B �ܳɹ����ҳ���Ϊ" << sum2 << std::endl;
	std::cout << "fibo �ܳɹ����ҳ���Ϊ" << sum3 << std::endl;
	std::cout << "��ֵ �ܳɹ����ҳ���Ϊ" << sum4 << std::endl;
	return 0;
}

