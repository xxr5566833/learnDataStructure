#include "stdafx.h"
//��ͷ���NIL�ĵ����������ز���
//��������䣬����������������һ�飬��ʱ���Լ�ʵ��һ��ԭ���������ÿһ�ַ�������ϸ������еĲ�ͬ
typedef struct headnode
{
	int key;
	struct headnode *next;
}HeadNode;
HeadNode *nil = 0;

void init()
{
	//��Ҫ��ʼ�����NILͷ���
	if(!nil)
	{
		nil = new HeadNode();
		nil->key = 0;
		nil->next = 0;
	}
}
//����NILͷ��㣬���벻��Ҫ��飬��Ȼ���뱣֤n�ĺϷ���
void insert(HeadNode *n, int key)
{
	//���뵽n���棬nһ��������NILΪͷ����������
	HeadNode *newnode = new HeadNode();
	newnode->key = key;
	newnode->next = n->next;
	n->next = newnode;
}
