#pragma once
#include "BST.h"

//理想平衡条件
#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-1 <= BalFac(x)) && (BalFac(x) <= 1))
//在左，右孩子中取更高者
//在AVL平衡调整前，借此确定重构方案
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
	//将关键码e插入AVL树中
	BinNodePosi(T) &x = search(e);
	if(x)
		return x;
	BinNodePosi(T) newx = x = new BinNode<T>(e, _hot);
	_size ++;
	//此时，x的父亲_hot如果增高，则其祖父可能失衡
	for(BinNodePosi(T) g = _hot ; g ; g = g->parent)
	{
		//从x的父亲出发向上，逐层检查各代祖先g，x的父亲应该不会失衡吧？要更新高度！
		if(!AvlBalanced(*g)){
			//一旦发现g失衡，那么采用“3+4”算法使之复平衡，并将子树重新接入原树
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else{
			//这也是为什么要从父亲节点开始遍历的原因
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
		//注意与插入时的不同，即使没有失衡，高度也可能降低
		updateHeight(g);
	}
	return true;
}

//在实际的旋转操作中，只需要对一个局部结构，包括3个节点和4棵子树进行操作
//可以用于AVL和RedBlack的局部平衡调整
//其实就是根据已经确定好的abc和T0T1T2T3来创建这样一棵恢复平衡的二叉树，关键还是如何确定abc和T
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
	//v为非空孙子辈节点
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