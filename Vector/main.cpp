// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Vector.h"
#include "Stack.h"
#include "List.h"
#include "Queen.h"
#include <vector>
#include "Bitmap.h"
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
	std::cout << "搜索长度为" << count << std::endl;
	return result;
}

int *generateArray(int size)
{
	srand(time(0));
	//一开始发现一直产生相同的随机数列，后来才发现是因为rand调用了我自己写的rand函数。。
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
	//重写了一遍快排，竟然有这么多问题TVT
	if(lo < hi - 1)
	{
		srand(time(0));
		//终于发现错误了，这里是lo和hi界定的，但我的随机下标产生的时候是[0, hi - lo)范围的，..
		//注意不能通过a = a + lo来实现，因为lo 和 hi 是直接的下标
		int sel = rand() % (hi - lo) + lo;
		T key = a[sel];
		a[sel] = a[hi - 1];
		//注意范围是lo和hi ，所以i和j的初始化值由lo确定
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
		//而这里算法的不变性是表示[0, i]一定满足小于key，故要拿i + 1的位置放key
		a[hi - 1] = a[i + 1];
		a[i + 1] = key;

		quickSort(a, lo, i + 1);
		quickSort(a, i + 2, hi);
	}
}

void testSearch()
{
	int size = 100;
	int *a = generateArray(size);
	quickSort(a, 0, size);
	std::cout << "序列为" << std::endl;
	for(int i = 0 ; i < size ; i ++)
		std::cout << a[i] << std::endl;
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	for(int i = 0 ; i < size ; i++)
	{
		std::cout << "查找" << a[i] << std::endl;
		binSearch(a, a[i] + 5, 0, size, &sum1);
		binSearchB(a, a[i] + 5, 0, size, &sum2);
		fibSearch(a, a[i] + 5, 0, size, &sum3);
		interpolationSearch(a, a[i], 0, size, &sum4);
		
	}
	std::cout << "二分A 总成功查找长度为" << sum1 << std::endl;
	std::cout << "二分B 总成功查找长度为" << sum2 << std::endl;
	std::cout << "fibo 总成功查找长度为" << sum3 << std::endl;
	std::cout << "插值 总成功查找长度为" << sum4 << std::endl;
}

void testSearchLength()
{
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
		std::cout << "总成功查找长度" << S << std::endl;
		std::cout << "总失败查找长度" << F << std::endl;
		std::cout << "失败减成功 " << F - S << std::endl;
	}
	
}

void testBubbleSort()
{
	srand(time(0));
	int size = rand() % 20;

	int *a = generateArray(size);
	Vector<int> myv = Vector<int>(a, size);
	myv.bubbleSort(0, myv.size());
}

void testMerge()
{
	srand(time(0));
	int size = rand() % 20;

	int *a = generateArray(size);
	Vector<int> myv = Vector<int>(a, size);
	myv.mergeSort(0, myv.size());
	myv.print();

}

void testBitmap()
{
	Bitmap m = Bitmap(8);
	m.set(0);
	m.set(5);
	m.clear(5);
	m.set(5);
	std::cout << m.test(5) << std::endl;
	
}

void testEratosthenes()
{
	for(int i = 2 ; i < 100 ; i ++)
		Eratosthenes(i);
}


void testList()
{
	int a[] = {6, 5};
	List<int> l = List<int>(a, 2);
	l.reverse();
	print(l);
}

void testConvert()
{
	Vector<char> l;
	Stack<char> s;
	convert(s, 16, 8);
	while(!s.empty())
	{
		std::cout << s.pop() << " ";
	}
}

void testStackPermute()
{
	int size = 4;
	int B[] = {1, 4, 2, 3};
	bool result  = checkStackPermu(B, 4);
	std::cout << result << std::endl;
}

void testEvaluate()
{
	char *RPN = new char[100];
	//保存下开始地址
	char *s = RPN;
	char *input = new char[100];
	std::cin >> input;
	double result = evaluate(input, RPN);
	std::cout << "最后结果为 " << (double)result << std::endl;
	std::cout << "逆波兰表达式为" << s << std::endl;

}

void testQueen()
{
	placeQueens(6);
}

int _tmain(int argc, _TCHAR* argv[])
{
	testQueen();
	return 0;
}

