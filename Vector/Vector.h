#pragma once
#include "fib.h"
typedef int Rank;	//秩
#define DEFAULT_CAPACITY 3

template<typename T>
static Rank fibSearch(T *a, T const &e, Rank hi, Rank lo);
template<typename T>
static Rank exponentialSearch(T *a, T const &e, Rank lo, Rank hi);
template <typename T>
static int interpolationSearch(T *a, T const &e, int lo, int hi, int *sum);
template<typename T>
static Rank binSearchB(T *A, T const &e, Rank lo, Rank hi, int *sum );
template<typename T>

class Vector
{
	//为了方便调试，这里先public
public:
	Rank _size;
	int _capacity;
	T *_elem;
	//构造函数经常用到
	void copyFrom(T const* A, Rank lo, Rank hi);		//复制数组区间[lo,hi)
	void expand();										//空间不足时扩容
	void shrink();		//装填因子过小时压缩
	//接下来是一些排序算法以及它们的辅助方法
	Rank bubble(Rank lo, Rank hi);		//扫描交换
	void bubbleSort(Rank lo, Rank hi);	//冒泡排序
	Rank max(Rank lo, Rank hi);			//选取最大元素
	void selectionSort(Rank lo, Rank hi);	//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);	//归并算法
	void mergeSort(Rank lo, Rank hi);		//归并排序算法
	Rank partition(Rank lo, Rank hi);		//轴点构造算法
	void quickSort(Rank lo, Rank hi);		//快速排序算法
	void heapSort(Rank lo, Rank hi);		//堆排序
public:

	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为c，规模为s，所有元素初始为v
	{
		//约定s <= c，内部还是数组
		_capacity = c;
		_elem = new T[_capacity];
		/*
		for(_size = 0 ; _size < s ; _size++)
		{
			_elem[_size] = v;
		}
		*/
		for(_size = 0 ; _size < s ; _elem[_size++] = v);
	}
	Vector(T const *A, Rank lo, Rank hi)
	{
		//问题：还没构造好就用这个对象的方法？？
		copyFrom(A, lo, hi);
	}
	Vector(T const *A, Rank n)
	{
		copyFrom(A, 0, n);
	}
	Vector(Vector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}
	Vector(Vector<T> const &V)
	{
		copyFrom(V._elem, 0, V._size);
	}
	
	//析构函数
	~Vector()
	{
		//谁申请谁释放原则，如果元素不是简单类型，那么是否delete由调用者决定，这里仅仅释放_elem
		delete[] _elem;
	}

	//只读访问接口
	Rank size() const { return _size;}
	bool empty() const {return !_size;}
	int disordered() const;//判断向量是否已经排序
	Rank find(T const& e)const {return find(e, 0, _size);}	//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi)const;			//无序向量区间查找
	Rank search(T const& e)const			//有序向量整体查找
	{return (_size <= 0 ? -1 : search(e, 0, _size));}
	Rank search(T const &e, Rank lo, Rank hi)const;		//有序向量区间查找
	
	//可写访问接口
	T& operator[](Rank r)const;		//重载下标操作符
	Vector<T> & operator=(Vector<T> const &);	//重载赋值操作符，以便直接克隆向量
	T remove(Rank r);		//删除秩为r的元素
	int remove(Rank lo, Rank hi);		//删除秩在区间[lo, hi)之内的元素
	Rank insert(Rank r, T const &e);	//插入元素
	Rank insert(T const &e){return insert(_size, e);}	//默认作为末尾元素插入
	void sort(Rank lo, Rank hi);		//对[lo, hi)排序
	void sort() {sort(0, _size);}		//整体排序
	void unsort(Rank lo, Rank hi);		//对[lo, hi)置乱
	void unsort()	{unsort(0, _size);}	//整体置乱
	int deduplicate();					//无序去重
	int uniquify();						//有序去重

