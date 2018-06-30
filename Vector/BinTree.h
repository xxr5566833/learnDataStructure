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

	void swapIter(BinNodePosi(T) x);
	void swapRecu(BinNodePosi(T) x);

	bool valueLessSumIter(BinNodePosi(T) x);
	bool valueLessSumRecu(BinNodePosi(T) x);
};


//实现
//更新高度

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	int heightlc = stature(x->lc);
	int heightrc = stature(x->rc);
	return x->height = 1 + (heightlc > heightrc ? heightlc : heightrc);
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x)
	{
		//如果高度没有发生变化，那么不需要继续向上更新
		if(x->height == updateHeight(x))
			break;
		x = x->parent;
	}
}

//节点插入（约定都是在原来位置上没有节点时）
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	//错误：注意对_size的维护
	_size = 1;
	return _root = new BinNode<T>(e);

}


template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	_size ++;
	x->insertAsLC(e);
	//错误：注意这里来维护高度
	updateHeightAbove(x);
	//错误：这里需要返回新加入的节点
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
	S->_size = 0;
	//release()怎么实现？
	//为什么查了以后没有发现什么关于release的消息。。
	S = NULL;
	//返回接入位置
	return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S)
{
	//既要把x的右孩子赋为S的root，又要判断这个root是不是为NULL
	if(x->rc = S->_root)	x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	//所以这里先不管release
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

//递归释放每个节点的空间，并返回该节点为根节点的子树的节点数
template<typename T>
static int removeAt(BinNodePosi(T) x)
{
	if(!x)	return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete x;
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
		//后来再一次写这个程序的时候，把中序遍历和后序混了，
		//中序遍历是先根节点，然后是右子树，然后才是上上一层的根节点和右子树
		//所以在沿着最左通路走时，只需要把根节点压栈即可，之后拿出来visit后，直接设置为其右子树即可
		s.push(x);
		x = x->lc;
	}
}

template<typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> s;
	while(!s.empty() || x)
	{
		//中序遍历就是对于每一个节点，先沿最左通路保存要遍历的节点，然后取出最左通路的最末节点，访问它，并遍历它的右子树
		goAlongLeftBranch(x, s);
		
		x = s.pop();
		visit(x->data);
		x = x->rc;
	}
}

template<typename T>
BinNodePosi(T) BinNode<T>::pred()
{
	BinNodePosi(T) p = this;
	if(p->lc)
	{
		p = p->lc;
		while(p->rc)
			p = p->rc;
	}
	else{
		while(IsLChild(*p))
		{
			p = p->parent;
		}
		p = p->parent;
	}
	return p;
}
//遍历为二叉树的各个节点赋予了一个次序，于是一旦指定了遍历策略，就可以与向量和列表一样，为二叉树的节点之间定义前驱与后继关系

template<typename T>
BinNodePosi(T) BinNode<T>::succ()
{
	BinNodePosi(T) s = this;
	if(s->rc)
	{
		s = s->rc;
		while(HasLChild(*s))
		{
			s = s->lc;
		}
		return s;
	}
	//这里使用宏定义
	while(IsRChild(*s))
	{
		s = s->parent;
	}
	s = s->parent;
	//当没有后继时，返回NULL
	return s;
}

//中序遍历迭代版#2
//这个版本就是把版本#1的while循环里的那个while循环给拆开由外面的while控制了
template<typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;
	while(true)
	{
		if(x)
		{
			S.push(x);
			x = x->lc;
		}
		else if(!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rc;
		}else
			break;
	}
}

//中序遍历版本#3，这个思路就是利用一个标志位表示是否刚从右子树处回溯
template<typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST &visit)
{
	//这里不适用栈，那么怎么保证可以获得下一次遍历的根节点呢？
	//就是用succ的思想，不管怎样，下一次一定是遍历后继节点
	bool backtrack = false;
	while(true)
	{
		if(!backtrack && HasLChild(*x))
		{
			x = x->lc;
		}
		else{
			//是从左子树回溯来的或者是没有左子树
			//这里的思路和我之前的“把左子树遍历完以后设置其左子树为空”是一个道理，但是我们不能改变其树的结构，所以用backtrack来表示
			//此时x一定要表示为遍历完的左子树的父亲节点
			visit(x->data);
			if(HasRChild(*x))
			{
				x = x->rc;
				//这里开始，输出根节点，然后遍历其右子树，所以需要把backtrack关闭
				//如果不关闭，那么在第一次回溯后，所有的子树都无法遍历其左子树
				backtrack = false;
			}
			else{
				//这里需要获得x的后继，因为当前一定是某一左子树被遍历完毕，原来是用栈记录的，现在使用succ方法来获得
				if(!(x = x->succ()))	break;
				//backtrack被设置说明当前栈顶元素的左子树已经被遍历完毕，也就是左孩子节点的右子树被遍历完毕
				backtrack = true;
			}
		}

	}
}

