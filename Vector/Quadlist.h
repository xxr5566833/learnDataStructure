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
		//С�ڵ���0ֵ����˼����
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

	//��д���ʽӿ�
	//ɾ��p���Ľڵ㣨�Ϸ��������ر�ɾ���ڵ����ֵ
	T remove(QlistNodePosi(T) p);
	QlistNodePosi(T)
		insertAfterAbove(T const &e, QlistNodePosi(T) p = NULL, QlistNodePosi(T) b = NULL);

	//����
	void traverse(void(*) (T &));
	template<typename VST>
	void traverse(VST &);
};

//��ʼ��
template<typename T>
void Quadlist<T>::init()
{
	//ע�⵽�������ֱ��new T���͵�
	//�����Ҿ�����Ҫ��header��tailer����������һЩ�����������������EntryҲ��ʹ��ģ��ģ�����Ϊ�˱�֤header����С��tailer�����
	//�һ���Ҫȷ�����ģ���Ӧ����С������Ѿ�ȷ���ˣ����Ծ�������ֱ���ж��Ƿ�Ϊheader����tailer��
	header = new QuadlistNode<T>;
	tailer = new QuadlistNode<T>;
	header->succ = tailer;
	header->pred = NULL;
	tailer->pred = header;
	tailer->succ = NULL;
	header->above = tailer->above = NULL;
	header->below = tailer->below = NULL;
	//�Ҿ���������Ҫ����header��tailer��entry��
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
//ɾ��Quadlist��λ��p���Ľڵ㣬�������д�ŵĴ���
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