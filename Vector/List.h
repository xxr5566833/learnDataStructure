#pragma once
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
	//����Ԫ�ذ�˳�������б�
	List(T *a, int size);
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
	header = new ListNode<T>();
	tailer = new ListNode<T>();
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

//�����ʼ���б�
template<typename T>
List<T>::List(T *a, int size)
{
	init();
	while(--size >= 0)
	{
		insertA(header, a[size]);
	}
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
	std::cout << "����" << std::endl;
	for(ListNodePosi(T) p = header->succ ; p != tailer ; p = p ->succ)
		visit(p->data);
	std::cout << std::endl;
	std::cout << "����" << std::endl;
	for(ListNodePosi(T) p = tailer->pred ; p != header ; p = p ->pred)
		visit(p->data);
}

template<typename T>
struct Print{
	virtual void operator()(T &e)
	{
		std::cout << e << " ";
	}
};

template<typename T>
void print(List<T> &L)
{
	L.traverse(Print<T>());
	std::cout << std::endl;
}


//�����б�
template<typename T>
int List<T>::uniquify()
{
	ListNodePosi(T) p = first(), q = first()->succ;
	int oldsize = _size;
	while(q != tailer)
	{
		if(p->data == q->data)
		{
			ListNodePosi(T) old = q;
			q = q->succ;
			remove(old);
		}
		else{
			p = p->succ;
			q = q->succ;
		}
	}
	return oldsize - _size;
}

//��p��n����ǰ�����ҵ�������e�������
template<typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p)const
{
	if(n <= 0)	return NULL;
	while(0 <= n--)
	{
		if((p = p->pred)->data <= e)	break;
	}
	return p;
}

//������
template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	switch(rand() % 3)
	{
	case 1: insertionSort(p, n);	break;
	case 2: selectionSort(p, n);	break;
	default: mergeSort(p, n);	break;
	}
}

//��������
template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
	//ʵ�����ƶ��ڵ�λ�þͿ�����
	if(n <= 1)	return ;
	ListNodePosi(T) q = p->succ;
	int length = 0;
	while(n--)
	{
		//����ע�����insertA����Ҫ����node��insertAs����ΪinsertA�ж�size��ά��
		insertA(search(p->data, length++, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

//ѡ������
//ð�������Ч��һ��ԭ�����ĳ��Ԫ�ر����Ծ���һ�ν����͵��������е�λ�ã�����ð������ȴһֱ����
//�����ѡ������������������Ҵδ�...
//ѡ�����������벻���еģ���������û�����������Ҫn2ʱ��
template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for(int i = 0 ; i < n ; i++)	tail = tail->succ;
	while(1 < n)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertB(tail, remove(max));
		n--;
		tail = tail->pred;
	}
}
//����ʼ��λ��p��n��Ԫ����ѡ�������
//�����������ø��߼������ݽṹʵ�֣���ôֻ��Ҫlognʱ��
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for(ListNodePosi(T) cur = p ; 1 < n ; n--)
	{
		//����Ҫ��֤�ȶ���
		if(cur->data >= max->data)
			max = cur;
		cur = cur->succ;
	}
	return max;
}
//�鲢����
//�鲢����������Ϊ�����������֮���������Ϊ�鲢����Ĺ����У�ֻ��Ҫ�õ���front()��ȡ���������е�ͷԪ�ؽ��бȽϢ�dequeue()ȡ����С��ͷԪ�آ�enqueue()���뵽���������
template<typename T>
void List<T>::merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;
	while(0 < m)
	{
		if(0 < n && p->data <= q->data)
		{
			//�����������q��������һ��p����ô�Ͳ��úϲ���
			if(q == (p = p->succ))	break;
			n--;
		}
		else{
			insertB(p, L.remove((q = q->succ)->pred));
			m--;

			
		}
	}
	p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T) &p, int n)
{
	if(n < 2)	return ;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	//����Ҳֻ����ѭ������ȡ�����м�ڵ���
	//������ﲻ�ܱ�֤���ֵľ����ԣ���ô����Ч�ʻ��½�
	for(int i = 0 ; i < m ; i++)	q = q->succ;
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

//reverse���ýӿڣ�֮ǰд����������ĵ��ã�������˫������ԭ��Ҳһ��
//��һ��
/*
template<typename T>
void List<T>::reverse()
{
	//������������������ֳ������֣�ǰһ�����Ѿ����ã���һ���ִ�����
	//���ں�һ���ֵ�ͷ���a��ǰһ���ֵ�ͷ���b�����ȴ���a��ԭ����̣�Ȼ����a�ĺ��ָ��b��b��ǰ��ָ��a��Ȼ���������a֮��Ľڵ�
	//#define�Ļ�����ֻ��ָʾǰһ����ָ�룬��һ���Ͳ�����Ϊ��ָ����
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = header->succ;
	while(q)
	{
		ListNodePosi(T) next = q->succ;
		p->pred = q;
		q->succ = p;
		p = q;
		q = next;
	}
	header->succ = NULL;
	tailer->pred = NULL;
	//����header��tailer
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;

}
*/

/*
template<typename T>
void List<T>::reverse()
{
	//��һ�鵹�ú��ָ�룬�ڶ��鵹��ǰ��ָ��
	//��ʵ����������������ȫ������һ�α����оͿ������
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = header->succ;
	while(q)
	{
		ListNodePosi(T) next = q->succ;
		q->succ = p;
		p = q;
		q = next;
	}
	header->succ = NULL;
	p = tailer;
	q = tailer->pred;
	while(q)
	{
		ListNodePosi(T) pre = q->pred;
		q->pred = p;
		p = q;
		q = pre;
	}
	tailer->pred = NULL;
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;
}
*/
/*
//�����֣������������
//�������������ܸ��ӣ���ôƵ���������ܵ��º�ʱ�Ĺ��죬��������
template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) p = header->succ;
	ListNodePosi(T) q = tailer->pred;
	for(int i = 0 ; i < _size >> 1 ; i++)
	{
		T temp = p->data;
		p->data = q->data;
		q->data = temp;
		p = p->succ;
		q = q->pred;
	}
	//ע�Ⱑ������������Ļ������Ҫ����ͷβ�ڵ�
}
*/
//ֱ�ӽ���ÿһ���ڵ��ǰ���ͺ��ָ��Ϳ����˰���
template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) p = header;
	for(p ; p ; p = p->pred)
	{
		ListNodePosi(T) temp = p ->succ;
		p->succ = p->pred;
		p->pred = temp;
	}
	ListNodePosi(T) temp = header;
	header = tailer;
	tailer = temp;
}

//Josephus�����⣬���֣�һ����ѭ������ʵ�֣���һ����ʹ�õݹ