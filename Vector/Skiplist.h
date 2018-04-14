#pragma once
#include "List.h"
#include "Entry.h"
#include "Quadlist.h"
#include "Dictionary.h"

template <typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
	bool skipSearch(
			ListNode<Quadlist<Entry<K, V>>*>* &qlist,
			QuadlistNode<Entry<K, V>>* &p,
			K &k
		);
public:
	//�ײ�Quadlist�Ĺ�ģ
	int size() const
	{
		return empty() ? 0 : last()->data->size();
	}
	//���
	int level()
	{
		return List::size();
	}
	//Skiplist��������ظ����ʱ�Ȼ�ɹ�
	bool put(K, V);
	//��ȡ
	V *get(K k);
	//ɾ��
	bool remove(K k);
};

//����ת���в鳭�ؼ���k�ľ������
template<typename K, typename V>
V *Skiplist<K, V>::get(K k)
{
	if(empty())	return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>> *p = qlist->data->first();
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL;
}

/********************************************************************

* Skiplist ���������㷨�����ڲ����ã�

* ��ڣ�qlistΪ�����б�pΪqlist���׽ڵ�

* ���ڣ����ɹ���pΪ���йؼ����������Ķ����ڵ㣬qlistΪp�����б�
		����pΪ�������Ļ�����������Ӧ�ڲ�����k���������ҹؼ��룬qlistΪ��

* Լ���������������ʱ����������ȡ�����

********************************************************************/


template <typename K, typename V>
bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist,
	QuadlistNode<Entry<K, V>>* &p,
	K &k
	)
{
	while(true)
	{
		//��ÿһ�㣿
		//header��һ��Ҫ������
		//���ﲻ��������header
		while( p->succ && (p->entry.key <= k))
		{
			p = p ->succ;
		}
		//��ʱ����һ��
		p = p->pred;
		//����
		//p->pred��֤�����ﲻ����Ϊheader��keyΪ0������
		if(p->pred && (k == p->entry.key))
			return true;
		//����ת����һ��
		qlist = qlist->succ;
		//���ѵ���͸�ײ㣬����ζ��ʧ��
		if(!qlist->succ)	return false;

		p = (p->pred) ? p->below : qlist->data->first();
	}
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
	//��ת����������㷨
	Entry<K, V> e = Entry<K, V>(k, v);
	if(empty())	
		insertAsFirst(new Quadlist<Entry<K, V>>);
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>> *p = qlist->data->first();
	if(skipSearch(qlist, p, k))
		while(p->below)	
			p = p->below;
	qlist = last();
	QuadlistNode<Entry<K, V>>*b = qlist->data->insertAfterAbove(e, p);

	while(rand() & 1)
	{
		//�ҳ������ڴ˸߶ȵ����ǰ��
		while(qlist->data->valid(p) && !p->above)
			p = p->pred;
		if(!qlist->data->valid(p))
		{
			//����ǰ����header
			if(qlist == first())
			{
				//�ҵ�ǰ������㣬����ζ�ű������ȴ����µ�һ�㣬Ȼ��pת����һ��Skiplist��header
				insertAsFirst(new Quadlist<Entry<K, V>>);
			}
			p = qlist->pred->data->first()->pred;
		}
		else
			p = p->above;
		qlist = qlist->pred;
		b = qlist->data->insertAfterAbove(e, p, b);
	}
	return true;
}

//ɾ��
template<typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
	//���������
	if(empty())	return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>> *p = qlist->data->first();

	if(!skipSearch(qlist, p, k))
		return false;
	do{
		QuadlistNode<Entry<K, V>>* lower = p->below;
		qlist->data->remove(p);
		p = lower;
		qlist = qlist->succ;
	}while(qlist->succ);
	//��ס���������
	while(!empty() && first()->data->empty())
		//��������Ѿ����������Ķ���Quadlist
		List::remove(first());
	return true;
}