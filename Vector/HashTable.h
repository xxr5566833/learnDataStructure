#pragma once
#include "Dictionary.h"
#include "Bitmap.h"
#include "prime.h"
#include "stdafx.h"
template<typename K, typename, T>
class HashTable:public Dictionary<K, V>
{
private:
	//Ͱ���飬��Ŵ�����ָ��
	Entry<K, V> **ht;
	//Ͱ��������
	int M;
	//��������
	int N;
	//����ɾ�����
	Bitmap *lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	//�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
	int probe4Hit(const K& k);
	//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
	int probe4Free(const K& k);
	//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
	void rehash();
public:
	//����һ��������С��c��ɢ�б�
	HashTable(int c = 5);
	//�ͷ�Ͱ���鼰���и��ǿ�Ԫ����ָ��Ĵ���
	~HashTable();
	//��ǰ������Ŀ
	int size() const
	{
		return N;
	}
	//���루��Ϊ��ֹ������ͬ������ʧ�ܣ�
	bool put(K, V);
	//��ȡ
	V *get(K k);
	//ɾ��
	bool remove(K k);
};

//��ʼ��
template<typename K, typename V>
HashTable<K, V>::HashTable(int c)
{
	M = Eratosthenes(c);
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);

	lazyRemoval = new Bitmap(M);
}

//����
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

//ɢ�б���������㷨
template<typename K, typename V>
V *HashTable<K, V>::get(K k)
{
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r] -> value) : NULL;
}

//probe4Hit
/***************************************

* �عؼ���k��Ӧ�Ĳ��������ҵ���֮ƥ���Ͱ�������Һ�ɾ������ʱ����

* ������������̽����Ϊ��

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