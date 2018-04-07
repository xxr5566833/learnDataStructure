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
