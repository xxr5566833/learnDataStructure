#include "BTNode.h"

template<typename T>
class BTree{
public:
	//��ŵĹؼ�����������֮ǰ�Ķ�������_size������
	int _size;
	//�״Σ�����Ϊ3��������ʱָ����һ�㲻���޸�
	int _order;
	BTNodePosi(T) _root;
	//��BSTһ����search�����ʵķǿյĽ��λ��
	BTNodePosi(T) _hot;
	//����������ķ��Ѵ������֮ǰ����ѧ��
	void solveOverflow(BTNodePosi(T));
	//��ɾ���������ĺϲ�����
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
		//�ҵ�������e�����ؼ���
		Rank r = v->key.search(e);
		if((0 <= r) && (e == v->key[r]))
			return v;
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL;
	//ʧ�ܾͷ���NULL
}

template<typename T>
bool BTree<T>::insert(const T &e)
{
	BTNodePosi(T) v = search(e);
	if(v)
		return false;

	Rank r = _hot->key.search(e);
	_hot->key.insert(r + 1, e);
	//��ʱ_hot����һ���Ȼ����ײ㣬������ֱ�Ӳ���ؼ���ͷ�֧����
	_hot->child.insert(r + 2, NULL);
	_size++;
	//���б�Ҫ����Ҫ������
	solveOverflow(_hot);
	return true;
}
template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	//ע���֧���ȹؼ�������1���ؼ����ؼ����_order�Ĺ�ϵ
	if(_order >= v->child.size())
		return ;
	Rank s = _order >> 1;
	BTNodePosi(T) u = new BTNode<T>();
	//��RankΪs�Ľ����Ҳ�ؼ���Ž�һ���µĽ��
	for(Rank j = 0 ; j < _order - s - 1 ; j++)
	{
		u->child.insert(j, v->child.remove(s + 1));
		u->key.insert(j, v->key.remove(s + 1));
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);
	//��Ϊ��ʼ��ʱ0���ؼ��룬1����֧NULL����child[0]������Ϊ�ж�child�Ƿ�Ϊ�յ�����
	//������Ҫͨ��debug�����������������
	if(u->child[0])
		for(Rank j = 0 ; j < _order - s ; j++)
			u->child[j]->parent = u;
	BTNodePosi(T) p = v->parent;
	if(!p)
	{
		//˵��ԭ��v���Ǹ��ڵ�
		_root = p = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}
	//p��ָ��u��ָ�����
	Rank r = 1 + p->key.search(v->key[0]);
	//��s�ŵ�p��
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
		//v��Ҷ�ӣ���e�ĺ�̱�Ȼ����ĳ��Ҷ���
		BTNodePosi(T) u = v->child[r + 1];
		while(u->child[0])
			u = u->child[0];
		//������Ϊ���ҳ�e�ĺ��
		//�Ѻ�̵����ݸ��ǵ�ԭ��Ҫɾ���Ĺؼ�������ݣ�Ȼ��ת��ΪҪɾ�������̣�һ����Ҷ�ӽڵ㣩������
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
		//ֻ�������������ؼ���ʱ����Ҫ�����紦��
		if(!v->key.size() && v->child[0]){
			//��Ϊ������v�Ѿ������ؼ��룬ȴ��Ψһ�ķǿյĺ���
			//�����ؼ��룬��ô����û���κκ���Ҳ����ֻ��һ������
			_root = v->child[0];
			_root->parent = NULL;
			v->child[0] = NULL;
			//�ͷ�v
		}
		return ;
	}
	Rank r = 0;
	while(p->child[r] != v)
		r++;
	//ȷ��v��p�ĵ�r������
	//��ʱv���ܲ����ؼ��룬�ʲ���ͨ���ؼ�����ң���
	//��ʵ���˺���ָ����е�����Ҳ����ֱ����find�ӿڶ�λ

	// ������ʵ�ָ������
	//���1�������ֵܽ�ؼ���
	if(r > 0){
		//���ֵܱ�Ȼ����
		BTNodePosi(T) ls = p->child[r - 1];
		//ע��child�ĳ��ȱ�key����1
		if((_order + 1) / 2 < ls->child.size()){
			//��ʱ���ֵܵ������㹻
			//p�Ƚ�һ����v
			v->key.insert(0, p->key[r - 1]);
			//���ֵܵ����ؼ���ת��p
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
			//ͬʱls�����Ҳຢ�ӹ��̸�v�������Ҫ����
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
			if(v->child[0]){
				v->child[0]->parent = v;
			}
			//���ʣ������Ļ���child[0]��null������ζ��֮���child����null���߸�����������һ�
			return ;
			//�൱����������
		}
	}
	//�����ֵܽ�ؼ���
	if(p->child.size() - 1 > r){
		//��v����p�����һ�����ӣ���ô���ֵܱ�Ȼ����
		BTNodePosi(T) rs = p->child[r + 1];
		if((_order + 1) / 2 < rs->child.size()){
			//p�����Ӧλ���ϵĹؼ����v��Ϊ���ؼ���
			v->key.insert(v->key.size(), p->key[r]);
			p->key[r] = rs->key.remove(0);
			v->child.insert(v->child.size(), rs->child.remove(0));
			//��Ϊv�����Ҳຢ��
			if(v->child[v->child.size() - 1]){
				//�޸�֮ǰ���ӵĸ���
				v->child[v->child.size() - 1]->parent = v;
			}
			return ;
		}
	}
	//�����ֵ�ҪôΪ�գ�Ҫô̫��
	if(r > 0){
		BTNodePosi(T) ls = p->child[r - 1];
		ls->key.insert(ls->key.size(), p->key.remove(r - 1));
		p->child.remove(r);
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if(ls->child[ls->child.size() - 1]){
			ls->child[ls->child.size() - 1]->parent = ls;
		}
		//vʣ��Ĺؼ���ͺ��ӣ�����ת��ls
		while(!v->key.empty()){
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if(ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		//�ͷ�v����ʱv����key��child�Ѿ��������ֵ�

	}
	else{
		//�����ֵܺϲ��������������ֵ�ͬʱ�����ڣ�
		//�йؼ��룬 ��ô����ؼ������ߵ�child��Ӧ�ô��ڣ�
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
		//�ͷ�v
	}
	//�ݹ����
	solveUnderflow(p);
	return ;
}

