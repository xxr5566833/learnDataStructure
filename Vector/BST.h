#include "BinTree.h"

template<typename T>
class BST:public BinTree<T>{
public:
	BinNodePosi(T) _hot;
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);//对x及其父亲，祖父做统一旋转调整

	virtual BinNodePosi(T) &search(const T &e);
	virtual BinNodePosi(T) insert(const T &e);
	virtual bool remove(const T &e);
};

//在以v为根的搜索树中查找关键码e
template<typename T>
static BinNodePosi(T) &searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot)
{
	//递归基：在节点v（或假想的通配节点处命中）
	if(!v || (e == v->data))
		return v;
	hot = v;
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot );
}

template<typename T>
static BinNodePosi(T) &searchInIter(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot)
{

	while(!v && v->data != e)
	{
		hot = v;
		v = ((v->data > e) ? v->lc : v->rc);
	}
	return v;
}

template<typename T>
BinNodePosi(T) &BST<T>::search(const T &e)
{
	//注意这里将_hot置空
	return searchIn(_root, e, _hot = NULL);
	//返回目标节点位置的引用，以便后续插入，删除等操作
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e){
	BinNodePosi(T) &x = search(e);
	if(x)
		return x;
	
	x = new BinNode<T>(e, _hot);
	_size ++;
	updateHeightAbove(x);
	return x;
}

template<typename T>
bool BST<T>::remove(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if(!x)
		return false;
	removeAt(x, _hot);
	_size --;
	updateHeightAbove(_hot);
	return true;
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot)
{
	//实际被摘除的节点，初值同x
	BinNodePosi(T) w = x;
	//实际被删除节点的接替者
	BinNodePosi(T) succ = NULL;
	if(!HasLChild(*x))
		succ = x = x->rc;
	else if(!HasRChild(*x))
		succ = x = x->lc;
	else{
		//如果一直采用后继来代替原来的结点，会造成在多次删除后，树的“左倾”，所以这里最好使用随机数选择后继或者是前驱来代替
		if(rand() % 2)
		{
			w = w->succ();
			swap(x->data, w->data);
			BinNodePosi(T) u = w->parent;
			//这句话需要理解一下：
			//如果u是x，说明之前x的后继就是它的右子节点，那么此时用这个后继的右子节点替换这个后继的位置，同时设置后继的父亲节点与它的关系
			//如果u不是x，那么说明x的后继是x的右子树中的最左子节点，它一定是u的左子节点，然后做同样的操作即可
			//这里也和算法导论里所讲的思路差不多，但是因为这里直接交换了数据项所以大大简化了操作，其他地方都一样
			((u == x) ? u->rc : u->lc) = succ = w->rc;
		}
		else{
			w = w->pred();
			swap(x->data, w->data);
			BinNodePosi(T) u = w->parent;
			//前驱和后继这里也不相同，主要是前驱节点一定没有右子树，所以这里需要使用w->lc
			((u == x) ? u->lc : u->rc) = succ = w->lc;
		}
		
	}
	//上面都是设置父亲节点的对孩子节点的lc/rc关系，下面需要设置孩子节点对父亲节点的parent关系
	hot = w->parent;
	if(succ)
		succ->parent = hot;
	return succ;
}

