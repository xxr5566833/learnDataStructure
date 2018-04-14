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
	int heightlc = stature(x->lc);
	int heightrc = stature(x->rc);
	return x->height = 1 + heightlc > heightrc ? heightlc : heightrc;
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
	return _root = new BinNode<T>(e);

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
	S->_size = 0;
	//release()��ôʵ�֣�
	//Ϊʲô�����Ժ�û�з���ʲô����release����Ϣ����
	S = NULL;
	//���ؽ���λ��
	return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S)
{
	//��Ҫ��x���Һ��Ӹ�ΪS��root����Ҫ�ж����root�ǲ���ΪNULL
	if(x->rc = S->_root)	x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	//���������Ȳ���release
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

template<typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> s;
	while(!s.empty() || x)
	{
		//����������Ƕ���ÿһ���ڵ㣬��������ͨ·����Ҫ�����Ľڵ㣬Ȼ��ȡ������ͨ·����ĩ�ڵ㣬������������������������
		goAlongLeftBranch(x, s);
		
		x = s.pop();
		visit(x->data);
		x = x->rc;
	}
}

//����Ϊ�������ĸ����ڵ㸳����һ����������һ��ָ���˱������ԣ��Ϳ������������б�һ����Ϊ�������Ľڵ�֮�䶨��ǰ�����̹�ϵ
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
	}
	//����ʹ�ú궨��
	while(IsRChild(*s))
	{
		s = s->parent;
	}
	s = s->parent;
	//��û�к��ʱ������NULL
	return s;
}

//�������������#2
//����汾���ǰѰ汾#1��whileѭ������Ǹ�whileѭ�������������while������
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

//��������汾#3�����˼·��������һ����־λ��ʾ�Ƿ�մ�������������
template<typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST &visit)
{
	//���ﲻ����ջ����ô��ô��֤���Ի����һ�α����ĸ��ڵ��أ�
	//������succ��˼�룬������������һ��һ���Ǳ�����̽ڵ�
	bool backtrack = false;
	while(true)
	{
		if(!backtrack && HasLChild(*x))
		{
			x = x->lc;
		}
		else{
			//�Ǵ��������������Ļ�����û��������
			//�����˼·����֮ǰ�ġ����������������Ժ�������������Ϊ�ա���һ�������������ǲ��ܸı������Ľṹ��������backtrack����ʾ
			//��ʱxһ��Ҫ��ʾΪ��������������ĸ��׽ڵ�
			visit(x->data);
			if(HasRChild(*x))
			{
				x = x->rc;
				//���￪ʼ��������ڵ㣬Ȼ���������������������Ҫ��backtrack�ر�
				//������رգ���ô�ڵ�һ�λ��ݺ����е��������޷�������������
				backtrack = false;
			}
			else{
				//������Ҫ���x�ĺ�̣���Ϊ��ǰһ����ĳһ��������������ϣ�ԭ������ջ��¼�ģ�����ʹ��succ���������
				if(!(x = x->succ()))	break;
				//backtrack������˵����ǰջ��Ԫ�ص��������Ѿ���������ϣ�Ҳ�������ӽڵ�����������������
				backtrack = true;
			}
		}

	}
}


//�������

//����û�������������������
//�������Ҳ���Ժ�ǰ����һ������ȷ���ı���˳�������������������Ҫ��������������ĵ�һ���ڵ�
//����Ҫ�Ļ���Ҫ��ջ��ȷ����������ĺ������˳��
template<typename T>

static void gotoHLVFL(Stack<BinNodePosi(T)> &s)
{
	//�Զ����£��������ջ���ڵ�
	//���ѭ��������������xΪNULL����ʱֻ��˵��x��ĳ���ڵ�����ӽڵ�=��x�ĸ��׽ڵ��û������Ҳû���Һ���=��x�ĸ��׽ڵ㼴Ϊ����Ҫ�ҵ���������ĺ�������ĵ�һ���ڵ�
	while(BinNodePosi(T) x = s.top())
	{
		if(x->lc)
		{
			//������
			//��ʱע��Ҫ�Ȱ��Һ�����ջ������еĻ�������Ϊ��������Ĺ����У��������������ڸ��ڵ������
			if(x->rc)	s.push(x->rc);
			s.push(x->lc);
		}
		else
		{
			//û���ӣ���ô������
			s.push(x->rc);
		}
	}
	//��ջ����NULL����
	s.pop();
}


template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> s;
	//����Ҫע����x
	if(x)
		s.push(x);
	while(!s.empty())
	{
		//���ջ��Ԫ�غ͸ճ�ս��Ԫ���Ǹ��ӹ�ϵ����ôֻ��˵��ջ��Ԫ�����ڵ������ѱ������꣬ջ��Ԫ�ظó�ջ
		//����ջ��Ԫ��һ���Ǹճ�ջ��Ԫ�ص����ֵܣ���ʱӦ�ñ������ջ��Ԫ�����ڵ�����
		//����һ������������һ��ʼx�Ǹ��ڵ㣬��ʱx��ջ����Ԫ����һ���ġ���Ȼ������ջ��Ԫ����x�ĸ��׽ڵ������ϵ��������Ҫ����
		if(s.top() != x->parent)
		{
			//������ʱӦ�ÿ�ʼ���������������ȷ���ڵ�ı���˳��
			gotoHLVFL(s);
		}
		x = s.pop();
		visit(x->data);
	}
}

//�ܽ�һ�£�ǰ�����������������ͨ·���϶��·��ʸ��ڵ㣬ֱ��ĳ�����ڵ�û�����ӣ�Ȼ�����¶�����ͬ����ʽ����ÿ�����ڵ��������
//���������������������ͨ·�����Ǹ�û�����ӵ������ӽڵ㣬Ȼ�����¶��ϵ���������ͨ·�ȱ������ڵ㣬�ٱ���������
//����������ǴӸ��ڵ㿪ʼ�����ҵ�������ɼ�Ҷ�ӽڵ㣬Ȼ����ջ�Ĵ洢˳�򣬶�ÿһ���ڵ㿴�Ǵ�ӡ���Ǳ�����������


//����ǲ�α�����Ӧ��д��BinNode��ʵ�����
template <typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit)
{
	//��������α����㷨
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