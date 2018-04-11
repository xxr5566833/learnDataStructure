#pragma once
#include "BinNode.h"
#include "stdafx.h"
#include "Stack.h"
template<typename T>
class BinTree{
protected:
	int _size;
	BinNodePosi(T) _root;
	//更新节点x的高度
	virtual int updateHeight(BinNodePosi(T) x);
	//更新节点x及其祖先的高度
	void updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree() : _size(0), _root(NULL)	{}
	~BinTree() {
		if(0 < _size)
			remove(_root);
	}
	int size()const {
		return _size;
	}
	bool empty()const
	{
		return !root;
	}

	BinNodePosi(T) root()const
	{
		return _root;
	}

	//插入根节点
	BinNodePosi(T) insertAsRoot(T const &e);

	//e作为x的左孩子插入
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);

	//e作为x的右孩子插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);

	//T作为x左子树接入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&T);

	//T作为x的右子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&T);

	//删除以位置x处节点为根的子树，返回该子树原先的规模
	int remove(BinNodePosi(T) x);

	//将子树x从当前树中摘除，并将其转换为一棵独立子树
	BinTree<T> *secede(BinNodePosi(T) x);

	template<typename VST>
	void travLevel(VST &visit)
	{
		if(_root)
			_root->travLevel(visit);
	}

	template<typename VST>
	void travPre(VST &visit)
	{
		if(_root)
			_root->travPre(visit);
	}

	template<typename VST>
	void travIn(VST &visit)
	{
		if(_root)
			_root->travIn(visit);
	}

	template<typename VST>
	void travPost(VST &visit)
	{
		if(_root)
			_root->travPost(visit);
	}

	//这里比较和比对有什么意义呢?
	bool operator< (BinTree<T> const &t)
	{
		return _root && t._root && _root < t._root;
	}

	bool operator== (BinTree<T> const &t)
	{
		return _root && t._root && (_root == t._root);
	}
};

//实现
//更新高度
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

//节点插入（约定都是在原来位置上没有节点时）
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	_root = new BinNode(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	_size ++;
	x->insertAsLC(e);
	//注意这里来维护高度
	updateHeightAbove(x);
	return x->lc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

//子树接入，
//任意一个二叉树均可以作为另一个二叉树中指定节点的左子树或者是右子树
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&S)
{
	//将S当做节点x的左子树接入，S本身置空
	//注意这里还要设置S的root节点的parent，当然在设置之前需要先判断一下是不是NULL
	if(x->lc = S->_root)	x->lc->parent = x;
	
	_size += S->size();
	updateHeightAbove(x);
	//height的性质，每一个节点的height只与它的后代节点有关，而与它的父亲节点无关
	//但是深度就不一样了
	
	//释放原树的步骤：
	S->_root = NULL;
	S->size = 0;
	//release()怎么实现？
	release(S);
	S = NULL;
	//返回接入位置
	return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S)
{
	if(x->rc == S->_root)	x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	release(S);
	S = NULL;
	return x;
}

//子树删除
template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	//切断来自父节点的指针，原来父节点的x的位置现在就变成了NULL
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	//这就是删除要返回被删除的节点数量的原因
	_size -= n;
	return n;
}

template<typename T>
static int removeAt(BinNodePosi(T) x)
{
	if(!x)	return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	release(x->data);
	release(x);
	return n;
}

//子树分离，要对分离出来的子树重新封装，并返回给上层的调用者
template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	//注意FromParentTo 不是对指针操作
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	//这里封装就是设置根节点，根节点的parent，以及设置_size即可
	BinTree<T> *S = new BinTree<T>;
	S->_root = x->_root;
	//不要忘记把子树根节点原来的parent节点设置为NULL
	x->parent = NULL;
	S->_size = x->size();
	_size -= x->size();
	return S;


}

//接下来就是最重要的遍历了！这里注意和之前的自己实现的遍历方法相比较一下
//遍历的过程就是把二叉树这个半线性结构转换为线性结构的过程

//这里还是先写一下二叉树的简单的三种递归遍历
template<typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit)
{
	if(!x)	return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

template<typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit)
{
	if(!x)	return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template<typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit)
{
	if(!x)	return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

//遍历迭代版

//先序遍历迭代版#1，这个版本和我一开始的先序遍历的思路一样
//尾递归优化：尾递归是指函数的最后一步是调用函数自身，那么此时在再一次调用这个函数时，不需要保存上一个函数的信息
template<typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	if(x)	s.push(x);
	while(!s.empty())
	{
		BinNodePosi(T) n = s.pop();
		//这里注意先序遍历，先根节点然后是左，最后是右，因为使用栈所以左右节点进栈顺序相反
		if(HasRChild(*n))	s.push(n->rc);
		if(HasLChild(*n))	s.push(n->lc);
		visit(n->data);
	}
}

//先序遍历迭代版#2，这个版本也是之前很熟悉的思路
//先沿最左通路自顶向下访问沿途节点，然后再自底向上依次以同样的方式遍历这些节点的右子树
//preorder(T) = visit(L0), visit(L1)... visit(Ld),preorder(Rd), preorder(R d-1)...preorder(R0)
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
	while(x)
	{
		visit(x->data);
		//这里我一开始的思路是保存x到栈中，之后取出来后再求得它的右子节点并进行同样的操作
		//但实际上这里直接把x的右孩子存进来就好了
		S.push(x->rc);
		x = x->lc;
	}
}

template<typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	while(true)
	{
		//这里就是对每一个节点，都采用先沿最左通路遍历，然后自底向上遍历右子树，
		//这里“每一个节点”指的是根节点-》每一课右子树根节点
		//问题：这种遍历的栈的最后出来的那个元素是不是一定是NULL？
		//反证法：如果最后一个不是NULL。那么它还需要遍历其左子树和右子树，在左子树遍历完后，还需从栈中取出其右子树，不管其右子树是不是为空，都矛盾了
		//所以先序遍历栈中最后一个pop的元素一定是一个NULL，且一旦检测到当前x为NULL且栈为空，那就表示遍历结束，所以这就证明了我之前的那个退出循环的方式是正确的
		visitAlongLeftBranch(x, visit, s);
		//这里退出循环的方法和我之前的有些不太一样
		if(s.empty())	break;
		x = s.pop();
		
	}
}

//迭代版中序遍历
//迭代版中序遍历版本#1
//课本上的思路与我一开始的思路也很相似，就是按照自底向上的方式，依次 访问根节点-》遍历右子树-》访问上一个根节点 这样的顺序
template<typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>  &s)
{
	while(x)
	{
		//沿着最左通路，记录沿途各个根节点
		s.push(x);
		x = x->lc;
	}
}
