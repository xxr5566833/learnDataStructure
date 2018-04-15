#pragma once
#include "BinTree.h"
#include "Vector.h"
#include "Bitmap.h"
#include "Skiplist.h"
typedef BinTree<char> PFCTree;

typedef Vector<PFCTree *> PFCForest;

//PFC�����������ʽΪ����key = �ַ��� value = ���봮��
typedef Skiplist<char, char*> PFCTable;

//ֻ���ǿɴ�ӡ�ַ���
#define N_CHAR (0x80 - 0x20)

//PFC����ɭ�ֳ�ʼ��
PFCForest *initForest();
PFCTree *generateTree(PFCForest *forest);
void generateCT
	(Bitmap *code, int length, PFCTable *table, BinNodePosi(char) v);
int encode(PFCTable *table, Bitmap &codeString, char* s);
void decode(PFCTree *tree, Bitmap& code, int n);
PFCTable *generateTable(PFCTree *tree);

//����N_CHAR��ֻ����һ���ڵ������ɭ��
PFCForest *initForest()
{
	//����N_CHAR��Χ�ڵ�ÿ���Ϸ��ַ���ֻ��һ�����ڵ�Ķ�����
	PFCForest* forest = new PFCForest;
	//����һ�ζ�Ӧ��PFC����������ʼ����ֻ������Ӧ��һ���ڵ�
	for(int i = 0 ; i < N_CHAR ; i++)
	{
		forest->insert(i, new PFCTree());
		(*forest)[i]->insertAsRoot(0x20 + i);
	}
	return forest;
}

//���������ϵĲ��ԣ���֮ǰ��N_CAHR��������Ϊһ��
PFCTree *generateTree(PFCForest *forest)
{
	srand((unsigned int)time(NULL));
	while(1 < forest->size())
	{
		PFCTree *s = new PFCTree;
		//����������ΪʲôҪѡ��'^'������ûɶӰ��
		s->insertAsRoot('^');
		Rank r1 = rand() % forest->size();
		s->attachAsLC(s->root(), (*forest)[r1]);
		forest->remove(r1);
	
		Rank r2 = rand() % forest->size();
		//����ԭ��������attachAsLC
		s->attachAsRC(s->root(), (*forest)[r2]);
		forest->remove(r2);
		//�ϲ�������½���ɭ��
		forest->insert(forest->size(), s);
	}
	return (*forest)[0];
}


//����PFC�����

//ͨ��������ȡ�����ַ��ı���
void generateCT
	(Bitmap *code, int length, PFCTable *table, BinNodePosi(char) v)
{
	if(IsLeaf(*v))
	{
		table->put(v->data, code->bits2string(length));
		return ;
	}
	//������ȱ����Ĺ��̣�����Ҷ�ӽڵ��ֹͣ���ѵ�ǰbitmap�洢��·��ת��Ϊ�ַ��������浽skiplist��
	//length��¼��ǰ�ڵ�����
	if(HasLChild(*v))
	{
		code->clear(length);
		generateCT(code, length + 1, table, v->lc);
		//���ﲻreturn
	}
	if(HasRChild(*v))
	{
		code->set(length);
		generateCT(code, length + 1, table, v->rc);
	}
}

//���ɱ����:��ʼ��table��λͼ��ִ��generateCT
PFCTable *generateTable(PFCTree *tree)
{
	PFCTable *table = new PFCTable;
	Bitmap *code = new Bitmap;
	generateCT(code, 0, table, tree->root());
	return table;
}
//��������s��ÿһ���ַ���ת��Ϊλͼ�еı�־λ����󷵻ر����ĳ���
int encode(PFCTable *table, Bitmap &codeString, char* s)
{
	int n = 0;
	//��������s[]�е�ÿ���ַ�
	for(size_t m = strlen(s), i = 0 ; i < m ; i++)
	{
		//ȡ�����Ӧ�ı��봮
		char **pCharCode = table->get(s[i]);
		//���ﲻ̫��⣿table�Ѿ������0x20 - 0x80��ÿ���ַ��ı����ˣ�ΪʲôpCharCode������ΪNULL��
		//���Ҳ�����Сд���Ǵ�д���������Χ�ڰ�
		if(!pCharCode)
			pCharCode = table->get(s[i] + 'A' - 'a');
		//�޷�ʶ����ַ�ͳһ�����ո�
		if(!pCharCode)
			pCharCode = table->get(' ');
		if(!(pCharCode))
		{
			std::cout << "��" << std::endl;
		}
		printf("%s", *pCharCode);
		for(size_t m = strlen(*pCharCode), j = 0 ; j < m ; j++)
			'1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
	}
	return n;
}
//�����������������λͼ�������ĳ��ȣ�����������ַ�

void decode(PFCTree *tree, Bitmap& code, int n)
{
	BinNodePosi(char) x = tree->root();
	for(int i = 0 ; i < n ; i++)
	{
		x= code.test(i) ? x->rc : x->lc;
		if(IsLeaf(*x))
		{
			printf("%c", x->data);
			x = tree->root();
		}
	}
}