	//遍历
	void traverse(void(*) (T&));		//遍历，使用函数指针，只读或局部性修改
	template <typename VST> void traverse(VST &);	//遍历（使用函数对象，可全局性修改）

	void print();

};

template<typename T>

void Vector<T>::print()
{
	for(int i = 0 ; i < this->size(); std::cout << _elem[i++] << " ");
	std::cout << std::endl;
}

//这里以数组[lo, hi)为蓝本
template<typename T>


void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
	//初始一般capacity是 hi - lo的两倍
	//copyFrom会创建新的_elem
	//课后2-2
	//这里要保证_elem与A的独立性，如果不能保证，那么可能需要注意copy的顺序
	//这里一开始想错了，A的每一个元素是有效的，_elem是待赋值数组
	//如果_elem有某一后缀与A前缀重叠，那么此时应该从A的0位置元素开始copy，如果从最后开始复制，那么A的前缀会被覆盖
	//如果_elem有某一前缀与A后缀重叠，那么此时应该从A的最后往前复制，如果从开始往最后复制，那么A的后缀会被覆盖
	//综上，从可能被覆盖的地方开始复制
	_elem = new T[_capacity = 2 * (hi - lo)];
	//真的发现人的思维是固定的，过了很长时间又写这个方法还是用for循环复制数组
	for(_size = 0 ; _size < hi - lo ; _elem[_size++] = A[lo + _size]);
}

template<typename T>

Vector<T> & Vector<T>::operator=(Vector<T> const &V)
{
	if(_elem)	delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	//返回当前对象的引用，以便链式赋值
	return *this;
}

template<typename T>
//insert一开始都要调用这个算法
//2-1 分摊更具有参考价值，分摊和平均没有蕴含关系
//O(1)分摊时间

void Vector<T>::expand()
{
	//没满不扩，满了彩扩
	if(_size < _capacity) return ;
	//问题：不低于最小容量？_capacity低于最小容量不可能发生啊？shrink里也不会发生啊
	if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;	//不低于最小容量
	T *oldElem = _elem;
	//这里注意乘2用移位！！！！！！！
	_elem = new T[_capacity <<= 1];	//容量加倍
	for(int i = 0 ; i < _size ; i++)
		//T为基本类型，或者已经重载=
		_elem[i] = oldElem[i];
	delete[] oldElem;
	
	//_size 没变
}

