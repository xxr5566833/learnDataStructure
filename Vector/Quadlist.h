#pragma once
#include "QuadlistNode.h"
template<typename T>
class Quadlist{
private:
	int _size;
	QlistNodePosi(T) header;
	QlistNodePosi(T) tailer;
protected:
	void init();
	int clear();
public:
	Quadlist()
	{
		init();
	}
	~Quadlist()
	{
		clear();
		delete header;
		delete tailer;
	}
	Rank size() const
	{
		return _size;
	}

	bool empty() const
	{
		//小于等于0值得深思。。
		return _size <= 0;
	}

	QlistNodePosi(T) first() const
	{
		return header->succ;
	}

	QlistNodePosi(T) last() const
	{
		return tailer->pred;
	}

	bool valid(QlistNodePosi(T) p)
	{
		return p && (tailer != p) && (header != p);
	}

	//可写访问接口
	//删除p处的节点（合法），返回被删除节点的数值
	T remove(QlistNodePosi(T) p);
	QlistNodePosi(T)
		insertAfterAbove(T const &e, QlistNodePosi(T) p = NULL, QlistNodePosi(T) b = NULL);

	//遍历
	void traverse(void(*) (T &));
	template<typename VST>
	void traverse(VST &);
};

//初始化
template<typename T>
void Quadlist<T>::init()
{
	//注意到这里可以直接new T类型的
	//这里我觉得需要对header和tailer的数据域做一些特殊操作，但是这里Entry也是使用模板的，所以为了保证header是最小，tailer是最大
	//我还需要确保这个模板对应的最小和最大都已经确定了，所以决定还是直接判断是否为header或者tailer吧
	header = new QuadlistNode<T>;
	tailer = new QuadlistNode<T>;
	header->succ = tailer;
	header->pred = NULL;
	tailer->pred = header;
	tailer->succ = NULL;
	header->above = tailer->above = NULL;
	header->below = tailer->below = NULL;
	//我觉得这里需要设置header和tailer的entry域？
	_size = 0;
	
}
template<typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterAbove(T const &e, QlistNodePosi(T) p = NULL, QlistNodePosi(T) b = NULL)
{
	_size ++;
	if(!p)
		return header->insertAsSuccAbove(e, b);
	return p->insertAsSuccAbove(e, b);
}
//删除Quadlist内位置p处的节点，返回其中存放的词条
template<typename T>
T Quadlist<T>::remove(QlistNodePosi(T) p)
{
	
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	_size --;
	T e = p->entry;
	delete p;
	return e;
}

template<typename T>
int Quadlist<T>::clear()
{
	int oldSize = _size;
	while(0 < _size)
	{
		remove(header->succ);
	}
	return oldSize;
}