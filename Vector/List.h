#pragma once
#include "ListNode.h"
#include "stdafx.h"

template <typename T>
class List{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) tailer;

protected:
	//列表创建时的初始化
	void init();
	//清除所有节点
	int clear();
	//复制列表中自位置p起的n项，为什么返回void？
	void copyNodes(ListNodePosi(T), int);
	//归并
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
	//对从p开始连续的n个节点归并排序
	void mergeSort(ListNodePosi(T)&, int);
	//对从p开始连续的n个节点选择排序
	void selectionSort(ListNodePosi(T), int);
	//对从p开始连续的n个节点插入排序
	void insertionSort(ListNodePosi(T), int);

public:
	//构造函数
	List() {init();}
	//整体复制列表L
	List(List<T> const& L);
	//复制列表L中自第r项起的n项
	List(List<T> const &L, Rank r, int n);
	//复制列表中自位置p起的n项
	List(ListNodePosi(T) p, int n);
	//数组元素按顺序生成列表
	List(T *a, int size);
	~List();
	//只读访问接口
	Rank size() const {return _size;}
	//判空
	bool empty()const {return _size == 0;}
	//重载，支持循秩访问
	T &operator[](Rank r)const;
	//首节点位置
	ListNodePosi(T) first() const {return header->succ;}
	//末节点位置
	ListNodePosi(T) last() const {return tailer->pred;}
	//判断位置p是否对外合法，语义是非NULL非头非尾
	bool valid(ListNodePosi(T) p)
	{return p && (tailer != p) && header != p;}
	//判断列表是否已经有序
	int disordered()const;
	//无序列表查找
	ListNodePosi(T) find(T const& e)const
	{return find(e, _size, tailer);}
	//无序区间查找，和前面的vector一样，从后往前找
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p)const;
	//有序列表的查找
	ListNodePosi(T) search(T const &e)const
	{return search(e, _size, tailer);}
	//有序区间查找
	ListNodePosi(T) search(T const&e, int n, ListNodePosi(T) p)const;
	//在p及其n-1个后继中选出最大者
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	//整体最大者
	ListNodePosi(T) selectMax()
	{return selectMax(header->succ, _size);}

	//可写访问接口
	//将e当做首节点插入
	ListNodePosi(T) insertAsFirst(T const&e);
	//将e当做末节点插入
	ListNodePosi(T) insertAsLast(T const &e);
	//将e当做p的后继插入
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e);
	//将e当做p的前驱插入
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e);
	//删除合法位置p处的节点，返回被删除节点
	T remove(ListNodePosi(T) p);
	//全列表归并
	void merge(List<T> &L)
	{merge(first(), size, L, L.first(), L._size);}
	//列表区间排序
	void sort(ListNodePosi(T) p, int n);
	//列表整体排序
	void sort()
	{sort(first(), _size);}
	//无序去重
	int deduplicate();
	//有序去重
	int uniquify();
	//前后倒置
	void reverse();

	//遍历
	void traverse(void(*) (T &));
	template <typename VST>
	void traverse(VST &);
};

template <typename T>
void List<T>::init()
{
	//header和tailer都是指针
	header = new ListNode<T>();
	tailer = new ListNode<T>();
	header->succ = tailer;
	header->pred = NULL;
	tailer->pred = header;
	tailer->succ = NULL;
	//不要忘记初始化size
	_size = 0;
}
//秩到位置的转换
//效率不如向量，不管怎样都必须要O(n)的复杂度，不过可以按照r和size/2的关系选择查找的顺序
template <typename T>
T &List<T>::operator[](Rank r)const
{
	ListNodePosi(T) p = first();
	while(r-- && p != tailer)
		p = p->succ;
	//返回其中的值而不是整个地址
	return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p)const
{
	while(n-- && p->pred != header)
	{
		//注意查找范围不包括p自己
		p = p ->pred;
		if(p->data == e)
			return p;
	}
	return NULL;
}
//插入
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e)
{
	//不需要那么麻烦，调用ListNode里的insertas即可
	//注意维护_size
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}

//复制
template <typename T>
//复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	//p合法，且至少有n-1个真后继节点
	init();
	//这里需要深拷贝
	while(n--)
	{
		insertAsLast(p->data);
		p = p ->succ;
	}
}

//构造方法
//p开始复制n个
template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}
//复制整个列表
template<typename T>
List<T>::List(List<T> const &L)
{
	copyNodes(L.first(), L._size);
}
//复制L的第r项开始的n项
template<typename T>
List<T>::List(List<T> const &L, int r, int n)
{
	copyNodes(L[r], n);
}

//数组初始化列表
template<typename T>
List<T>::List(T *a, int size)
{
	init();
	while(--size >= 0)
	{
		insertA(header, a[size]);
	}
}

//删除
template<typename T> T List<T>::remove(ListNodePosi(T) p)
{
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	//不要忘记维护size
	_size--;
	T e = p->data;
	delete p;
	return e;
}

//析构
template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete tailer;
}
//清空链表，仅剩头尾节点
template<typename T>
int List<T>::clear()
{
	int oldsize = _size;
	//反复删除首节点即可
	while(_size)
		remove(header->succ);
	return oldsize;
}

//唯一化
template<typename T>
int List<T>::deduplicate()
{
	if(_size < 2)	return;
	ListNodePosi(T) p = header->succ;
	int oldsize = _size;
	int length = 0;
	while(p != tailer)
	{
		ListNodePosi(T) q = NULL;
		if(q = find(p->data, length, p))
		{
			remove(q);
		}
		else
		{
			length++;
		}
		p = p ->succ;
	}
	return oldsize - _size;
}