//不仅无需辅助栈，也无需辅助标志位
//就是利用succ方法，但是这里不是每个节点都调用succ获得它的下一个节点，而是在当前节点没有右子节点时调用succ
///如果当前节点有右子节点，那么还是找到这个右子树的最左子节点（也是succ的其中一种情况），这个逻辑在while中实现了
//那不如直接所有节点都调用succ？
template<typename T, typename VST>
void travIn_I4(BinNodePosi(T) x, VST &visit)
{
	while(true)
	{
		if(HasLChild(*x))
		{
			x = x->lc;
		}
		else{
			//此时x没有左孩子
			visit(x->data);
			while(!HasRChild(*x))
			{
				if(x = x->succ())	
					return ;
				else
					visit(x->data);
			}
			x = x->rc;
		}
	}
}



//后序遍历

//这里没有理解好这个函数的作用
//后序遍历也可以和前两个一样，有确定的遍历顺序，所以这个方法不光是要遍历到后序遍历的第一个节点
//最重要的还是要用栈来确定这棵子树的后序遍历顺序
template<typename T>

static void gotoHLVFL(Stack<BinNodePosi(T)> &s)
{
	//自顶向下，反复检查栈顶节点
	//这个循环结束的条件是x为NULL，此时只能说明x是某个节点的右子节点=》x的父亲节点既没有左孩子也没有右孩子=》x的父亲节点即为我们要找的这个子树的后序遍历的第一个节点
	while(BinNodePosi(T) x = s.top())
	{
		if(x->lc)
		{
			//有左孩子
			//此时注意要先把右孩子入栈（如果有的话），因为后序遍历的过程中，右子树是优先于根节点遍历的
			if(x->rc)	s.push(x->rc);
			s.push(x->lc);
		}
		else
		{
			//没左孩子，那么才向右
			s.push(x->rc);
		}
	}
	//把栈顶的NULL弹出
	s.pop();
}


template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> s;
	//这里要注意检查x
	if(x)
		s.push(x);
	while(!s.empty())
	{
		//如果栈顶元素和刚出战的元素是父子关系，那么只能说明栈顶元素所在的子树已被遍历完，栈顶元素该出栈
		//否则，栈顶元素一定是刚出栈的元素的右兄弟，此时应该遍历这个栈顶元素所在的子树
		//除了一个特例，就是一开始x是根节点，此时x和栈顶的元素是一样的。自然不满足栈顶元素是x的父亲节点这个关系，所以需要遍历
		if(s.top() != x->parent)
		{
			//表明此时应该开始遍历这个子树，并确定节点的遍历顺序
			gotoHLVFL(s);
		}
		x = s.pop();
		visit(x->data);
	}
}

//总结一下，前序遍历就是沿着最左通路自上而下访问根节点，直到某个根节点没有左孩子，然后自下而上以同样方式遍历每个根节点的右子树
//中序遍历就是先沿着最左通路到达那个没有左孩子的最左子节点，然后自下而上的沿着最左通路先遍历根节点，再遍历右子树
//后序遍历就是从根节点开始，先找到最高左侧可见叶子节点，然后按照栈的存储顺序，对每一个节点看是打印还是遍历其右子树


//最后是层次遍历，应该写在BinNode的实现里的
template <typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit)
{
	//二叉树层次遍历算法
	Queue<BinNodePosi(T)> q;
	q.enqueue(this);
	while(!q.empty())
	{
		BinNodePosi(T) x = q.dequeue();
		if(HasLChild(*x))
		{
			q.enqueue(x->lc);
		}
		if(HasRChild(*x))
		{
			q.enqueue(x->rc);
		}
		visit(x->data);
	}
}

//swap 交换二叉树的每一个节点的左右孩子
template <typename T>
void BinTree<T>::swapRecu(BinNodePosi(T) x)
{
	//这里采用先序遍历
	if(x)
	{
		BinNodePosi(T) temp = x->lc;
		x->lc = x->rc;
		x->rc = temp;
		if(x->rc)
			swapRecu(x->rc);
		if(x->lc)
			swapRecu(x->lc);
	}

}

template <typename T>
void BinTree<T>::swapIter(BinNodePosi(T) x)
{
	//迭代版，这里我觉得可能需要使用层次遍历了
	//这里只需要能遍历每一个节点就ok了，不需要管遍历的次序
	//这里就用先序遍历
	Stack<BinNodePosi(T)> s;
	while(true)
	{
		//原来是线序遍历写错了
		if(x)
		{
			
			if(x->rc)
				s.push(x->rc);
			BinNodePosi(T) p = x;
			x = x->lc;
			BinNodePosi(T) temp = p->lc;
			p->lc = p->rc;
			p->rc = temp;
		}
		else{
			if(s.empty())
				break;
			x = s.pop();
		}
	}
}

