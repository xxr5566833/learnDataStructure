#include "BST.h"

template<typename T> 
class Splay : public BST<T>
{
public:
	//���ڵ�v��չ����
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
		//������ԭ�������游
		BinNodePosi(T) gg = g->parent;
		//��������֮ǰ��rotateAtһ��������v p g�Ĳ�ͬ���ѡ��ͬ��ת����
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
	//˫����չ�����󣬱���gΪNULL����������v����ȵ���ż�Բ�ȷ�������Կ���p��Ϊ�գ�����һ����Ҫ���
	if(p = v->parent)
	{
		//��ʱpӦ���Ѿ���V��parentΪʲôif��Ҫ����һ��
		if(IsLChild(*v))
		{
			//��Ҫ������ת
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
	//����һ��������v��parent������while���������Ϊ����whileһ��ʼ���ж�����ȷ��
	v->parent = NULL;
	return v;
}

template<typename T>
BinNodePosi(T) &Splay<T>::search(const T &e)
{
	BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
	_root = splay(p ? p : _hot);
	return _root;
	//ע���_root������
}


//���ﲻ��Ҫ��search���ٲ��룬����չ����Ϊ��ʱ��search�Ѿ�����չ�Ĺ��ܼ�����
//����ֱ������չ��Ľ���Ļ����Ͻ����޸�
template<typename T>
BinNodePosi(T) Splay<T>::insert(const T &e)
{
	if(!_root)
	{
		//�˻��������Ϊ��
		_size ++;
		return _root = new BinNode<T>(e);
	}
	//����Ѿ����ڣ���ô����_root��ʵ���Ƿ���������Ϊe���Ǹ��ڵ�
	if(e == search(e)->data)
		return _root;
	_size ++;
	BinNodePosi(T) t = _root;
	//����������С�ڵ���7��ָ������ɾֲ��ع�
	if(_root->data < e)
	{
		//��ʱӦ�����½ڵ���Ϊ���ڵ㣬����ԭ����_root��Ϊ����������
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
	//����չ����ɾ���ؼ���e
	if(!_root || (e != search(e)->data))
		return false;
	BinNodePosi(T) w = _root;
	if(!HasLChild(*_root)){
		//û������������ôֱ��ɾ��
		_root = _root->rc;
		if(_root)
			_root->parent = NULL;
	}
	else if(!HasRChild(*_root))
	{
		//û���������������remove֮ǰ�Ĵ���������
		_root = _root->lc;
		if(_root)
			_root->parent = NULL;
	}
	else{
		//��������ͬʱ����
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = NULL;
		_root->lc = NULL;

		_root = _root->rc;
		_root->parent = NULL;

		search(w->data);
		/*����ע�⣺�������ж��Ǳ�w->data������ݣ�������search�е�searchIn�Ĳ��ҷ�����
		һ������ʧ�ܣ�_hot�ᱻ����Ϊ���һ�η��ʵķǿս�㣬������ɿսڵ�һ����w�ĺ�̣�
		ԭ��w���������������������ÿһ����С������searchIn�Ĳ��Ҳ��ԣ�������������ͨ·���в���
		ֱ���ҵ��������е���С��㣬��w�ĺ�̽ڵ�
		ͬʱ������չ�ĵȼ��ԣ��������̱���չΪ���ڵ�ʱ������һ��û�����ӽڵ�ģ���Ϊ���Ѿ�����С��
		*/
		_root->lc = lTree;
		lTree->parent = _root;
	}
	//�ͷŽڵ�
	_size --;
	//�����ڵ���splayʱ�����˸߶ȣ��о�����Ը߶ȵĸ����е��ң�������չ��Ҳ�����߶�
	if(_root)
		updateHeight(_root);
	return true;
}