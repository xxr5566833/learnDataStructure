#include "stdafx.h"
//带头结点NIL的单向链表的相关操作
//这个待补充，仅仅是脑子里想了一遍，有时间自己实现一下原来单链表的每一种方法，仔细体会其中的不同
typedef struct headnode
{
	int key;
	struct headnode *next;
}HeadNode;
HeadNode *nil = 0;

void init()
{
	//需要初始化这个NIL头结点
	if(!nil)
	{
		nil = new HeadNode();
		nil->key = 0;
		nil->next = 0;
	}
}
//有了NIL头结点，插入不需要检查，当然必须保证n的合法性
void insert(HeadNode *n, int key)
{
	//插入到n后面，n一定是在以NIL为头结点的链表里
	HeadNode *newnode = new HeadNode();
	newnode->key = key;
	newnode->next = n->next;
	n->next = newnode;
}
