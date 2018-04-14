// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Vector.h"
#include "Stack.h"
#include "List.h"
#include "Queen.h"
#include "Deque.h"
#include "Queue.h"
#include "BinTree.h"
#include <vector>
#include "Bitmap.h"
#include <stdint.h>
#include "BinNode.h"
#include "BinTree.h"

#include "Skiplist.h"
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
	for(int i = 0 ; i < 100 ; i++)
		input[i] = 0;
	std::cin >> input;
	double result = evaluate(input, RPN);
	std::cout << "最后结果为 " << (double)result << std::endl;
	std::cout << "逆波兰表达式为" << s << std::endl;

}

void testQueen()
{
	placeQueens(8);
}

void testQueue()
{
	Queue<int> q;
	q.enqueue(10);
	q.enqueue(9);
	q.enqueue(8);
	q.dequeue();
	std::cout << q.front() << std::endl;
}

void testReadNumber()
{
	char *num = new char[100];
	for(int i = 0 ; i < 100 ; i++)
		num[i] = 0;
	std::cin >> num;
	Stack<double> s;
	readNumber(num, s);
	std::cout << s.top() << std::endl;
}

void testFindAnswer()
{
	for(int i = 0 ; i < 100 ; i++)
	{
		std::cout << "和为" << i << std::endl;
		findAnswer(i);
	}
}

void testDelete()
{
	int *a = new int[4];
	for(int i = 0 ; i < 4 ; i++)
		a[i] = i;
	delete[] a;
	for(int i = 0 ; i < 4 ; i++)
		std::cout << a[i] << std::endl;
	//这就说明delete之后，a中的元素的值会改变
}

void testQueueReverse()
{

	Queue<int> q = Queue<int>();
	for(int i = 0 ; i < 10 ; i++)
		q.enqueue(i);
	print(q);
	q.reverse();
	print(q);

}

void testStackReverse()
{
	Stack<int> s;
	for(int i = 0 ; i < 10 ; i++)
		s.push(i);
	s.print();
	s.reverse();
	s.print();
}


template<typename T>
void testBinTrav()
{
	BinTree<int> tree;
	tree.insertAsRoot(11);

	BinTree<int> subtree5;
	subtree5.insertAsRoot(5);
	subtree5.insertAsLC(subtree5.root(), 3);
	subtree5.insertAsRC(subtree5.root(), 4);

	BinTree<int> subtree7;
	subtree7.insertAsRoot(7);
	//这里注意，attachAsLC的第二个参数是指针的引用，但是你不能直接对比如subtree7取地址，因为你取完地址后得到的值被存在一个临时变量中，而&只会对一个左表达式（有固定地址的）求值
	//所以这里我们需要把指针先付给一个新的变量，然后用这个变量作为参数
	BinTree<int> *s5 = &subtree5;
	subtree7.attachAsLC(subtree7.root(), s5);
	subtree7.insertAsRC(subtree7.root(), 6);

	BinTree<int> subtree2;
	subtree2.insertAsRoot(2);
	subtree2.insertAsRC(subtree2.root(), 1);

	BinTree<int> subtree8;
	subtree8.insertAsRoot(8);
	BinTree<int> *s2 = &subtree2;
	BinTree<int> *s7 = &subtree7;
	subtree8.attachAsLC(subtree8.root(), s2);
	subtree8.attachAsRC(subtree8.root(), s7);

	BinTree<int> subtree9;
	subtree9.insertAsRoot(9);
	BinTree<int> *s8 = &subtree8;
	subtree9.attachAsRC(subtree9.root(), s8);
	
	BinTree<int> *s9 = &subtree9;
	tree.attachAsLC(tree.root(), s9);
	tree.insertAsRC(tree.root(), 10);
	
	tree.travLevel(Print<T>());

}

void testQuadlist()
{
	Skiplist<int, int> qlist;
	QuadlistNode<Entry<int, int>> n;
	for(int i = 0 ; i < 10 ; i ++)
	{
		qlist.put(10 - i, 1);
	}
	qlist.remove(10);

}

int _tmain(int argc, _TCHAR* argv[])
{
	testQuadlist();
	return 0;
}

