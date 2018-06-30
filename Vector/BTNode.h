#include "Vector.h"
#define BTNodePosi(T) BTNode<T>*

template<typename T> struct BTNode{
	BTNodePosi(T) parent;
	Vector<T> key;
	//长度总比key多1
	Vector<BTNodePosi(T)> child;
	//构造函数
	//BTNode只能作为根节点创建？？
	BTNode(){
		parent = NULL;
		child.insert(0, NULL);
	}
	BTNode(T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL){
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc);
		child.insert(1, rc);
		if(lc)
			lc->parent = this;
		if(rc)
			rc->parent = this;
	}
};