#pragma once
#include "stdafx.h"
#include "List.h"
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

};

//银行服务模拟
struct Customer
{
	//所属窗口
	int window;
	//服务时长
	unsigned int time;
};

//为新顾客确定最佳队列，最短优先
int bestWindow(Queue<Customer> windows[], int nWin)
{
	int minSize = windows[0].size(), optiWin = 0;
	for(int i = 1 ; i < nWin ; i++)
	{
		//在所有窗口中
		if(minSize > windows[i].size())
		{
			minSize = windows[i].size();
			optiWin = i;
		}
	}
	return optiWin;
}

//按指定窗口数，服务总时间模拟银行业务
void simulate(int nWin, int servTime)
{
	//每个窗口创建一个队列
	Queue<Customer> *windows = new Queue<Customer>[nWin];
	for(int now = 0 ; now < servTime ; now++)
	{
		if(rand() % (1 + nWin))
		{
			Customer c;
			//新顾客到达，服务时长随机确定
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

