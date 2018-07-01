#include "BST.h"
template<typename T> class RedBlack:public BST<T>{

public:
	//˫������
	void solveDoubleRed(BinNodePosi(T) x);
	//˫������
	void solveDoubleBlack(BinNodePosi(T) x);
	//���½ڵ�x�ĸ߶�
	int updateHeight(BinNodePosi(T) x);

	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

// �������غ궨��
#define IsBlack (!(p) || (RB_BLACK == (p)->color))
//�Ǻڼ���
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x)( \
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
)

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x){
	x->height = max(stature(x->lc), stature(x->rc));
	// ������height ���� height++ return�Ķ���height
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T &e){
	BinNodePosi(T) &x = search(e);
	if(x)
		return x;
	//������ڵ�x:��_hotΪ�����ڸ߶�ע������Ϊ-1
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
	//���� x�ĸ���p�ش���
	BinNodePosi(T) p = x->parent;
	//pΪ�ڣ���ô��Ȼ������ֹ����
	if(IsBlack(p))
		return ;
	//����pΪ�죬��x���游��Ȼ���ڣ��ұ�Ϊ��ɫ
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);
	if(IsBlack(u)){
		//uΪ��ɫ����NULL
		//x��pͬ��ʱ
		if(IsLChild(*x) == IsLChild(*p))
			p->color = RB_BLACK;
		else
			//���
			x->color = RB_BLACK;
		g->color = RB_RED;
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}
	else{
		//uΪ��ɫ
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
	//����ڵ�ɾ���ˣ���ôֱ�ӷ���true
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
	//��ʱ��Ҫ���
	solveDoubleBlack(r);
	return true;
}

// ���x�뱻������Ľ�㶼�Ǻ�ɫ
template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r){
	BinNodePosi(T) p = r ? r->parent : _hot;
	if(!p)
		return ;

	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;
	if(IsBlack(s)){
		//s�Ǻ�ɫ
		//����֮ǰ�ķ������ȼ��s��û�к�ɫ���
		BinNodePosi(T) t = NULL;
		//s�ĺ캢�ӣ������ҽԺ죬�������ȣ��Ժ�ʱΪNULL
		if(IsRed(s->rc))
			t = s->rc;
		if(IsRed(s->lc))
			t = s->lc;
		if(t){
			//�к캢�ӣ�����BB-1ģʽ
			//����ԭ�������ڵ�p����ɫ������t���丸�ף��游ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
			//ע����������tΪ׼������ת
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
			//sû�к캢�ӣ���ʱ����p����ɫ
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
		//BB-3 �ֵ�sΪ�죬��ת+Ⱦɫ
		s->color = RB_BLACK;
		p->color = RB_RED;
		//t��rotateAt�Ĳ���������Ҫȡ��s�����s������ͬ��λ���ϵĺ���
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
		_hot = p;
		//��t���丸�ף��游��ƽ�����
		FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);
		//�����޸������Ǵ�ʱp�Ѿ��Ǻ�ɫ�ˣ�����ֻ����BB-1 ������ BB-2R
	}
}