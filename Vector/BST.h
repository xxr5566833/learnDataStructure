#include "BinTree.h"

template<typename T>
class BST:public BinTree<T>{
public:
	BinNodePosi(T) _hot;
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);//��x���丸�ף��游��ͳһ��ת����

	virtual BinNodePosi(T) &search(const T &e);
	virtual BinNodePosi(T) insert(const T &e);
	virtual bool remove(const T &e);
};

//����vΪ�����������в��ҹؼ���e
template<typename T>
static BinNodePosi(T) &searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot)
{
	//�ݹ�����ڽڵ�v��������ͨ��ڵ㴦���У�
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
	//ע�����ｫ_hot�ÿ�
	return searchIn(_root, e, _hot = NULL);
	//����Ŀ��ڵ�λ�õ����ã��Ա�������룬ɾ���Ȳ���
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
	//ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
	BinNodePosi(T) w = x;
	//ʵ�ʱ�ɾ���ڵ�Ľ�����
	BinNodePosi(T) succ = NULL;
	if(!HasLChild(*x))
		succ = x = x->rc;
	else if(!HasRChild(*x))
		succ = x = x->lc;
	else{
		//���һֱ���ú��������ԭ���Ľ�㣬������ڶ��ɾ�������ġ����㡱�������������ʹ�������ѡ���̻�����ǰ��������
		if(rand() % 2)
		{
			w = w->succ();
			swap(x->data, w->data);
			BinNodePosi(T) u = w->parent;
			//��仰��Ҫ���һ�£�
			//���u��x��˵��֮ǰx�ĺ�̾����������ӽڵ㣬��ô��ʱ�������̵����ӽڵ��滻�����̵�λ�ã�ͬʱ���ú�̵ĸ��׽ڵ������Ĺ�ϵ
			//���u����x����ô˵��x�ĺ����x���������е������ӽڵ㣬��һ����u�����ӽڵ㣬Ȼ����ͬ���Ĳ�������
			//����Ҳ���㷨������������˼·��࣬������Ϊ����ֱ�ӽ��������������Դ����˲����������ط���һ��
			((u == x) ? u->rc : u->lc) = succ = w->rc;
		}
		else{
			w = w->pred();
			swap(x->data, w->data);
			BinNodePosi(T) u = w->parent;
			//ǰ���ͺ������Ҳ����ͬ����Ҫ��ǰ���ڵ�һ��û��������������������Ҫʹ��w->lc
			((u == x) ? u->lc : u->rc) = succ = w->lc;
		}
		
	}
	//���涼�����ø��׽ڵ�ĶԺ��ӽڵ��lc/rc��ϵ��������Ҫ���ú��ӽڵ�Ը��׽ڵ��parent��ϵ
	hot = w->parent;
	if(succ)
		succ->parent = hot;
	return succ;
}

