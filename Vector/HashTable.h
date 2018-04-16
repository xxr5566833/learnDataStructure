#pragma once
#include "Dictionary.h"
#include "Bitmap.h"
#include "prime.h"
#include "Entry.h"
#include "stdafx.h"
template<typename K, typename V>
class HashTable:public Dictionary<K, V>
{
private:
	Entry<K, V> **ht;
	int M;
	int N;
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
	while((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
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

/*
* 重散列算法：装填因子过大时，采用“逐一取出再插入”的朴素策略，对桶数组扩容
* 不可简单地通过memcpy将原桶数组复制到新桶数组（比如前端），否则存在两个问题：
* 1.会继承原有冲突；2.可能导致查找链在后端断裂——即使为所有扩充桶设置懒惰删除标志也无济于事
*/

template<typename K, typename V>
void HashTable<K, V>::rehash()
{
	int old_capacity = M;
	Entry<K, V> **old_ht = ht;
	M = Eratosthenes(2 * M);
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);
	delete lazyRemoval;
	lazyRemoval = new Bitmap(M);
	for(int i = 0 ; i < old_capacity ; i++)
	{
		if(old_ht[i])
		{
			put(old_ht[i]->key, old_ht[i]->value);
		}
	}
	delete[] old_ht;
}

static size_t hashCode(char c)
{
	return (size_t)c;
}

static size_t hashCode(int k)
{
	return (size_t) k;
}

static size_t hashCode(long long i)
{
	return (size_t) ((i >> 32) + (int) i);
}
//生成字符串的循环移位散列码
static size_t hashCode(char s[])
{
	int h = 0;
	for(size_t n = strlen(s), i = 0 ; i < n ; i++)
	{
		h = (h << 5) | (h >> 27);
		h += (int)s[i];
	}
	return (size_t) h;
}

//循环左移五位是实验统计得出的最佳值