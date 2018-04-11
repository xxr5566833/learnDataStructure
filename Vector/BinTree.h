#pragma once
#include "BinNode.h"
#include "stdafx.h"
#include "Stack.h"
template<typename T>
class BinTree{
protected:
	int _size;
	BinNodePosi(T) _root;
	//���½ڵ�x�ĸ߶�
	virtual int updateHeight(BinNodePosi(T) x);
	//���½ڵ�x�������ȵĸ߶�
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

	//������ڵ�
	BinNodePosi(T) insertAsRoot(T const &e);

	//e��Ϊx�����Ӳ���
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);

	//e��Ϊx���Һ��Ӳ���
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);

	//T��Ϊx����������
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&T);

	//T��Ϊx������������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&T);

	//ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	int remove(BinNodePosi(T) x);

	//������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
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

	//����ȽϺͱȶ���ʲô������?
	bool operator< (BinTree<T> const &t)
	{
		return _root && t._root && _root < t._root;
	}

	bool operator== (BinTree<T> const &t)
	{
		return _root && t._root && (_root == t._root);
	}
};

//ʵ��
//���¸߶�
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

//�ڵ���루Լ��������ԭ��λ����û�нڵ�ʱ��
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
	//ע��������ά���߶�
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

//�������룬
//����һ����������������Ϊ��һ����������ָ���ڵ��������������������
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&S)
{
	//��S�����ڵ�x�����������룬S�����ÿ�
	//ע�����ﻹҪ����S��root�ڵ��parent����Ȼ������֮ǰ��Ҫ���ж�һ���ǲ���NULL
	if(x->lc = S->_root)	x->lc->parent = x;
	
	_size += S->size();
	updateHeightAbove(x);
	//height�����ʣ�ÿһ���ڵ��heightֻ�����ĺ���ڵ��йأ��������ĸ��׽ڵ��޹�
	//������ȾͲ�һ����
	
	//�ͷ�ԭ���Ĳ��裺
	S->_root = NULL;
	S->size = 0;
	//release()��ôʵ�֣�
	release(S);
	S = NULL;
	//���ؽ���λ��
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

//����ɾ��
template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	//�ж����Ը��ڵ��ָ�룬ԭ�����ڵ��x��λ�����ھͱ����NULL
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	//�����ɾ��Ҫ���ر�ɾ���Ľڵ�������ԭ��
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

//�������룬Ҫ�Է���������������·�װ�������ظ��ϲ�ĵ�����
template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	//ע��FromParentTo ���Ƕ�ָ�����
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	//�����װ�������ø��ڵ㣬���ڵ��parent���Լ�����_size����
	BinTree<T> *S = new BinTree<T>;
	S->_root = x->_root;
	//��Ҫ���ǰ��������ڵ�ԭ����parent�ڵ�����ΪNULL
	x->parent = NULL;
	S->_size = x->size();
	_size -= x->size();
	return S;


}

//��������������Ҫ�ı����ˣ�����ע���֮ǰ���Լ�ʵ�ֵı���������Ƚ�һ��
//�����Ĺ��̾��ǰѶ�������������Խṹת��Ϊ���Խṹ�Ĺ���

//���ﻹ����дһ�¶������ļ򵥵����ֵݹ����
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

//����������

//�������������#1������汾����һ��ʼ�����������˼·һ��
//β�ݹ��Ż���β�ݹ���ָ���������һ���ǵ��ú���������ô��ʱ����һ�ε����������ʱ������Ҫ������һ����������Ϣ
template<typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	if(x)	s.push(x);
	while(!s.empty())
	{
		BinNodePosi(T) n = s.pop();
		//����ע������������ȸ��ڵ�Ȼ������������ң���Ϊʹ��ջ�������ҽڵ��ջ˳���෴
		if(HasRChild(*n))	s.push(n->rc);
		if(HasLChild(*n))	s.push(n->lc);
		visit(n->data);
	}
}

//�������������#2������汾Ҳ��֮ǰ����Ϥ��˼·
//��������ͨ·�Զ����·�����;�ڵ㣬Ȼ�����Ե�����������ͬ���ķ�ʽ������Щ�ڵ��������
//preorder(T) = visit(L0), visit(L1)... visit(Ld),preorder(Rd), preorder(R d-1)...preorder(R0)
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
	while(x)
	{
		visit(x->data);
		//������һ��ʼ��˼·�Ǳ���x��ջ�У�֮��ȡ������������������ӽڵ㲢����ͬ���Ĳ���
		//��ʵ��������ֱ�Ӱ�x���Һ��Ӵ�����ͺ���
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
		//������Ƕ�ÿһ���ڵ㣬��������������ͨ·������Ȼ���Ե����ϱ�����������
		//���ÿһ���ڵ㡱ָ���Ǹ��ڵ�-��ÿһ�����������ڵ�
		//���⣺���ֱ�����ջ�����������Ǹ�Ԫ���ǲ���һ����NULL��
		//��֤����������һ������NULL����ô������Ҫ������������������������������������󣬻����ջ��ȡ�������������������������ǲ���Ϊ�գ���ì����
		//�����������ջ�����һ��pop��Ԫ��һ����һ��NULL����һ����⵽��ǰxΪNULL��ջΪ�գ��Ǿͱ�ʾ�����������������֤������֮ǰ���Ǹ��˳�ѭ���ķ�ʽ����ȷ��
		visitAlongLeftBranch(x, visit, s);
		//�����˳�ѭ���ķ�������֮ǰ����Щ��̫һ��
		if(s.empty())	break;
		x = s.pop();
		
	}
}

//�������������
//��������������汾#1
//�α��ϵ�˼·����һ��ʼ��˼·Ҳ�����ƣ����ǰ����Ե����ϵķ�ʽ������ ���ʸ��ڵ�-������������-��������һ�����ڵ� ������˳��
template<typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>  &s)
{
	while(x)
	{
		//��������ͨ·����¼��;�������ڵ�
		s.push(x);
		x = x->lc;
	}
}
