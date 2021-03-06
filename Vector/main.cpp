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
#include "prime.h"
#include <stdint.h>
#include "BinNode.h"
#include "BinTree.h"
#include "HashTable.h"
#include "Huff.h"
#include "Skiplist.h"
#include "Graph.h"
#include "GraphMatrix.h"
#include "BTree.h"
#include "Splay.h"
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
	//快排和归并有些互逆的味道，快排是先分再分别排，归并是先分别排然后合并
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

void testHashTable()
{
	HashTable<int, int> t = HashTable<int, int>(10);
	for(int i = 0 ; i < 100 ; i += 11)
	{
		t.put(i, i + 2);
	}
	t.put(230, 10);
	t.remove(11);
	t.get(11);
	
}

template<typename T>
void testBinTrav()
{
	BinTree<int> tree;
	tree.insertAsRoot(1);

	BinTree<int> subtree5;
	subtree5.insertAsRoot(16);
	subtree5.insertAsLC(subtree5.root(), 32);
	subtree5.insertAsRC(subtree5.root(), 32);

	BinTree<int> subtree7;
	subtree7.insertAsRoot(8);
	//这里注意，attachAsLC的第二个参数是指针的引用，但是你不能直接对比如subtree7取地址，因为你取完地址后得到的值被存在一个临时变量中，而&只会对一个左表达式（有固定地址的）求值
	//所以这里我们需要把指针先付给一个新的变量，然后用这个变量作为参数
	BinTree<int> *s5 = &subtree5;
	subtree7.attachAsLC(subtree7.root(), s5);
	subtree7.insertAsRC(subtree7.root(), 16);

	BinTree<int> subtree2;
	subtree2.insertAsRoot(8);
	subtree2.insertAsRC(subtree2.root(), 16);

	BinTree<int> subtree8;
	subtree8.insertAsRoot(4);
	BinTree<int> *s2 = &subtree2;
	BinTree<int> *s7 = &subtree7;
	subtree8.attachAsLC(subtree8.root(), s2);
	subtree8.attachAsRC(subtree8.root(), s7);

	BinTree<int> subtree9;
	subtree9.insertAsRoot(2);
	BinTree<int> *s8 = &subtree8;
	subtree9.attachAsRC(subtree9.root(), s8);
	
	BinTree<int> *s9 = &subtree9;
	tree.attachAsLC(tree.root(), s9);
	tree.insertAsRC(tree.root(), 2);
	
	//bool result = valueNotLessSum(tree.root());
	//setData(tree.root());
	travIn_I3(tree.root(), Print<int>());
	//tree.travIn(Print<int>());

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
/*#include "PFC.h"
void testPFC()
{
	const int size = 20;
	char *old = new char[size];
	for(int i = 0 ; i < size ; i++)
		old[i] = 0;
	std::cin >> old;
	//1.生成编码树
	PFCForest *forest = initForest();
	PFCTree *tree = generateTree(forest);
	//根据编码树生成编码表
	PFCTable *table = generateTable(tree);

	//根据编码表进行编码操作，并不是直接通过编码树编码，因为生成编码表后不用重复搜索了
	Bitmap map = Bitmap();
	int n = encode(table, map, old);
	decode(tree, map, n);
}*/


void testHuffCode()
{
	//统计字符频率
	int *freq = statistics("test.txt");
	//初始化森林
	HuffForest *forest = initForest(freq);
	//生成huffman树
	HuffTree *tree = generateTree(forest);
	//根据huffman树生成编码表
	HuffTable *table = generateTable(tree);
	Bitmap *map = new Bitmap;
	char *s = new char[100];
	for(int i = 0 ;  i< 100 ; i++)
		s[i] = 0;
	std::cin >> s;
	int n = encode(table, map, s);
	char *code = map->bits2string(n);
	decode(tree, map, n);

}
void testBinSB()
{
	int a[7] = {1, 2, 3, 4, 5, 6};
	int b = 0;
	binSearchB(a, 1, 0, 7, &b);
}

void testBfs()
{
	//图在书的161页
	char vlist[] = "ABCDEFGS";
	GraphMatrix<char, int> g;
	for(int i = 0 ; i < 8 ; i++)
	{
		g.insert(vlist[i]);
	}
	//插入边
	g.insert(0, 0, 7, 0);
	g.insert(0, 0, 7, 3);
	g.insert(0, 0, 7, 2);
	g.insert(0, 0, 0, 2);
	g.insert(0, 0, 0, 4);
	g.insert(0, 0, 2, 1);
	g.insert(0, 0, 3, 1);
	g.insert(0, 0, 4, 5);
	g.insert(0, 0, 4, 6);
	g.insert(0, 0, 6, 5);
	g.insert(0, 0, 6, 1);
	g.bfs(7);
	g.pfs(7, BfsPU<char, int>());
}

void testDfs()
{
	//图在书的163页
	char vlist[] = "ABCDEFG";
	GraphMatrix<char, int> g;
	for(int i = 0 ; i < 7 ; i++)
	{
		g.insert(vlist[i]);
	}
	//插入边
	g.insert(0, 0, 0, 1);
	g.insert(0, 0, 0, 5);
	g.insert(0, 0, 0, 2);
	g.insert(0, 0, 1, 2);
	g.insert(0, 0, 3, 0);
	g.insert(0, 0, 3, 4);
	g.insert(0, 0, 4, 5);
	g.insert(0, 0, 5, 6);
	g.insert(0, 0, 6, 0);
	g.insert(0, 0, 6, 2);
	
	g.dfs(0);
	g.pfs(0, DfsPU<char, int>());
}

void testTsort()
{
	//图在书的168页
	char vlist[] = "ABCDEF";
	GraphMatrix<char, int> g;
	for(int i = 0 ; i < 6 ; i++)
	{
		g.insert(vlist[i]);
	}
	//插入边
	g.insert(0, 0, 0, 2);
	g.insert(0, 0, 0, 3);
	g.insert(0, 0, 1, 2);
	g.insert(0, 0, 2, 3);
	g.insert(0, 0, 2, 4);
	g.insert(0, 0, 2, 5);
	g.insert(0, 0, 4, 5);
	
	Stack<char> *s = g.tSort(0);
	while(!s->empty())
		std::cout<< s->pop() << std::endl;
}

void testBTree()
{
	
	BTree<int> *b = new BTree<int>();
	b->insert(53);
	b->insert(36);
	b->insert(77);
	b->insert(89);
	b->insert(19);
	b->insert(41);
	b->insert(51);
	b->insert(75);
	b->insert(79);
	b->insert(84);
	b->insert(97);
	b->remove(53);
	b->remove(36);
	b->remove(77);
	b->remove(89);
	b->remove(19);
	b->remove(41);
	b->remove(51);
	b->remove(75);
	b->remove(79);
	b->remove(84);
	b->remove(97);
}

void testSplay(){
	Splay<int> *s = new Splay<int>();
	//发现如果按照1-8的顺序插入，会发现树会严重左倾
	s->insert(1);
	s->insert(2);
	s->insert(3);
	s->insert(4);
	s->insert(5);
	s->insert(6);
	s->insert(7);
	s->insert(8);
	s->search(1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	testSplay();
	return 0;
}

