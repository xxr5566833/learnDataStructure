#pragma once
#include "stdafx.h"
#include "Stack.h"

struct Queen{
	//�ʺ��������ϵ�����
	int x, y;
	Queen(int xx = 0, int yy = 0)
	{
		x = xx;
		y = yy;
	}
	//�����еȲ�������������ζ�ų�ͻ
	bool operator==(Queen const &q)const
	{
		return q.x == x || q.y == y || (q.x - x == q.y - y) || (q.x - x == y - q.y);
	}

	bool operator!=(Queen const &q)const
	{
		return !(*this == q);
	}

};


//N�ʺ��㷨�������棩��ʹ��ջ��¼���ҵĽ��
void placeQueens(int N)
{
	Stack<Queen> solu;
	int count = 0;
	//����������֮ǰ��������
	//q��ʾ��ǰҪȷ��λ�õĻʺ�
	Queen q = Queen(0, 0);
	do{
		//�����ж�q�Ƿ���Է��ڸ�λ�á�flagΪtrue��ʾ���ܷ����г�ͻ����λ�÷Ƿ���flagΪfalse��ʾ���Է���
		//������ԣ���ô��������ջ�У���������һ���ʺ��λ��
		//������У���ô�����ƶ�������Ѿ��ڱ�Ե����ô�о���ǰջ���ʺ�����λ���ƶ�
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
				//�ûʺ��Ѿ��������ƶ���
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
			//˵������ʺ��λ�ÿ��У���ô����solu
			solu.push(q);
			if(q.y == N - 1)
			{
				//�Ѿ������һ�У���ô�������ÿһ�еĻʺ������
				std::cout << "��" << count++ << "�ֽⷨ\n";
				for(int i = 0 ; i < N ; i++)
				{
					std::cout << solu[i].x << " " << std::endl;
				}
				std::cout << std::endl;
				//һֱ����⣬Ϊʲô�������ҵ����Ժ�û�����κεĲ�����������ȴû���ظ������
				//ԭ���Ǽ����ͻ���Ǹ�ѭ���q��ʱ�������һ�е�Ԫ�أ�������Ҳ�����뵽��ջ�У�����q�����Լ���ͻ�ˣ�����Ϊ�˱�֤��������ԣ�
				//���ﻹ�Ǵ���һ��
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

