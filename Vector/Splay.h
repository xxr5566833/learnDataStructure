#include "BST.h"

template<typename T> 
class Splay : public BST<T>
{
public:
	//将节点v伸展至根
	BinNodePosi(T) splay(BinNodePosi(T) v);
	BinNodePosi(T) &search(const T &e);
	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc = lc;
	if(lc)
		lc->parent = p;
}

template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rc = rc;
	if(rc)
		rc->parent;
}

template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
	if(!v)
		return NULL;
	BinNodePosi(T) p;
	BinNodePosi(T) g;
	while((p = v->parent) && (g = p->parent)){
		//保存下原来的曾祖父
		BinNodePosi(T) gg = g->parent;
		//接下来和之前的rotateAt一样，根据v p g的不同情况选择不同旋转策略
		if(IsLChild(*v))
			if(IsLChild(*p))
			{
				attachAsLChild(g, p->rc);
				attachAsRChild(p, g);
				attachAsLChild(p, v->rc);
				attachAsRChild(v, p);
			}
			else{
				attachAsRChild(g, v->lc);
				attachAsLChild(v, g);
				attachAsLChild(p, v->rc);
				attachAsRChild(v, p);
			}
		else{
			if(IsRChild(*p)){
				attachAsRChild(g, p->lc);
				attachAsRChild(p, v->lc);
				attachAsLChild(p, g);
				attachAsLChild(v, p);
			}
			else{
				attachAsRChild(p, v->lc);
				attachAsLChild(g, v->rc);
				attachAsRChild(v, g);
				attachAsLChild(v, p);
			}
		}
		if(!gg)
			v->parent = NULL;
		else{
			g == gg->lc ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}
	//双层伸展结束后，必有g为NULL，但是由于v的深度的奇偶性不确定，所以可能p不为空，还有一层需要提高
	if(p = v->parent)
	{
		//此时p应该已经是V的parent为什么if还要设置一次
		if(IsLChild(*v))
		{
			//需要向右旋转
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	//这里一定会设置v的parent，上面while里的设置是为了让while一开始的判断是正确的
	v->parent = NULL;
	return v;
}

template<typename T>
BinNodePosi(T) &Splay<T>::search(const T &e)
{
	BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
	_root = splay(p ? p : _hot);
	return _root;
	//注意对_root的设置
}


//这里不需要先search，再插入，再伸展，因为此时的search已经把伸展的功能加入了
//我们直接在伸展后的结果的基础上进行修改
template<typename T>
BinNodePosi(T) Splay<T>::insert(const T &e)
{
	if(!_root)
	{
		//退化情况，树为空
		_size ++;
		return _root = new BinNode<T>(e);
	}
	//如果已经存在，那么返回_root其实就是返回数据项为e的那个节点
	if(e == search(e)->data)
		return _root;
	_size ++;
	BinNodePosi(T) t = _root;
	//接下来调整小于等于7个指针以完成局部重构
	if(_root->data < e)
	{
		//此时应该让新节点作为根节点，并让原来的_root作为它的左子树
		t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
		if(HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc = NULL;
		}
	}
	else{
		t->parent = _root = new BinNode<T>(e, NULL, t->lc, t);
		if(HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc = NULL;
		}
	}
	updateHeightAbove(t);
	return _root;
}

template<typename T>
bool Splay<T>::remove(const T &e)
{
	//从伸展树中删除关键码e
	if(!_root || (e != search(e)->data))
		return false;
	BinNodePosi(T) w = _root;
	if(!HasLChild(*_root)){
		//没有左子树，那么直接删除
		_root = _root->rc;
		if(_root)
			_root->parent = NULL;
	}
	else if(!HasRChild(*_root))
	{
		//没有右子树，这里和remove之前的处理方法类似
		_root = _root->lc;
		if(_root)
			_root->parent = NULL;
	}
	else{
		//左右子树同时存在
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = NULL;
		_root->lc = NULL;

		_root = _root->rc;
		_root->parent = NULL;

		search(w->data);
		/*这里注意：右子树中都是比w->data大的数据，而根据search中的searchIn的查找方法，
		一旦查找失败，_hot会被设置为最后一次访问的非空结点，而这个飞空节点一定是w的后继！
		原因：w的数据项比这个右子树里的每一个都小，按照searchIn的查找策略，它会沿着最左通路进行查找
		直到找到右子树中的最小结点，即w的后继节点
		同时根据伸展的等价性，在这个后继被伸展为根节点时，它是一定没有左子节点的，因为它已经是最小的
		*/
		_root->lc = lTree;
		lTree->parent = _root;
	}
	//释放节点
	_size --;
	//其他节点在splay时更新了高度，感觉这里对高度的更新有点乱，不过伸展树也不看高度
	if(_root)
		updateHeight(_root);
	return true;
}