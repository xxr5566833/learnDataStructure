#include "stdafx.h"

typedef int Rank;
#define ListNodePosi(T)	ListNode<T>*	//列表节点位置

template <typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	//构造函数

	//针对header和tailer的构造
	ListNode()
	{
		
	}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
	{
		data = e;
		pred = p;
		succ = s;
	}
	//操作接口
	//紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsPred(T const &e);
	//-----------之后插入新节点
	ListNodePosi(T) insertAsSucc(T const &e);
};

template <typename T>
ListNodePosi(T) ListNode<T>:: insertAsPred(T const &e)
{
	ListNodePosi(T) p = new ListNode(e, pred, this);
	pred->succ = p;
	this->pred = p;
	return p;
}

template <typename T>
ListNodePosi(T) ListNode<T>:: insertAsSucc(T const &e)
{
	ListNodePosi(T) p = new ListNode(e, this, succ);
	succ->pred = p;
	this->succ = p;
	return p;
}
