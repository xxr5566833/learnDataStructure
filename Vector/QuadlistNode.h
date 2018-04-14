#pragma once
#include "Entry.h"
#define QlistNodePosi(T) QuadlistNode<T>*

template<typename T>
struct QuadlistNode
{

	T entry;
	QlistNodePosi(T) pred;
	QlistNodePosi(T) succ;
	QlistNodePosi(T) above;
	QlistNodePosi(T) below;
	QuadlistNode
		(T e = T(), QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL,
		QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL)
		:entry(e), pred(p), succ(s), above(a), below(b) {}
	QlistNodePosi(T) insertAsSuccAbove(T const &e, QlistNodePosi(T) b = NULL);

};

template<typename T>
QlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const &e, QlistNodePosi(T) b = NULL)
{
	QlistNodePosi(T) x = new QuadlistNode<T>(e, this, succ, NULL, b);
	succ->pred = x;
	succ = x;
	//Ĭ��b��above����ΪNULL������������insertAfterAbove�ĵ��������b��above����NULL����Ϊb���Ǳ�ʾ��ʱ�Ǹ���������
	if(b)	b->above = x;
	return x;
}