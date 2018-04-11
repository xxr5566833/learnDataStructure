#pragma once
#include "stdafx.h"
#include "List.h"
#include "Stack.h"
#include "ListNode.h"
template <typename T>
class Queue:public List<T>{
public:
	void enqueue(T const &e)
	{
		insertAsLast(e);
	}
	T dequeue()
	{
		return remove(first());
	}
	T &front()
	{
		return first()->data;
	}
	void reverse();
};

//���з���ģ��
struct Customer
{
	//��������
	int window;
	//����ʱ��
	unsigned int time;
};

//Ϊ�¹˿�ȷ����Ѷ��У��������
int bestWindow(Queue<Customer> windows[], int nWin)
{
	int minSize = windows[0].size(), optiWin = 0;
	for(int i = 1 ; i < nWin ; i++)
	{
		//�����д�����
		if(minSize > windows[i].size())
		{
			minSize = windows[i].size();
			optiWin = i;
		}
	}
	return optiWin;
}

//��ָ����������������ʱ��ģ������ҵ��
void simulate(int nWin, int servTime)
{
	//ÿ�����ڴ���һ������
	Queue<Customer> *windows = new Queue<Customer>[nWin];
	for(int now = 0 ; now < servTime ; now++)
	{
		if(rand() % (1 + nWin))
		{
			Customer c;
			//�¹˿͵������ʱ�����ȷ��
			c.time = 1 + rand() % 98;
			c.window = bestWindow(windows, nWin);
			windows[c.window].enqueue(c);
		}

	}
	for(int i = 0 ; i< nWin ; i++)
	{
		if(!windows[i].empty())
		{
			if(--windows[i].front().time <= 0)
			{
				windows[i].dequeue();
			}
		}
	}
	delete[] windows;
}

//����Ԫ�ص���
	//�ܿ��£������ں���������ʹ��ģ�壬�Ǹ���ջ�����������������ͱ��֣�
	//��������Ĭ��Ϊint��
//��Ȼ�Ǽ̳У��������ﻹ����Ҫ��queue��������һ�£�
template <typename T>
void Queue<T>::reverse()
{
	Stack<int> s;
	while(!empty())
	{
		s.push(dequeue());
	}
	while(!s.empty())
	{
		enqueue(s.pop());
	}
}
