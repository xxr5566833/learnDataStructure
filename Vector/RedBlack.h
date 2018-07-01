#include "BST.h"
template<typename T> class RedBlack:public BST<T>{

public:
	//双红修正
	void solveDoubleRed(BinNodePosi(T) x);
	//双黑修正
	void solveDoubleBlack(BinNodePosi(T) x);
	//更新节点x的高度
	int updateHeight(BinNodePosi(T) x);

	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

// 红黑树相关宏定义
#define IsBlack (!(p) || (RB_BLACK == (p)->color))
//非黑即红
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x)( \
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
)

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x){
	x->height = max(stature(x->lc), stature(x->rc));
	// 不管是height 还是 height++ return的都是height
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T &e){
	BinNodePosi(T) &x = search(e);
	if(x)
		return x;
	//创建红节点x:以_hot为父，黑高度注意设置为-1
	x = new BinNode<T>(e, _hot, NULL, NULL, -1);
	solveDoubleRed(x);
	return x ? x : _hot->parent;
}

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x){
	if(IsRoot(*x)){
		_root->color = RB_BLACK;
		_root->height++;
		return;
	}
	//否则 x的父亲p必存在
	BinNodePosi(T) p = x->parent;
	//p为黑，那么自然可以终止调整
	if(IsBlack(p))
		return ;
	//否则，p为红，则x的祖父必然存在，且必为黑色
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);
	if(IsBlack(u)){
		//u为黑色，含NULL
		//x与p同侧时
		if(IsLChild(*x) == IsLChild(*p))
			p->color = RB_BLACK;
		else
			//异侧
			x->color = RB_BLACK;
		g->color = RB_RED;
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}
	else{
		//u为红色
		p->color = RB_BLACK;
		p->height ++;
		u->color = RB_BLACK;
		u->height++;
		if(!IsRoot(*g))
			g->color = RB_RED;
		solveDoubleRed(g);
	}


}

template<typename T>
bool RedBlack<T>::remove(const T &e){
	BinNodePosi(T) &x = search(e);
	if(!x)
		return false;
	BinNodePosi(T) r = rotateAt(x, _hot);
	if(!(--_size))
		return true;
	//如果节点删完了，那么直接返回true
	if(!_hot){
		_root->color = RB_BLACK;
		updateHeight(_root);
		return true;
	}
	if(BlackHeightUpdated(*_hot))
		return true;
	if(IsRed(r)){
		r->color = RB_BLACK;
		r->height++;
		return true;
	}
	//此时需要解决
	solveDoubleBlack(r);
	return true;
}

// 解决x与被其替代的结点都是黑色
template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r){
	BinNodePosi(T) p = r ? r->parent : _hot;
	if(!p)
		return ;

	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;
	if(IsBlack(s)){
		//s是黑色
		//根据之前的分析，先检查s有没有红色后代
		BinNodePosi(T) t = NULL;
		//s的红孩子，若左右皆红，左者优先，皆黑时为NULL
		if(IsRed(s->rc))
			t = s->rc;
		if(IsRed(s->lc))
			t = s->lc;
		if(t){
			//有红孩子，进入BB-1模式
			//备份原子树根节点p的颜色，并对t及其父亲，祖父通过旋转重平衡，并将新子树的左右孩子染黑
			//注意这里是以t为准进行旋转
			RBColor oldColor = p->color;
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
			if(HasLChild(*b)){
				b->lc->color = RB_BLACK;
				updateHeight(b->lc);
			}
			if(HasRChild(*b)){
				b->rc->color = RB_BLACK;
				updateHeight(b->rc);
			}
			b->color = oldColor;
			updateHeight(b);
			
		}
		else{
			//s没有红孩子，此时根据p的颜色
			s->color = RB_RED;
			s->height--;
			if(IsRed(p))
				p->color = RB_BLACK;
			else{
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}else{
		//BB-3 兄弟s为红，旋转+染色
		s->color = RB_BLACK;
		p->color = RB_RED;
		//t是rotateAt的参数，故需要取与s相对于s父亲相同的位置上的孩子
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
		_hot = p;
		//对t及其父亲，祖父做平衡调整
		FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);
		//继续修复，但是此时p已经是红色了，所以只能是BB-1 或者是 BB-2R
	}
}