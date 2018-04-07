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
