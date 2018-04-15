#pragma once
#include "Dictionary.h"
#include "Bitmap.h"
#include "prime.h"
#include "stdafx.h"
template<typename K, typename, T>
class HashTable:public Dictionary<K, V>
{
private:
	//桶数组，存放词条的指针
	Entry<K, V> **ht;
	//桶数组容量
	int M;
	//词条容量
	int N;
	//懒惰删除标记
	Bitmap *lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	//沿关键码k对应的查找链，找到词条匹配的桶
	int probe4Hit(const K& k);
	//沿关键码k对应的查找链，找到首个可用空桶
	int probe4Free(const K& k);
	//重散列算法：扩充桶数组，保证装填因子在警戒线以下
	void rehash();
public:
	//创建一个容量不小于c的散列表
	HashTable(int c = 5);
	//释放桶数组及其中各非空元素所指向的词条
	~HashTable();
	//当前词条数目
	int size() const
	{
		return N;
	}
	//插入（因为禁止词条雷同，可能失败）
	bool put(K, V);
	//读取
	V *get(K k);
	//删除
	bool remove(K k);
};

//初始化
template<typename K, typename V>
HashTable<K, V>::HashTable(int c)
{
	M = Eratosthenes(c);
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);

	lazyRemoval = new Bitmap(M);
}

//析构
template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	for(int i = 0 ; i < M ; i++)
	{
		if(ht[i])
			delete ht[i];
	}
	delete[] ht;
	
}

//散列表词条查找算法
template<typename K, typename V>
V *HashTable<K, V>::get(K k)
{
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r] -> value) : NULL;
}

//probe4Hit
/***************************************

* 沿关键码k对应的查找链，找到与之匹配的桶，供查找和删除词条时调用

* 这里以线性试探策略为例

***************************************/
template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazyRemoved(r)))
		r = (r + 1) % M;
	return r;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(K k)
{
	int r = probe4Hit(k);
	if(!ht[r])
	{
		return false;
	}
	delete ht[r];
	ht[r] = NULL;
	markAsRemoved(r);
	N--;
	return true;
}


template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v)
{
	if(ht[probe4Hit(k)])	return false;
	//success only if load factor is controlled properly
	int r = probe4Free(k);
	ht[r] = new Entry<K, V>(k ,v);
	++N;
	if(N * 2 > M)
		rehash();
}

template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;
	while(ht[r])
		r = (r + 1) % M;
	return r;
}