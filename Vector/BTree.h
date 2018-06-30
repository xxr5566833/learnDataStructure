#include "BTNode.h"

template<typename T>
class BTree{
public:
	//存放的关键码总数，和之前的二叉树的_size语义差不多
	int _size;
	//阶次，至少为3——创建时指定，一般不能修改
	int _order;
	BTNodePosi(T) _root;
	//和BST一样，search最后访问的非空的结点位置
	BTNodePosi(T) _hot;
	//插入而上溢后的分裂处理，这个之前好像学过
	void solveOverflow(BTNodePosi(T));
	//因删除而下溢后的合并处理
	void solveUnderflow(BTNodePosi(T));

	BTree(int order = 3):
	_order(order), _size(0)
	{_root = new BTNode<T>();}

	int const order()
	{
		return _order;
	}
	int const size()
	{
		return _size;
	}
	BTNodePosi(T) &root()
	{
		return _root;
	}
	bool empty() const
	{
		return !_root;
	}
	BTNodePosi(T) search(const T &e);
	bool insert(const T &e);
	bool remove(const T &e);

};

template<typename T>
BTNodePosi(T) BTree<T>::search(const T &e)
{
	BTNodePosi(T) v = _root;
	_hot = NULL;
	while(v)
	{
		//找到不大于e的最大关键码
		Rank r = v->key.search(e);
		if((0 <= r) && (e == v->key[r]))
			return v;
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL;
	//失败就返回NULL
}

template<typename T>
bool BTree<T>::insert(const T &e)
{
	BTNodePosi(T) v = search(e);
	if(v)
		return false;

	Rank r = _hot->key.search(e);
	_hot->key.insert(r + 1, e);
	//此时_hot的下一层必然是最底层，故这里直接插入关键码和分支即可
	_hot->child.insert(r + 2, NULL);
	_size++;
	//如有必要，需要做分裂
	solveOverflow(_hot);
	return true;
}
template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	//注意分支数比关键码数多1，关键看关键码和_order的关系
	if(_order >= v->child.size())
		return ;
	Rank s = _order >> 1;
	BTNodePosi(T) u = new BTNode<T>();
	//把Rank为s的结点的右侧关键码放进一个新的结点
	for(Rank j = 0 ; j < _order - s - 1 ; j++)
	{
		u->child.insert(j, v->child.remove(s + 1));
		u->key.insert(j, v->key.remove(s + 1));
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);
	//因为初始化时0个关键码，1个分支NULL，故child[0]可以作为判断child是否为空的条件
	//这里需要通过debug测试用例来加深理解
	if(u->child[0])
		for(Rank j = 0 ; j < _order - s ; j++)
			u->child[j]->parent = u;
	BTNodePosi(T) p = v->parent;
	if(!p)
	{
		//说明原来v就是根节点
		_root = p = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}
	//p中指向u的指针的秩
	Rank r = 1 + p->key.search(v->key[0]);
	//把s放到p中
	p->key.insert(r, v->key.remove(s));
	p->child.insert(r + 1, u);
	u->parent = p;
	solveOverflow(p);

}
template<typename T>
bool BTree<T>::remove(const T &e)
{
	BTNodePosi(T) v = search(e);
	if(!v)
		return false;
	Rank r = v->key.search(e);
	if(v->child[0])
	{
		//v非叶子，则e的后继必然属于某个叶结点
		BTNodePosi(T) u = v->child[r + 1];
		while(u->child[0])
			u = u->child[0];
		//这样是为了找出e的后继
		//把后继的数据覆盖掉原来要删除的关键码的数据，然后转化为要删除这个后继（一定是叶子节点）的数据
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1);
	_size --;
	solveUnderflow(v);
	return true;
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v){
	if((_order + 1) / 2 <= v->child.size())
		return;
	BTNodePosi(T) p = v->parent;
	if(!p){
		//只有在树根不含关键码时才需要做下溢处理
		if(!v->key.size() && v->child[0]){
			//作为树根的v已经不含关键码，却有唯一的非空的孩子
			//不含关键码，那么可能没有任何孩子也可能只有一个孩子
			_root = v->child[0];
			_root->parent = NULL;
			v->child[0] = NULL;
			//释放v
		}
		return ;
	}
	Rank r = 0;
	while(p->child[r] != v)
		r++;
	//确定v是p的第r个孩子
	//此时v可能不含关键码，故不能通过关键码查找？？
	//在实现了孩子指针的判等器后，也可以直接用find接口定位

	// 接下来实现各种情况
	//情况1：向左兄弟借关键码
	if(r > 0){
		//左兄弟必然存在
		BTNodePosi(T) ls = p->child[r - 1];
		//注意child的长度比key还大1
		if((_order + 1) / 2 < ls->child.size()){
			//此时左兄弟的数量足够
			//p先借一个给v
			v->key.insert(0, p->key[r - 1]);
			//左兄弟的最大关键码转入p
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
			//同时ls的最右侧孩子过继给v，这个不要忘了
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
			if(v->child[0]){
				v->child[0]->parent = v;
			}
			//疑问：这样的话，child[0]是null并不意味着之后的child都是null或者根本不存在这一项？
			return ;
			//相当于右旋操作
		}
	}
	//向右兄弟借关键码
	if(p->child.size() - 1 > r){
		//若v不是p的最后一个孩子，那么右兄弟必然存在
		BTNodePosi(T) rs = p->child[r + 1];
		if((_order + 1) / 2 < rs->child.size()){
			//p借出相应位置上的关键码给v作为最大关键码
			v->key.insert(v->key.size(), p->key[r]);
			p->key[r] = rs->key.remove(0);
			v->child.insert(v->child.size(), rs->child.remove(0));
			//作为v的最右侧孩子
			if(v->child[v->child.size() - 1]){
				//修改之前孩子的父亲
				v->child[v->child.size() - 1]->parent = v;
			}
			return ;
		}
	}
	//左右兄弟要么为空，要么太瘦
	if(r > 0){
		BTNodePosi(T) ls = p->child[r - 1];
		ls->key.insert(ls->key.size(), p->key.remove(r - 1));
		p->child.remove(r);
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if(ls->child[ls->child.size() - 1]){
			ls->child[ls->child.size() - 1]->parent = ls;
		}
		//v剩余的关键码和孩子，依次转入ls
		while(!v->key.empty()){
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if(ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		//释放v，此时v所有key和child已经归入左兄弟

	}
	else{
		//与右兄弟合并（不可能左右兄弟同时不存在）
		//有关键码， 那么这个关键码两边的child就应该存在，
		BTNodePosi(T) rs = p->child[r + 1];
		rs->key.insert(0, p->key.remove(r));
		p->child.remove(r);

		rs->child.insert(0, v->child.remove(v->child.size() - 1));
		if(rs->child[0])
			rs->child[0]->parent = rs;
		while(!v->key.empty()){
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if(rs->child[0]){
				rs->child[0]->parent = rs;
			}
		}
		//释放v
	}
	//递归分裂
	solveUnderflow(p);
	return ;
}

