#pragma once
#include "stdafx.h"

typedef int Rank;
#define ListNodePosi(T)	ListNode<T>*	//�б�ڵ�λ��

template <typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	//���캯��

	//���header��tailer�Ĺ���
	ListNode()
	{
		
	}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
	{
		data = e;
		pred = p;
		succ = s;
	}
	//�����ӿ�
	//������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsPred(T const &e);
	//-----------֮������½ڵ�
	ListNodePosi(T) insertAsSucc(T const &e);
};
//һ��ʼһֱ��һ��C2953����˵����ģ���ظ����壬�����Ҿ�����һ��listnode����
//���˰���ԭ�������뵽�����ͷ�ļ����ܱ��ظ������ˣ���Ȼ������#pragma once�ͺ���
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
