#pragma once
#include "List.h"
#include "stdafx.h"

template <typename T>
class Deque:public List<T>{
public:
	T &front();	//读取首元素
	T &rear();	//读取末元素
	void insertFront(T const &e);	//将元素e插至队列前端
	void insertRear(T const &e);	//将元素e插至队列末端
	T removeFront();				//删除队列的首元素
	T removeRear();					//删除队列的末元素
};
//这里规定：队列前端是靠近tail节点的，队列后端是靠近header节点的
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
//很容易就错误的写成栈了
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

