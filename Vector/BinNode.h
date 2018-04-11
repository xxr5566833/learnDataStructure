#pragma once
#include "stdafx.h"

//�������ڵ�ģ����
#define BinNodePosi(T) BinNode<T>*
//�ڵ�߶ȣ�������߶�Ϊ-1��Լ����ͳһ
#define stature(p)	((p) ? (p)->height : -1)
//�ڵ���ɫ
typedef enum {RB_RED, RB_BLACK}	RBColor;


/*

*BinNode ״̬�����ʵ��ж�*

*/
#define IsRoot(x) ((x).parent == NULL)
#define IsLChild(x)	(!IsRoot(x) && (& (x).parent->lc == (x)))
#define IsRChild(x) (!IsRoot(x) && (& (x).parent->rc == (x)))
#define HasParent(x)	((x).parent != NULL)
#define HasLChild(x)	((x).lc != NULL)
#define HasRChild(x)	((x).rc != NULL)
#define HasChild(x)		(HasLChild(x) || HasRChild(x))
#define HasBothChild(x)	(HasLChild(x) && HasRChild(x))
#define IsLeaf(x)	(!HasChild(x))

/*

*��BinNode�����ض���ϵ�Ľڵ��ָ��*

*/

#define sibling(p) (IsLChild(* (p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x)	(sibling((x)->parent))
//���Ը��׵�����
#define FromParentTo(x)	(IsRoot(x) ? _root : (IsLChild(x) ? (x)->parent->lc : (x)->parent->rc))



template<typename T>
struct BinNode{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;
	int height;
	//Null Path Length�����϶ѣ�Ҳ����ֱ����height���棩
	int npl;
	//��ɫ�������
	RBColor color;

	//���캯��
	BinNode():
	parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED):
	data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)	{}


	//�����ӿ�
	//ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	int size();
	//������ͺ���֮ǰ��˫�������ʵ���ˣ�
	//��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi(T) insertAsLC(T const &);
	//��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const &);
	//ȡ��ǰ�ڵ��ֱ�Ӻ�̣���ָ֮ǰд�������������ֱ�Ӻ���𣿣�
	BinNodePosi(T) succ();
	//������α���
	template<typename VST>	void travLevel(VST &);
	//ǰ�����
	template<typename VST>	void travPre(VST &);
	//�������
	template<typename VST>	void travIn(VST &);
	//�������
	template<typename VST>	void travPost(VST &);

	//�Ƚ������е���
	bool operator<(BinNode const &bn)	{return data < bn.data;}
	bool operator==(BinNode const &bn)	{return data == bn.data;}
	bool operator<=(BinNode const &bn)	{return data <= bn.data;}
	bool operator>(BinNode const &bn)	{return data > bn.data;}
	bool operator>=(BinNode const &bn)	{return data >= bn.data;}
	bool operator!=(BinNode const &bn)	{return data != bn.data;}

};

//���뺢�ӽڵ㣬Լ���ڲ���ǰû����Ӧ���ӽڵ�
template<typename T>
BinNodePosi(T)	BinNode<T>::insertAsLC(T const &e)
{
	//�߶ȣ�
	return lc = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T)	BinNode<T>::insertAsRC(T const &e)
{
	return rc = new BinNode(e, this);
}

template<typename T>
//������



template<typename VST>
void BinNode<T>::travIn(VST &visit)
{
	//��������������㷨ͳһ���
	switch(rand() % 5)
	{
	case 1:travIn_I1(this, visit); break;
	case 2:travIn_I2(this, visit);	break;
	case 3:travIn_I3(this, visit);	break;
	case 4:travIn_I4(this, visit);	break;
	default:	travIn_R(this, visit);	break;
	}
}
//�������������Ȼ��4�ֵ��������Ҽǵ���֮ǰҲ��2�֣�



