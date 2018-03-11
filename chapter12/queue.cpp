#include "stdafx.h"

int queue[50] = {0};
int length = 10;
int head = 0;
int tail = 0;

//队列只能满足n-1个元素
/*int enqueue(int key)
{
	if(head == (tail + 1) % length)
	{
		std::cout << "队列为满" << std::endl;
		return -1;
	}
	queue[tail] = key;
	tail = (tail + 1) % length;
}

int dequeue()
{
	if(head == tail)
	{
		std::cout << "队列为空" << std::endl;
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