//装填因子过小时压缩向量所占空间
template<typename T>
void Vector<T>::shrink()
{
	//不至于收缩到default的容量以下
	if(_capacity < DEFAULT_CAPACITY << 1)	return ;
	//注意左移二位是乘四
	if(_size << 2 > _capacity)	return;
	//如果当前规模是容量的四分之一以上，即当前填装因子大于1/4，那么也不收缩
	T *oldElem = _elem;
	_elem = new T[_capacity >>= 1];//容量减半
	for(int i = 0 ; i < _size ; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>

//get set都被取代了，返回的是引用，所以get，set都会被取代
T& Vector<T>::operator[](Rank k)const
{
	//assert: 0<=r<_size
	return _elem[k];
}


template<typename T>
//各元素等概率出现于每一个位置
void permute(Vector<T> &V)
{
	for(int i = V.size() ; i > 0 ; i--)
	{
		//自后向前
		swap(V[i- 1], V[rand() % i]);
	}
}
//区间置乱
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T *V = _elem + lo;
	for(Rank i = hi - lo ; i > 0 ; i--)
		swap(V[i - 1], V[rand() % i]);
}

//比较和比对
template<typename T> static bool lt(T *a, T *b)	{return lt(*a, *b);}
template<typename T> static bool lt(T &a, T &b)	{return a < b;}
template<typename T> static bool equal(T *a, T *b)	{return equal(*a, *b);}
template<typename T> static bool equal(T &a, T &b)	{return a == b;}

template<typename T>


//统一约定返回其中秩最大者
//查找与e相等的元素，约定[lo, hi)
//规模相同，内部组成不同的输入，渐进运行时间却有本质区别，这类算法也叫输入敏感的算法
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	while((lo < hi--) && (e != _elem[hi]));
	return hi;
	//若hi小于lo，那么查找失败，否则，hi即为要找的元素的秩
	//从后往前查找，所以会返回相等元素的在这个区间内的秩最大的
}
//把e插入到秩为r的位置，运行时间线性正比于后缀的长度，若插入位置等概率分布，平均运行时间为O(n)
template<typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
	expand();
	for(int i = _size ; i > r ; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size ++;
	return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if(lo == hi)	return 0;
	while(hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
//删除无序向量中重复元素（高效版）
int Vector<T>::deduplicate()
{
	int oldSize = _size;
	Rank i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0) ?
		i++ : remove(i);
	return oldSize - _size;
}

template<typename T>
//利用函数指针
void Vector<T>::traverse(void (*visit)(T&))
{
	for(int i = 0 ; i < _size ; i++)
		visit(_elem[i]);
}
template<typename T>
template<typename VST>
//函数对象机制的遍历
void Vector<T>::traverse(VST &visit)
{
	for(int i = 0 ; i < _size ; i++)
		visit(_elem[i]);
}

template<typename T>
struct Increase
{
	virtual void operator()(T &e)
	{
		e++;
	}
};
template<typename T>
void increase(Vector<T> &V)
{
	V.traverse(Increase<T>());
}

template<typename T>
struct Double
{
	virtual void operator()(T &e)
	{
		e *= 2;
	}
};

template<typename T>
void doub(Vector<T> &T)
{
	V.traverse(Double<T>());
}

/*
在这里总结一下无序向量各个操作的特点
Rank find(e, lo, hi)	从后向前扫描	返回相同元素中秩最大的，找不到返回lo - 1	平均O(n)，输入敏感，时间取决于元素在向量中后继的个数
Rank insert(e, r)		从后向前移动	返回r，一开始会检测是否需要expand()			平均O(n)，输入敏感，时间取决于 size - r，即也是后继的个数
int remove(lo, hi)		从前往后移动	返回删除的元素个数hi - lo，最后会shrink		平均O(n)，输入敏感，时间取决于被删除区间的后继个数
T remove(r)				从前往后移动	返回被删除元素的值							平均O(n)，输入敏感，时间取决于被删除元素的后继个数即size - r
void unsort(lo, hi)		从后往前置乱	rand()如果理想，那么可以等概率随机置乱		O(n)，输入就不敏感
重载[]									返回引用，取代get put						O(1)

可以看到很多算法都是从后往前的，无论是find还是unsort，都倾向于从最后一个元素开始
*/


//通过返回相邻逆序对的个数来判断是否有序
template<typename T>
int Vector<T>:: disordered()const	
{
	int n = 0;
	for(int i = 1 ; i < _size ; i++)
	{
		if(_elem[i - 1] > _elem[i])	n++;
	}
	return n;
}

//有序向量重复元素剔除算法
	//书上的思路，就是在原数组上删除即可，把数组分成三部分，
	//前半部分是已经确定没有相同元素的
	//中间部分是一些相同的可以丢弃的元素
	//后半部分是待查看的元素
	//和partition有几分相似
//或者可以把相同的元素看做一个组，那么每一次都只是取每组的第一个元素
template<typename T>
int Vector<T>::uniquify()
{
	int i = 0 , j = 0;
	while(j++ < _size)
	{
		if(_elem[j] != _elem[i])
			_elem[i++] = _elem[j];
	}
	_size = ++i;
	shrink();
	return j - i;
}
//查找，简单的二分查找就有这么多原理在里面
template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi)const
{
	return binSearch(_elem, e, lo, hi) ;
}
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi)
{
	while(lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi + 1;
	}
	return lo - 1;
}

