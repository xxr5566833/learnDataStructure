#include "stdafx.h"

int queue[50] = {0};
int length = 10;
int head = 0;
int tail = 0;

//����ֻ������n-1��Ԫ��
/*int enqueue(int key)
{
	if(head == (tail + 1) % length)
	{
		std::cout << "����Ϊ��" << std::endl;
		return -1;
	}
	queue[tail] = key;
	tail = (tail + 1) % length;
}

int dequeue()
{
	if(head == tail)
	{
		std::cout << "����Ϊ��" << std::endl;
		return 0x8000001;
	}
	int key = queue[head];
	head = head + 1;
	if(head == length)
	{
		head = 0;
	}
	return key;
	

}*/


