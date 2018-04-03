#include "ListNode.h"
#include "stdafx.h"

template <typename T>
class List{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) tailer;

protected:
	//�б���ʱ�ĳ�ʼ��
	void init();
	//������нڵ�
	int clear();
	//�����б�����λ��p���n�Ϊʲô����void��
	void copyNodes(ListNodePosi(T), int);
	//�鲢
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
	//�Դ�p��ʼ������n���ڵ�鲢����
	void mergeSort(ListNodePosi(T)&, int);
	//�Դ�p��ʼ������n���ڵ�ѡ������
	void selectionSort(ListNodePosi(T), int);
	//�Դ�p��ʼ������n���ڵ��������
	void insertionSort(ListNodePosi(T), int);

public:
	//���캯��
	List() {init();}
	//���帴���б�L
	List(List<T> const& L);
	//�����б�L���Ե�r�����n��
	List(List<T> const &L, Rank r, int n);
	//�����б�����λ��p���n��
	List(ListNodePosi(T) p, int n);
	~List();
	//ֻ�����ʽӿ�
	Rank size() const {return _size;}
	//�п�
	bool empty()const {return _size == 0;}
	//���أ�֧��ѭ�ȷ���
	T &operator[](Rank r)const;
	//�׽ڵ�λ��
	ListNodePosi(T) first() const {return header->succ;}
	//ĩ�ڵ�λ��
	ListNodePosi(T) last() const {return tailer->pred;}
	//�ж�λ��p�Ƿ����Ϸ��������Ƿ�NULL��ͷ��β
	bool valid(ListNodePosi(T) p)
	{return p && (tailer != p) && header != p;}
	//�ж��б��Ƿ��Ѿ�����
	int disordered()const;
	//�����б����
	ListNodePosi(T) find(T const& e)const
	{return find(e, _size, tailer);}
	//����������ң���ǰ���vectorһ�����Ӻ���ǰ��
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p)const;
	//�����б�Ĳ���
	ListNodePosi(T) search(T const &e)const
	{return search(e, _size, tailer);}
	//�����������
	ListNodePosi(T) search(T const&e, int n, ListNodePosi(T) p)const;
	//��p����n-1�������ѡ�������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	//���������
	ListNodePosi(T) selectMax()
	{return selectMax(header->succ, _size);}

	//��д���ʽӿ�
	//��e�����׽ڵ����
	ListNodePosi(T) insertAsFirst(T const&e);
	//��e����ĩ�ڵ����
	ListNodePosi(T) insertAsLast(T const &e);
	//��e����p�ĺ�̲���
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e);
	//��e����p��ǰ������
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e);
	//ɾ���Ϸ�λ��p���Ľڵ㣬���ر�ɾ���ڵ�
	T remove(ListNodePosi(T) p);
	//ȫ�б�鲢
	void merge(List<T> &L)
	{merge(first(), size, L, L.first(), L._size);}
	//�б���������
	void sort(ListNodePosi(T) p, int n);
	//�б���������
	void sort()
	{sort(first(), _size);}
	//����ȥ��
	int deduplicate();
	//����ȥ��
	int uniquify();
	//ǰ����
	void reverse();

	//����
	void traverse(void(*) (T &));
	template <typename VST>
	void traverse(VST &);
};

template <typename T>
void List<T>::init()
{
	//header��tailer����ָ��
	header = new ListNode();
	tailer = new ListNode();
	header->succ = tailer;
	header->pred = NULL;
	tailer->pred = header;
	tailer->succ = NULL;
	//��Ҫ���ǳ�ʼ��size
	_size = 0;
}
//�ȵ�λ�õ�ת��
//Ч�ʲ�����������������������ҪO(n)�ĸ��Ӷȣ��������԰���r��size/2�Ĺ�ϵѡ����ҵ�˳��
template <typename T>
T &List<T>::operator[](Rank r)const
{
	ListNodePosi(T) p = first();
	while(r-- && p != tailer)
		p = p->succ;
	//�������е�ֵ������������ַ
	return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p)const
{
	while(n-- && p->pred != header)
	{
		//ע����ҷ�Χ������p�Լ�
		p = p ->pred;
		if(p->data == e)
			return p;
	}
	return NULL;
}
//����
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e)
{
	//����Ҫ��ô�鷳������ListNode���insertas����
	//ע��ά��_size
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}

//����
template <typename T>
//�����б�����λ��p���n��
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	//p�Ϸ�����������n-1�����̽ڵ�
	init();
	//������Ҫ���
	while(n--)
	{
		insertAsLast(p->data);
		p = p ->succ;
	}
}

//���췽��
//p��ʼ����n��
template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}
//���������б�
template<typename T>
List<T>::List(List<T> const &L)
{
	copyNodes(L.first(), L._size);
}
//����L�ĵ�r�ʼ��n��
template<typename T>
List<T>::List(List<T> const &L, int r, int n)
{
	copyNodes(L[r], n);
}

//ɾ��
template<typename T> T List<T>::remove(ListNodePosi(T) p)
{
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	//��Ҫ����ά��size
	_size--;
	T e = p->data;
	delete p;
	return e;
}

//����
template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete tailer;
}
//���������ʣͷβ�ڵ�
template<typename T>
int List<T>::clear()
{
	int oldsize = _size;
	//����ɾ���׽ڵ㼴��
	while(_size)
		remove(header->succ);
	return oldsize;
}

//Ψһ��
template<typename T>
int List<T>::deduplicate()
{
	if(_size < 2)	return;
	ListNodePosi(T) p = header->succ;
	int oldsize = _size;
	int length = 0;
	while(p != tailer)
	{
		ListNodePosi(T) q = NULL;
		if(q = find(p->data, length, p))
		{
			remove(q);
		}
		else
		{
			length++;
		}
		p = p ->succ;
	}
	return oldsize - _size;
}

//����
template<typename T>
void List<T>::traverse(void (*visit)(T&))
{
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p->succ)
		visit(p->data);
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit)
{
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p ->succ)
		visit(p->data);
}