//有序向量的二分查找：左1右2命中2
//最原始版本，系数1.50，还没有满足约定
	//[lo, hi)
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	int count = 0;
	while(lo < hi)
	{
		Rank mid = (lo + hi) >> 1;
		if(e < A[mid])	{
			count++;
			hi = mid;
		}
		else if(A[mid] < e){
			count += 2;
			lo = mid + 1;
		}
		else{
			count += 2;
			*sum = *sum + count;
			std::cout << "二分查找A的成功查找长度为   " << count << std::endl;
			return mid;
		}
	}
	*sum = *sum + count;
	std::cout << "二分查找A的失败查找长度为" << count << std::endl;
	return -1;
}

//接下来，视频讲了一个斐波那契查找算法
//假设数组长度n = fib(k) - 1
//与二分查找类似的是，也是减而治之，只不过切分点是 fib(k - 1) - 1
//是因为左查找与右查找的操作量不同，故切分时左多右少，保证落在左边的概率更大

template<typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	Fib fib(hi - lo);
	int count = 0;
	while(lo < hi)
	{
		while(hi - lo < fib.get())	fib.prev();
		Rank mi = lo + fib.get() - 1;
		if(e < A[mi]) {
			count++;
			hi = mi;
		}
		else if (A[mi] < e){
			count += 2;
			lo = mi + 1;
		}
		else{
			count += 2;
			*sum = *sum + count;
			std::cout << "fibonacci查找的成功查找长度为   " << count << std::endl;
			return mi;
		}
	}
	*sum = *sum + count;
	std::cout << "fibonacci的失败查找长度为" << count << std::endl;
	return -1;
}

//二分查找：版本B，左右都只做一次元素比较即可
template<typename T>

static Rank binSearchB(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	int count = 0;
	while(lo < hi - 1)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi;
		count+=1;
	}
	count++;
	*sum = *sum + count;
	if(e == A[lo])
	{
		std::cout << "二分查找B的成功查找长度为   " << count << std::endl;
		return lo;
	}
	else{
		std::cout << "二分查找B的失败查找长度为" << count << std::endl;
		return -1;
	}
}

/*
//二分查找最终版本，符合语义
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	while(lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi + 1;
		count ++;
	}
	return lo - 1;
}*/
/*指数查找：
在一个非降的正整数向量A[0,n)中，对于任意给定的元素x <= A[n - 1]，从该向量中找出一个元素A[k]，使得 A[k] <= x <= A[min(n - 1, k平方)]
有多个仅需返回任意一个，查找时间不超过O(loglogk)
查找失败返回 lo - 1 或 hi
*/
template<typename T>
static Rank exponentialSearch(T *a, T const &e, Rank lo, Rank hi)
{
	//assert:e <= a[hi - 1]
	a = a + lo;
	if(e < a[0])	return lo - 1;
	for(int i = 0 ; i * i < hi - lo ; i++)
	{
		if(e <= a[i * i] && e >= a[i])
		{
			return lo + i;
		}
	}
	return hi;
}

/*马鞍查找，这里一共讲了二分，fibo，expo，马鞍查找等算法*/

/*最后还有一个  插值查找！ 线性逼近，其实也是找切分点*/
template <typename T>
static int interpolationSearch(T *a, T const &e, int lo, int hi, int *sum)
{
	int count = 0;
	while(lo < hi - 1)
	{
		//与二分查找不同之处在于，这里在计算切分点时，这个切分点不一定命中[lo, hi)范围，而一旦这个切分点没有命中，那么只能说明e不在[lo,hi)范围内
		int y = (e - a[lo]) * (hi - lo - 1) /  (a[hi - 1] - a[lo]) + lo;
		if(y < lo || y >= hi)
			return -1;
		if(a[y] < e)
		{
			count ++;
			lo = y + 1;
		}
		else if(e < a[y]){
			count += 2;
			hi = y;
		}
		else
			{
				count += 2;
				std::cout << "插值查找的成功查找长度为   " << count << std::endl;
				*sum = *sum + count;
				return y;
		}
	}
	count += 1;
	if(a[lo] == e)
	{
		std::cout << "插值查找的成功查找长度为2   " << count << std::endl;
		*sum = *sum + count;
		return lo;
	}
	else{
		std::cout << "插值查找的失败查找长度为" << count << std::endl;
		*sum = *sum + count;
		return -1;
	}
}

