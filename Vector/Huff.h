#pragma once
#include "HuffChar.h"
#include "List.h"
#include "BinTree.h"
#include "Bitmap.h"
#include "HashTable.h"
#define HuffTree BinTree<HuffChar>

typedef List<HuffTree*> HuffForest;

typedef Bitmap HuffCode;

typedef HashTable<char, char*> HuffTable;

//˳������ַ���ͳ�Ƴ��ֵĴ���
int *statistics(char *text)
{
	int *freq = new int[N_CHAR];
	memset(freq, 0, sizeof(int) * N_CHAR);
	FILE *fp = fopen(text, "r");
	for(char ch ; 0 < fscanf(fp, "%c", &ch) ; )
	{
		//ch��С��0x80
		if(ch >= 0x20)
			freq[ch - 0x20]++;
	}
	fclose(fp);
	return freq;
}

HuffForest *initForest(int *freq)
{
	HuffForest *forest = new HuffForest;
	for(int i = 0 ; i < N_CHAR ; i++)
	{
		HuffTree *tree = new HuffTree();
		tree->insertAsRoot(HuffChar(0x20 + i, freq[i]));
		forest->insertAsLast(tree);
	}
	return forest;
}
//��forest���ҳ�Ȩ����С�ĳ��ַ�������������������������ɾ��
HuffTree *minChar(HuffForest *forest)
{
	ListNodePosi(HuffTree *) p = forest->first();
	ListNodePosi(HuffTree *) minChar = p;
	int minWeight = p->data->root()->data.weight;
	p = p->succ;
	while(forest->valid(p))
	{
		if(p->data->root()->data.weight < minWeight)
		{
			minWeight = p->data->root()->data.weight;
			minChar = p;
		}
		p = p->succ;
	}
	return forest->remove(minChar);
}

//Huffman������
HuffTree *generateTree(HuffForest *forest)
{
	while(1 < forest->size())
	{
		HuffTree *t1 = minChar(forest);
		HuffTree *t2 = minChar(forest);
		HuffTree *s = new HuffTree;
		s->insertAsRoot(HuffChar('^', t1->root()->data.weight + t2->root()->data.weight));
		s->attachAsLC(s->root(), t1);
		s->attachAsRC(s->root(), t2);
		//ͻȻ�о�֮ǰ�б�API�з���ֵ�����ǲ�������data��ʵͦ�����
		forest->insertAsLast(s);
	}

	return forest->first()->data;
}

static void generateCT(Bitmap *code, int length, HuffTable *table, BinNodePosi(HuffChar) v)
{
	if(IsLeaf(*v))
	{
		table->put(v->data.ch, code->bits2string(length));
		return ;
	}
	if(HasLChild(*v))
	{
		//����ǵð���Ӧ��־λ����һ��
		code->clear(length);
		generateCT(code, length + 1, table, v->lc);
	}
	if(HasRChild(*v))
	{
		code->set(length);
		generateCT(code, length + 1, table, v->rc);
	}
}

HuffTable *generateTable(HuffTree *tree)
{
	HuffTable *table = new HuffTable;
	Bitmap *code = new Bitmap;
	generateCT(code, 0, table, tree->root());
	delete code;
	return table;
}

int encode(HuffTable *table, Bitmap *codeString, char *s)
{
	int n = 0;
	for(int m = strlen(s), int i = 0 ; i < m ; i ++)
	{
		char **pCharCode = table->get(s[i]);
		if(!pCharCode)
			pCharCode = table->get(s[i] + 'A' - 'a');
		if(!pCharCode)
			pCharCode = table->get(' ');
		printf("%s", *pCharCode);
		for(size_t m = strlen(*pCharCode), j = 0 ; j < m ; j++)
		{
			'1' == (*pCharCode)[j] ? codeString->set(n++) : codeString->clear(n++);
		}
	}
	printf("\n");
	return n;
}

void decode(HuffTree *tree, Bitmap *code, int n)
{
	BinNodePosi(HuffChar) x = tree->root();
	for(int i = 0 ; i < n ; i++)
	{
		//ע���Ȱ��յ�ǰ���룬ȷ��x����һ��λ�ã�Ȼ���ж�x�ǲ���Ҷ�ӽڵ�
		x = code->test(i) ? x->lc : x->rc;
		if(IsLeaf(*x))
		{
			printf("%c", x->data.ch);
			x = tree->root();
		}
	}
}