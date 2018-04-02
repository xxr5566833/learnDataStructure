#include "stdafx.h"
//带头结点的双向循环链表
typedef struct doubleLinkedList
{
	struct doubleLinkedList *rlink;
	struct doubleLinkedList *llink;
	int key;
}dNode;

dNode *head = 0;
//初始化头结点
/*void init()
{
	head = new doubleLinkedList();
	head->llink = head;
	head->rlink = head;
	head->key = -1;
}*/
//清华大学数据结构2.19，改造一个带头结点的双向链表，所有节点的原有次序保持在各个节点的rLink域中
//利用lLink域把所有节点按照其值从小到大的顺序链接起来
void transform(dNode *head)
{
	return ;
}