//专门用于排序算法的实现

//冒泡排序
//我最开始理解的冒泡排序，就是一遍又一遍的扫描，直到没有逆序对就结束
//在听了老师的讲解后，理解了：从k = n开始，每一趟从k往前扫描
//扫描结束后，都可以保证第k + 1大元素在秩为k的位置上，故整个排序过程就变成了n - 1趟的扫描

//但是实际上有时不一定必须是n - 1趟，可能会提前结束，或者说可以“空过”某一段已经排好序的扫描，那么下一趟完全可以把上次扫描交换了的最大下标作为下一次扫描的hi界
//根据课后题，我们可以方向交替的执行扫描交换，动态记录最左和最右的逆序元素

//时间关系，我先写好最终版的
template<typename T>




void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while(lo < (hi = bubble(lo, hi)))
	{
		this->print();
	}
}

template<typename T>
Rank Vector<T>::bubble(Rank lo, Rank hi)
{
	Rank last = lo;
	while(lo < hi - 1)
	{
		if(_elem[lo + 1] < _elem[lo])
		{
			T temp = _elem[lo];
			_elem[lo] = _elem[lo + 1];
			_elem[lo + 1] = temp;
			last = lo + 1;
		}
		lo++;
	}
	return last;
}

//二路归并排序的实现
template<typename T>

void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if(lo < hi - 1)
	{
		int mi = (lo + hi) >> 1;
		mergeSort(lo, mi);
		mergeSort(mi, hi);
		merge(lo, mi, hi);
	}
}


template<typename T>


void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *B = new T[mi - lo];
	T *C = _elem + mi;
	Rank left = 0, right = 0;
	Rank leftb = mi - lo, rightb = hi - mi;
	for(Rank i = 0 ; i < leftb ; i ++)
		B[i] = _elem[i + lo];
	Rank p = lo;
	while(left < leftb)
	{
		if(right < rightb)
		{
			//注意稳定性
			if(B[left] <= C[right])
				_elem[p++] = B[left++];
			else
				_elem[p++] = C[right++];
		}
		else 
		{
			_elem[p++] = B[left++];
		}
	}
}
/*
//学会用指针加法
//只需要B用辅助空间，然后可以把某个数组为空，另一个不为空这个特殊情况也写在for循环里
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *A = _elem + lo;
	T *B = new T[mi - lo];
	for(int i = 0 ; i < mi - lo ; B[i++] = A[i]);
	T *C = _elem + mi;
	int lb = mi - lo;
	int lc = hi - mi;
	for(int i = 0, j = 0, k = 0 ; (j < lb) || (k < lc);)
	{
		if(j < lb && (lc <= k || B[j] <= C[k]))	A[i++] = B[j++];
		if(k < lc && (lb <= j || C[k] < B[j]))	A[i++] = C[k++];
	}
	delete[] B;
}
*/

//选择排序
template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	for(int i = hi - 1 ; i > lo ; i--)
	{
		int mx;
		//这里max一定要返回值最大的最末尾的元素
		if((mx = max(lo, hi)) != i)
		{
			T temp = _elem[i];
			_elem[i] = _elem[mx];
			_elem[mx] = temp;
		}
	}
}

template<typename T>
int Vector<T>::max(Rank lo, Rank hi)
{
	int mx = lo;
	for(int i = lo + 1 ; i < hi ; i++)
	{
		//这里我顺序扫描所以为了保证稳定性这里用了>=
		if(_elem[i] >= _elem[mx])
			mx = i;
	}
	return mx;
}