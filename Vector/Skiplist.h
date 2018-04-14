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
	//底层Quadlist的规模
	int size() const
	{
		return empty() ? 0 : last()->data->size();
	}
	//层高
	int level()
	{
		return List::size();
	}
	//Skiplist允许词条重复，故必然成功
	bool put(K, V);
	//读取
	V *get(K k);
	//删除
	bool remove(K k);
};

//在跳转表中查抄关键码k的具体过程
template<typename K, typename V>
V *Skiplist<K, V>::get(K k)
{
	if(empty())	return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>> *p = qlist->data->first();
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL;
}

/********************************************************************

* Skiplist 词条查找算法（供内部调用）

* 入口：qlist为顶层列表，p为qlist的首节点

* 出口：若成功，p为命中关键码所属塔的顶部节点，qlist为p所属列表
		否则，p为所属塔的基座，该塔对应于不大于k的最大且最靠右关键码，qlist为空

* 约定：多个词条命中时，沿四联表取最靠后者

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
		//在每一层？
		//header是一定要跳过的
		//这里不可能遇到header
		while( p->succ && (p->entry.key <= k))
		{
			p = p ->succ;
		}
		//此时倒退一步
		p = p->pred;
		//命中
		//p->pred保证了这里不会因为header的key为0而返回
		if(p->pred && (k == p->entry.key))
			return true;
		//否则转入下一层
		qlist = qlist->succ;
		//若已到穿透底层，则意味着失败
		if(!qlist->succ)	return false;

		p = (p->pred) ? p->below : qlist->data->first();
	}
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
	//跳转表词条插入算法
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
		//找出不低于此高度的最近前驱
		while(qlist->data->valid(p) && !p->above)
			p = p->pred;
		if(!qlist->data->valid(p))
		{
			//若该前驱是header
			if(qlist == first())
			{
				//且当前已是最顶层，则意味着必须首先创建新的一层，然后将p转至上一层Skiplist的header
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

//删除
template<typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
	//沿着塔拆除
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
	//记住清除空链表
	while(!empty() && first()->data->empty())
		//清除可能已经不含词条的顶层Quadlist
		List::remove(first());
	return true;
}