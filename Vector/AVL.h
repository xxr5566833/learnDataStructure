#pragma once
#include "BST.h"

//����ƽ������
#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-1 <= BalFac(x)) && (BalFac(x) <= 1))
//�����Һ�����ȡ������
//��AVLƽ�����ǰ�����ȷ���ع�����
#define tallerChild(x) (\
	stature((x)->lc) > stature((x)->rc) ? (x)->lc : (\
	stature((x)->lc) < stature((x)->lc) ? (x)->rc : (\
	IsChild(*(x)) ? (x)->lc : (x)->rc	\
	)\
	)\
)

template<typename T>
class AVL:public BST<T>{
public:
	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e)
{
	//���ؼ���e����AVL����
	BinNodePosi(T) &x = search(e);
	if(x)
		return x;
	BinNodePosi(T) newx = x = new BinNode<T>(e, _hot);
	_size ++;
	//��ʱ��x�ĸ���_hot������ߣ������游����ʧ��
	for(BinNodePosi(T) g = _hot ; g ; g = g->parent)
	{
		//��x�ĸ��׳������ϣ�������������g��x�ĸ���Ӧ�ò���ʧ��ɣ�Ҫ���¸߶ȣ�
		if(!AvlBalanced(*g)){
			//һ������gʧ�⣬��ô���á�3+4���㷨ʹ֮��ƽ�⣬�����������½���ԭ��
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else{
			//��Ҳ��ΪʲôҪ�Ӹ��׽ڵ㿪ʼ������ԭ��
			updateHeight(g);
		}
	}
	return newx;
}
template<typename T>
bool AVL<T>::remove(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if(!x)
		return false;
	removeAt(x, _hot);
	_size --;
	for(BinNodePosi(T) g = _hot ; g ; g = g->parent)
	{
		if(!AvlBalanced(*g))
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		//ע�������ʱ�Ĳ�ͬ����ʹû��ʧ�⣬�߶�Ҳ���ܽ���
		updateHeight(g);
	}
	return true;
}

//��ʵ�ʵ���ת�����У�ֻ��Ҫ��һ���ֲ��ṹ������3���ڵ��4���������в���
//��������AVL��RedBlack�ľֲ�ƽ�����
//��ʵ���Ǹ����Ѿ�ȷ���õ�abc��T0T1T2T3����������һ�ûָ�ƽ��Ķ��������ؼ��������ȷ��abc��T
template<typename T>
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
	){
	a->lc = T0;
	if(T0)	T0->parent = a;
	a->rc = T1;
	if(T1)	T1->parent = a;
	updateHeight(a);
	c->lc = T2;
	if(T2)	T2->parent = c;
	c->rc = T3;
	if(T3)	T3->parent = c;
	updateHeight(c);
	b->lc = a;
	a->parent = b;
	b->rc = c;
	c->parent = b;
	updateHeight(b);
	return b;
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
	//vΪ�ǿ����ӱ��ڵ�
	BinNodePosi(T) p = v->parent;
	BinNodePosi(T) g = p->parent;
	if(IsLChild(*p))
		if(IsLChild(*v)){
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	else{
		if(IsLChild(*v))
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
		else{
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
	}
}