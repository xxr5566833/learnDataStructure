#pragma once
#include "stdafx.h"
#include "Stack.h"

struct Queen{
	//皇后在棋盘上的坐标
	int x, y;
	Queen(int xx = 0, int yy = 0)
	{
		x = xx;
		y = yy;
	}
	//重载判等操作，等于则意味着冲突
	bool operator==(Queen const &q)const
	{
		return q.x == x || q.y == y || (q.x - x == q.y - y) || (q.x - x == y - q.y);
	}

	bool operator!=(Queen const &q)const
	{
		return !(*this == q);
	}

};


//N皇后算法（迭代版），使用栈记录查找的结果
void placeQueens(int N)
{
	Stack<Queen> solu;
	int count = 0;
	//让我想起了之前做的数独
	//q表示当前要确定位置的皇后
	Queen q = Queen(0, 0);
	do{
		//首先判断q是否可以放在该位置。flag为true表示不能放置有冲突或者位置非法，flag为false表示可以放置
		//如果可以，那么把它加入栈中，并搜索下一个皇后的位置
		//如果不行，那么向右移动，如果已经在边缘，那么研究当前栈顶皇后，让它位置移动
		int flag = q.x == N;
		for(int i = 0 ; i < solu.size() ; i++)
		{
			if(q == solu[i])
			{
				flag = true;
				break;
			}
		}
		
		if(flag)
		{
			
			if(q.x == N)
			{
				//该皇后已经不能在移动了
				if(solu.empty())
					break;
				q = solu.pop();
				q.x += 1;
				continue;
			}
			else{
				q.x = q.x + 1;
			}
		}
		else{
			//说明这个皇后的位置可行，那么加入solu
			solu.push(q);
			if(q.y == N - 1)
			{
				//已经是最后一行，那么这里输出每一行的皇后的列数
				std::cout << "第" << count++ << "种解法\n";
				for(int i = 0 ; i < N ; i++)
				{
					std::cout << solu[i].x << " " << std::endl;
				}
				std::cout << std::endl;
				//一直不理解，为什么这里在找到解以后没有做任何的操作，最后输出却没有重复输出？
				//原来是检验冲突的那个循环里，q当时还是最后一行的元素，而且它也被加入到了栈中，所以q和它自己冲突了，但是为了保证不会二义性，
				//这里还是处理一下
				q = solu.pop();
				q.x += 1;
			}
			else{
				Queen n = Queen(0, q.y + 1);
				q = n;
			}
		}

	}while(1);
}

