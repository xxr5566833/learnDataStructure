#include "stdafx.h"
//��ͷ����˫��ѭ������
typedef struct doubleLinkedList
{
	struct doubleLinkedList *rlink;
	struct doubleLinkedList *llink;
	int key;
}dNode;

dNode *head = 0;
//��ʼ��ͷ���
/*void init()
{
	head = new doubleLinkedList();
	head->llink = head;
	head->rlink = head;
	head->key = -1;
}*/
//�廪��ѧ���ݽṹ2.19������һ����ͷ����˫���������нڵ��ԭ�д��򱣳��ڸ����ڵ��rLink����
//����lLink������нڵ㰴����ֵ��С�����˳����������
void transform(dNode *head)
{
	return ;
}