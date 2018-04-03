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
	header = new ListNode();
	tailer = new ListNode();
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
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p ->succ)
		visit(p->data);
}