//判断一棵树是否所有节点的数值均不小于其真祖先的数值总和
bool valueNotLessSum(BinNode<int> *n, int sum)
{
	if(n->data < sum)
		return false;
	bool result = true;
	if(n->lc)
	{
		result = result && valueNotLessSum(n->lc, sum + n->data);
	}
	if(n->rc)
	{
		result = result && valueNotLessSum(n->rc, sum + n->data);
	}
	return result;
}

bool valueNotLessSum(BinNode<int> *n)
{
	//sum表示当前n节点的所有真祖先的权值之和
	int sum = 0;
	Stack<BinNode<int> *> s;
	if(n)	
		s.push(n);
	while(!s.empty())
	{
		//按照后序遍历思路，先左再右再父亲节点
		if(n->parent != s.top())
		{
			//说明n是左子节点，s.top()是其兄弟节点
			while(s.top())
			{
				//这里我们需要遍历这个右子树
				n = s.top();
				if(n->lc)
				{
					if(n->rc)
						s.push(n->rc);
					s.push(n->lc);
					sum += n->data;
					n = n->lc;	
				}
				else{
					if(n->rc)
					{
						s.push(n->rc);
						sum += n->data;
					}
					else{
						break;
					}
				}
			}
		}
		else{
			//如果上一次节点n与当前栈顶是父亲关系，那么此时应该把sum减去栈顶元素的data
			//如果是兄弟关系，那么sum不变
			sum -= s.top()->data;	
		}
		n = s.pop();
		if(n->data < sum)
			return false;
		//此时说明n已经被检查过了，接下来应该把sum换成它的真祖父的权值和
		return true;
	}
	return false;
}

//5-25
//设计并实现一个递归算法，在O(n)时间内将每个节点的数值替换为其后代中的最大数值
void exchangeDataUseMax(BinNode<int> *n, int *max)
{
	//这里要使用后序遍历，因为必须知道子节点的信息才能确定父节点的信息
	if(n)
	{
		int lmax, rmax;
		exchangeDataUseMax(n->lc, &lmax);
		exchangeDataUseMax(n->rc, &rmax);
		//先调用获得其真后代的最大值
		//然后更新max
		*max = lmax > rmax ? lmax : rmax;
		*max = (*max) > n->data ? *max : n->data;
		n->data = *max;
	}
	else{
		//对于null节点，返回最小int（因为这里类型是int）
		*max = 0x80000000;
	}
	
}
//迭代版：
void exchangeDataUseMax(BinNode<int> *n)
{
	Stack<BinNode<int> *> s;
	//我需要一个max栈来记录每一个节点的后代的max
	Stack<int> max;
	//当前节点的真后代的max
	int realmax = 0;
	if(n)
		s.push(n);
	while(!s.empty())
	{
		if(n->parent != s.top())
		{
			while(true)
			{
				n = s.top();
				if(n->lc)
				{
					if(n->rc)
						s.push(n->rc);
					s.push(n->lc);
					n = n->lc;
				}
				else{
					if(n->rc)
					{
						s.push(n->rc);
					}
					else
					{
						//这里作为上面递归的递归基，把max更新一下
						realmax = 0x80000000;
						break;
					}
				}
			}
		}
		else{
			//此时栈顶是n的父亲节点，那么需要更新n的父亲的真后代的max
			if(s.top()->lc && s.top()->rc)
			{
				//那么从max栈中弹出两个，一定分别为左右子树的max，求出最大的max
				int rmax = max.pop();
				int lmax = max.pop();
				realmax = rmax > lmax ? rmax : lmax;
			}
			else
			{
				realmax = max.pop();
			}
		}
		
		n = s.pop();
		if(realmax < n->data)
			realmax = n->data;
		else
			n->data = realmax;
		//把当前节点后代的最大值push到栈里，供当前节点的父亲节点使用
		max.push(realmax);
	}
	
}

//把树中每个节点的data域设置为按照其层次遍历的顺序的编号
//父亲节点是k，那么左子节点是2k+1,右子节点是2k+2
//首先是递归
void setData(BinNode<int> *n, int k)
{
	if(n)
	{
		if(n->parent)
		{
			if(IsLChild(*n))
			{
				n->data = 2 * k + 1;
			}
			else{
				n->data = 2 * k + 2;
			}
		}
		else{
			n->data = 0;
		}
		setData(n->lc, n->data);
		setData(n->rc, n->data);
	}
}
//迭代版的设置顺序编号
//各种遍历都可实现吧，但是用层次遍历最好是完全二叉树，普通的二叉树用层次遍历我觉得实现起来有点麻烦
void setData(BinNode<int> *n)
{
	//这里使用先序遍历
	Stack<BinNode<int> *> s;
	while(true)
	{
		while(n)
		{
			s.push(n->rc);
			if(n->parent)
			{
				n->data = (IsLChild(*n)) ? 2 * n->parent->data + 1 : 2 * n->parent->data + 2;
			} 
			else
				n->data = 0;
			n = n->lc;

		}
		if(s.empty())
			break;
		n = s.pop();
	}
}