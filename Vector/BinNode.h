#pragma once
#include "stdafx.h"

//二叉树节点模板类
#define BinNodePosi(T) BinNode<T>*
//节点高度，与空树高度为-1的约定相统一
#define stature(p)	((p) ? (p)->height : -1)
//节点颜色
typedef enum {RB_RED, RB_BLACK}	RBColor;


/*

*BinNode 状态与性质的判断*

*/
#define IsRoot(x) ((x).parent == NULL)
#define IsLChild(x)	(!IsRoot(x) && (& (x).parent->lc == (x)))
#define IsRChild(x) (!IsRoot(x) && (& (x).parent->rc == (x)))
#define HasParent(x)	((x).parent != NULL)
#define HasLChild(x)	((x).lc != NULL)
#define HasRChild(x)	((x).rc != NULL)
#define HasChild(x)		(HasLChild(x) || HasRChild(x))
#define HasBothChild(x)	(HasLChild(x) && HasRChild(x))
#define IsLeaf(x)	(!HasChild(x))

/*

*与BinNode具有特定关系的节点和指针*

*/

#define sibling(p) (IsLChild(* (p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x)	(sibling((x)->parent))
//来自父亲的引用
#define FromParentTo(x)	(IsRoot(x) ? _root : (IsLChild(x) ? (x)->parent->lc : (x)->parent->rc))



template<typename T>
struct BinNode{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;
	int height;
	//Null Path Length（左氏堆，也可以直接用height代替）
	int npl;
	//颜色，红黑树
	RBColor color;

	//构造函数
	BinNode():
	parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED):
	data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)	{}


	//操作接口
	//统计当前节点后代总数，亦即以其为根的子树的规模
	int size();
	//（这里就很像之前的双向链表的实现了）
	//作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsLC(T const &);
	//作为当前节点的右孩子插入新节点
	BinNodePosi(T) insertAsRC(T const &);
	//取当前节点的直接后继（是指之前写的有序二叉树的直接后继吗？）
	BinNodePosi(T) succ();
	//子树层次遍历
	template<typename VST>	void travLevel(VST &);
	//前序遍历
	template<typename VST>	void travPre(VST &);
	//中序遍历
	template<typename VST>	void travIn(VST &);
	//后序遍历
	template<typename VST>	void travPost(VST &);

	//比较器，判等器
	bool operator<(BinNode const &bn)	{return data < bn.data;}
	bool operator==(BinNode const &bn)	{return data == bn.data;}
	bool operator<=(BinNode const &bn)	{return data <= bn.data;}
	bool operator>(BinNode const &bn)	{return data > bn.data;}
	bool operator>=(BinNode const &bn)	{return data >= bn.data;}
	bool operator!=(BinNode const &bn)	{return data != bn.data;}

};

//插入孩子节点，约定在插入前没有相应孩子节点
template<typename T>
BinNodePosi(T)	BinNode<T>::insertAsLC(T const &e)
{
	//高度？
	return lc = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T)	BinNode<T>::insertAsRC(T const &e)
{
	return rc = new BinNode(e, this);
}

template<typename T>
//操作器



template<typename VST>
void BinNode<T>::travIn(VST &visit)
{
	//二叉树中序遍历算法统一入口
	switch(rand() % 5)
	{
	case 1:travIn_I1(this, visit); break;
	case 2:travIn_I2(this, visit);	break;
	case 3:travIn_I3(this, visit);	break;
	case 4:travIn_I4(this, visit);	break;
	default:	travIn_R(this, visit);	break;
	}
}
//惊了中序遍历竟然有4种迭代。。我记得我之前也就2种？