//遍历
template<typename T>
void List<T>::traverse(void (*visit)(T&))
{
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p->succ)
		visit(p->data);
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit)
{
	std::cout << "正序" << std::endl;
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p ->succ)
		visit(p->data);
	std::cout << std::endl;
	std::cout << "倒序" << std::endl;
	for(ListNodePosi(T) p = tailer->pred ; p != header ; p = p ->pred)
		visit(p->data);
}

template<typename T>
struct Print{
	virtual void operator()(T &e)
	{
		std::cout << e << " ";
	}
};

template<typename T>
void print(List<T> &L)
{
	L.traverse(Print<T>());
	std::cout << std::endl;
}


//有序列表：
template<typename T>
int List<T>::uniquify()
{
	ListNodePosi(T) p = first(), q = first()->succ;
	int oldsize = _size;
	while(q != tailer)
	{
		if(p->data == q->data)
		{
			ListNodePosi(T) old = q;
			q = q->succ;
			remove(old);
		}
		else{
			p = p->succ;
			q = q->succ;
		}
	}
	return oldsize - _size;
}

//从p的n个真前驱中找到不大于e的最后者
template<typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p)const
{
	if(n <= 0)	return NULL;
	while(0 <= n--)
	{
		if((p = p->pred)->data <= e)	break;
	}
	return p;
}

//排序器
template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	switch(rand() % 3)
	{
	case 1: insertionSort(p, n);	break;
	case 2: selectionSort(p, n);	break;
	default: mergeSort(p, n);	break;
	}
}

//插入排序
template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
	//实际上移动节点位置就可以了
	if(n <= 1)	return ;
	ListNodePosi(T) q = p->succ;
	int length = 0;
	while(n--)
	{
		//这里注意调用insertA，不要调用node的insertAs，因为insertA有对size的维护
		insertA(search(p->data, length++, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

//选择排序
//冒泡排序低效的一个原因就是某个元素本可以经过一次交换就到达它该有的位置，但是冒泡排序却一直交换
//这里的选择排序是先找最大，再找次大...
//选择排序是输入不敏感的，即不论最好还是最坏情况都需要n2时间
template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for(int i = 0 ; i < n ; i++)	tail = tail->succ;
	while(1 < n)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertB(tail, remove(max));
		n--;
		tail = tail->pred;
	}
}
//从起始于位置p的n个元素中选出最大者
//如果这个过程用更高级的数据结构实现，那么只需要logn时间
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for(ListNodePosi(T) cur = p ; 1 < n ; n--)
	{
		//这里要保证稳定性
		if(cur->data >= max->data)
			max = cur;
		cur = cur->succ;
	}
	return max;
}
//归并排序
//归并排序可以理解为两个有序队列之间的排序，因为归并排序的过程中，只需要用到①front()即取出两个队列的头元素进行比较②dequeue()取出较小的头元素③enqueue()加入到结果队列中
template<typename T>
void List<T>::merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;
	while(0 < m)
	{
		if(0 < n && p->data <= q->data)
		{
			//这里如果发现q正好是下一个p，那么就不用合并了
			if(q == (p = p->succ))	break;
			n--;
		}
		else{
			insertB(p, L.remove((q = q->succ)->pred));
			m--;

			
		}
	}
	p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T) &p, int n)
{
	if(n < 2)	return ;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	//这里也只能用循环来获取链表中间节点了
	//如果这里不能保证划分的均衡性，那么整体效率会下降
	for(int i = 0 ; i < m ; i++)	q = q->succ;
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

//reverse倒置接口，之前写过单向链表的倒置，这里是双向链表，原理也一样
//第一种
/*
template<typename T>
void List<T>::reverse()
{
	//遍历整个链表，把链表分成两部分，前一部分已经倒置，后一部分待倒置
	//对于后一部分的头结点a，前一部分的头结点b，让先存下a的原来后继，然后让a的后继指向b，b的前驱指向a，然后继续遍历a之后的节点
	//#define的坏处，只能指示前一个是指针，后一个就不被认为是指针了
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = header->succ;
	while(q)
	{
		ListNodePosi(T) next = q->succ;
		p->pred = q;
		q->succ = p;
		p = q;
		q = next;
	}
	header->succ = NULL;
	tailer->pred = NULL;
	//交换header和tailer
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;

}
*/

/*
template<typename T>
void List<T>::reverse()
{
	//第一遍倒置后继指针，第二遍倒置前驱指针
	//而实际上这两个倒置完全可以在一次遍历中就可以完成
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = header->succ;
	while(q)
	{
		ListNodePosi(T) next = q->succ;
		q->succ = p;
		p = q;
		q = next;
	}
	header->succ = NULL;
	p = tailer;
	q = tailer->pred;
	while(q)
	{
		ListNodePosi(T) pre = q->pred;
		q->pred = p;
		p = q;
		q = pre;
	}
	tailer->pred = NULL;
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;
}
*/
/*
//第三种，交换数据项。。
//但是如果数据项很复杂，那么频繁交换可能导致耗时的构造，析构运算
template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) p = header->succ;
	ListNodePosi(T) q = tailer->pred;
	for(int i = 0 ; i < _size >> 1 ; i++)
	{
		T temp = p->data;
		p->data = q->data;
		q->data = temp;
		p = p->succ;
		q = q->pred;
	}
	//注意啊，交换数据项的话最后不需要交换头尾节点
}
*/
//直接交换每一个节点的前驱和后继指针就可以了啊！
template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) p = header;
	for(p ; p ; p = p->pred)
	{
		ListNodePosi(T) temp = p ->succ;
		p->succ = p->pred;
		p->pred = temp;
	}
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;
}

//Josephus环问题，两种，一种是循环链表实现，另一种是使用递归