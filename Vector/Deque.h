#pragma once
#include "List.h"
#include "stdafx.h"

template <typename T>
class Deque:public List<T>{
public:
	T &front();	//��ȡ��Ԫ��
	T &rear();	//��ȡĩԪ��
	void insertFront(T const &e);	//��Ԫ��e��������ǰ��
	void insertRear(T const &e);	//��Ԫ��e��������ĩ��
	T removeFront();				//ɾ�����е���Ԫ��
	T removeRear();					//ɾ�����е�ĩԪ��
};
//����涨������ǰ���ǿ���tail�ڵ�ģ����к���ǿ���header�ڵ��
template<typename T>
T& Deque<T>::front()
{
	return last()->data;
}

template<typename T>
T& Deque<T>::rear()
{
	return first()->data;
}
//�����׾ʹ����д��ջ��
template<typename T>
void Deque<T>::insertFront(T const &e)
{
	insertAsLast(e);
}

template<typename T>
void Deque<T>::insertRear(T const &e)
{
	insertAsFirst(e);
}

template<typename T>
T removeFront()
{
	remove(last());
}

template<typename T>
T removeRear()
{
	remove(first());
}

