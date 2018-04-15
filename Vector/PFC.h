#pragma once
#include "BinTree.h"
#include "Vector.h"
#include "Bitmap.h"
#include "Skiplist.h"
typedef BinTree<char> PFCTree;

typedef Vector<PFCTree *> PFCForest;

//PFC编码表，词条格式为：（key = 字符， value = 编码串）
typedef Skiplist<char, char*> PFCTable;

//只考虑可打印字符？
#define N_CHAR (0x80 - 0x20)

//PFC编码森林初始化
PFCForest *initForest();
PFCTree *generateTree(PFCForest *forest);
void generateCT
	(Bitmap *code, int length, PFCTable *table, BinNodePosi(char) v);
int encode(PFCTable *table, Bitmap &codeString, char* s);
void decode(PFCTree *tree, Bitmap& code, int n);
PFCTable *generateTable(PFCTree *tree);

//创建N_CHAR个只含有一个节点的树的森林
PFCForest *initForest()
{
	//创建N_CHAR范围内的每个合法字符的只有一个根节点的二叉树
	PFCForest* forest = new PFCForest;
	//创建一课对应的PFC编码树，初始其中只包含对应的一个节点
	for(int i = 0 ; i < N_CHAR ; i++)
	{
		forest->insert(i, new PFCTree());
		(*forest)[i]->insertAsRoot(0x20 + i);
	}
	return forest;
}

//按照随机组合的策略，把之前的N_CAHR棵子树合为一棵
PFCTree *generateTree(PFCForest *forest)
{
	srand((unsigned int)time(NULL));
	while(1 < forest->size())
	{
		PFCTree *s = new PFCTree;
		//不明白这里为什么要选择'^'，不过没啥影响
		s->insertAsRoot('^');
		Rank r1 = rand() % forest->size();
		s->attachAsLC(s->root(), (*forest)[r1]);
		forest->remove(r1);
	
		Rank r2 = rand() % forest->size();
		//错误：原来这里是attachAsLC
		s->attachAsRC(s->root(), (*forest)[r2]);
		forest->remove(r2);
		//合并后的重新进入森林
		forest->insert(forest->size(), s);
	}
	return (*forest)[0];
}


//生成PFC编码表

//通过遍历获取各个字符的编码
void generateCT
	(Bitmap *code, int length, PFCTable *table, BinNodePosi(char) v)
{
	if(IsLeaf(*v))
	{
		table->put(v->data, code->bits2string(length));
		return ;
	}
	//深度优先遍历的过程，遇到叶子节点就停止，把当前bitmap存储的路劲转化为字符串，保存到skiplist中
	//length记录当前节点的深度
	if(HasLChild(*v))
	{
		code->clear(length);
		generateCT(code, length + 1, table, v->lc);
		//这里不return
	}
	if(HasRChild(*v))
	{
		code->set(length);
		generateCT(code, length + 1, table, v->rc);
	}
}

//生成编码表:初始化table，位图，执行generateCT
PFCTable *generateTable(PFCTree *tree)
{
	PFCTable *table = new PFCTable;
	Bitmap *code = new Bitmap;
	generateCT(code, 0, table, tree->root());
	return table;
}
//查编码表，把s的每一个字符都转化为位图中的标志位，最后返回编码后的长度
int encode(PFCTable *table, Bitmap &codeString, char* s)
{
	int n = 0;
	//对于明文s[]中的每个字符
	for(size_t m = strlen(s), i = 0 ; i < m ; i++)
	{
		//取出其对应的编码串
		char **pCharCode = table->get(s[i]);
		//这里不太理解？table已经存好了0x20 - 0x80的每个字符的编码了，为什么pCharCode还可能为NULL？
		//而且不管是小写还是大写都在这个范围内啊
		if(!pCharCode)
			pCharCode = table->get(s[i] + 'A' - 'a');
		//无法识别的字符统一视作空格
		if(!pCharCode)
			pCharCode = table->get(' ');
		if(!(pCharCode))
		{
			std::cout << "空" << std::endl;
		}
		printf("%s", *pCharCode);
		for(size_t m = strlen(*pCharCode), j = 0 ; j < m ; j++)
			'1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
	}
	return n;
}
//给你编码树，编码后的位图，编码后的长度，输出解码后的字符

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