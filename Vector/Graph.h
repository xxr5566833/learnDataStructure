#pragma once
#include <limits>
#include "Stack.h"
typedef enum{
	UNDISCOVERED,
	DISCOVERED,
	VISITED
}VStatus;//����״̬

typedef enum{
	UNDETERMINED,
	TREE,
	CROSS,
	FORWARD,
	BACKWARD
}EType;//���ڱ�����������������
template<typename Tv, typename Te>
class Graph{
public:
	//���ж��㣬�ߵĸ�����Ϣ��λ
	void reset()
	{
		for(int i = 0 ; i < n ; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for(int j = 0 ; j < n ; j++)
			{
				if(exists(i, j))
					type(i, j) = UNDETERMINED;
			}
		}
	}

	void BFS(int, int&);	//(��ͨ��)������������㷨
	void DFS(int, int&);	//(��ͨ��)������������㷨
	void BCC(int, int&, Stack<int>&);	//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
	bool TSort(int, int&, Stack<Tv>*);	//(��ͨ��)����DFS�����������㷨
	template<typename PU> void PFS(int, PU);		//(��ͨ��)���ȼ��������

	//����
	int n;	//��������
	//���߱���ϵͳ����һ�����麯��
	virtual int insert(Tv const&) = 0;	//���붥�㣬���ر��
	virtual Tv remove(int) = 0;			//ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(int) = 0;		//����v������
	virtual int inDegree(int) = 0;		//����v�����
	virtual int outDegree(int) = 0;		//����v�ĳ���
	virtual int firstNbr(int) = 0;		//����v���׸��ڽӶ���
	virtual int nextNbr(int, int) = 0;	//����v������ڶ���j����һ���ڽӶ���
	virtual VStatus& status(int) = 0;	//����v��״̬
	virtual int& dTime(int) = 0;		//����v��ʱ���ǩdTime
	virtual int& fTime(int) = 0;		//����v��ʱ���ǩfTime
	virtual int& parent(int) = 0;		//����v�ڱ������еĸ���
	virtual int& priority(int) = 0;		//����v�ڱ������е����ȼ���

	//��
	int e;	//������
	virtual bool exists(int, int) = 0;	//�ߣ�u��v���Ƿ����
	virtual void insert(Te const&, int, int, int) = 0;	//�ڶ���v�Ͷ���u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0;		//ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType& type(int, int) = 0;		//��(u,v)������
	virtual Te& edge(int, int) = 0;			//��(u,v)������
	virtual int& weight(int, int) = 0;		//�ñߵ�Ȩ��

	//�㷨
	void bfs(int);		//������������㷨
	void dfs(int);		//������������㷨
	void bcc(int);		//����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int);	//����DFS�����������㷨
	void prim(int);			//��С֧����Prim�㷨
	void dijkstra(int);		//���·��Dijkstra�㷨
	template<typename PU>	void pfs(int, PU);	//���ȼ��������

};
template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
	
	reset();
	int v = s;int clock = 0;
	do{
		if(status(v) == UNDISCOVERED)
			BFS(v, clock);
	}while(s != (v = (++v) % n));
	std::cout << "bfs��������" << std::endl;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock)
{
	Queue<int> Q;
	//ע���������õ�һ��������discovered
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while(!Q.empty())
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
		{
			if(status(u) == UNDISCOVERED)
			{
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(v, u) = TREE;
				parent(u) = v;
			}else{
				type(v, u) = CROSS;
			}
		}
		//�������ھӶ����뵽�����к�v������Ϊvisited
		status(v) = VISITED;
		std::cout << vertex(v) << std::endl;
	}
	
}


template<typename Tv, typename Te>

void Graph<Tv, Te>::dfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do{
		if(status(v) == UNDISCOVERED)
			DFS(v, clock);
	}while(s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int s, int& clock)
{
	int v = s;
	dTime(v) = ++clock;
	//�ڵݹ�Ŀ�ʼ����DISCOVERED״̬������ʼ����
	std::cout << clock << ":��ʼ����" << vertex(v) << std::endl;
	status(v) = DISCOVERED;
	for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
	{
		switch(status(u))
		{
		case UNDISCOVERED:
			//u��δ���֣���ζ��֧����������������չ
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			//u�����ֵ���δ������ϣ�Ӧ���ڱ����ָ�������
			type(v, u) = BACKWARD;
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
	std::cout << clock << ":��������" << vertex(v) << std::endl;

}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s){
	reset();
	int v = s;
	int clock = 0;
	Stack<Tv> *S = new Stack<Tv>;
	do{
		if(status(v) == UNDISCOVERED)
		{
			if(!TSort(v, clock, S))
			{
				//���ﻹҪ��S���
				//�����һ����ͨ��������DAG��ô�Ͳ�������������
				while(!S->empty())
					S->pop();
				break;
			}
		}
	}while(s != (v = (++v % n)));
	return S;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv> *S)
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
	{
		switch(status(u))
		{
		case UNDISCOVERED:
			//��dfsһ������һ��parent��tree
			parent(u) = v;
			type(v, u) = TREE;
			//һ����һ�εݹ���Ϊfalse����ô������϶���false
			if(!TSort(u, clock, S))
				return false;
			break;
		case DISCOVERED:
			//˵���л�����Ϊ�����ָ��������
			type(v, u) = BACKWARD;
			return false;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
	S->push(vertex(v));
	return true;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s){
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do{
		if(status(s) == UNDISCOVERED)
		{
			BCC(s, clock, S);
			//�������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
			S.pop();
		}
	}while(s != (v = (++v) % n));
}
#define hca(x) (fTime(x))
template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int>& S){
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	//v�����ֲ���ջ
	S.push(v);
	for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
	{
		switch(status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);
			//����uͨ������߿���ָ��v��������
			//dTime ������Ϊ�ǵݹ���ȣ�����˵�����Ĳ�����
			if(hca(u) < dTime(v))
				hca(v) = hca(v) < hca(u) ? hca(v) : hca(u);
			else{
				//u֮����ͨ����������ӵ�v�������ȣ���ôһ��v�ϵ�����ôu���µ����Ķ����޷���v���ϵĶ����v��������֧������ϵ
				//��ô˵����vΪ�ؽڵ㣨u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ�����
				while(v != S.pop());
				S.push(v);
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			//Ϊʲôu����Ϊparent����Ϊ����ͼ��
			if(u != parent(v))
				hca(v) = hca(v) < dTime(u) ? hca(v) : dTime(u);
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}

	}
	status(v) = VISITED;
}
#undef hca

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
	reset();
	int v = s;
	do{
		if(status(v) == UNDISCOVERED)
		{
			PFS(v, prioUpdater);
		}
	}while(s != (v = (++v % n)));
	std::cout << "���ȼ���������" << std::endl;
}

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	std::cout << vertex(s) << std::endl;
	while(1)
	{
		for(int w = firstNbr(s) ; w > -1 ; w = nextNbr(s, w))
		{
			//���¶���w�����ȼ����丸�ڵ�
			prioUpdater(this, s, w);
		}
		
		for(int shortest = INT_MAX , w = 0 ; w < n ; w++)
		{
			//����δ����������Ķ�����
			if(status(w) == UNDISCOVERED)
			{
				//ѡ����һ��
				if(shortest > priority(w))
				{
					shortest = priority(w);
					s = w;
				}
			}
		}
		if(status(s) == VISITED)
			break;
		std::cout << vertex(s) << std::endl;
		status(s) = VISITED;
		type(parent(s), s) = TREE;
	}
}

template<typename Tv, typename Te>
struct BfsPU{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
		//���ܶ�������ھ��������ȼ�������֮ǰ����������������������UNDISCOVERED���������ȼ�����,����DISCOVERED���״̬����û��
		if(g->status(v) == UNDISCOVERED && g->priority(v) > g->priority(uk) + 1){
			//�����൱������ÿ���ߵ�Ȩ�ض���1
			g->priority(v) = g->priority(uk) + 1;
			g->parent(v) = uk;	
			
		}
		
	}
};

template<typename Tv, typename Te>
struct DfsPU{
	//�����������������Ϊ��Խ�����֣�Խ��visit��֮ǰ���������Ϊ���ȼ���������ȷ�������������ʵ�˳�򣬵�����ʵֻ��ȷ����ʼ���ʵ�˳��
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
		//ֻҪ��һ�������޸ľͷ���
		if(g->status(v) == UNDISCOVERED && g->priority(v) > g->priority(uk) - 1){
			g->priority(v) = g->priority(uk) - 1;
			g->parent(v) = uk;
			return ;
		}
		
	}
};

template<typename Tv, typename Te>
struct PrimPU{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if(status(v) == UNDISCOVERED)
		{
			//��ʱ���ȼ�����ʾ��Tk�ľ���
			if(g->priority(v) > g->weight(uk, v))
			{
				g->priority(v) = g->weight(uk, v);
				//����parent���������˾Ͳ��ܸ��ˣ����һ����֮��ѡ�У���ô���parent���þ�����Ч�ģ����û��ѡ�У�parent�ͻᱻ��
				g->parent(v) = uk;
			}
		}
	}
};

template<typename Tv, typename Te>
struct DijkstraPU{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if(status(v) == UNDISCOVERED)
		{
			//��ʱ���ȼ���ʾ��Դ��s�ľ���
			if(g->priority(v) > g->weight(uk, v) + g->priority(uk))
			{
				g->priority(v) = g->weight(uk, v) + g->priority(uk);
				g->parent(v) = uk;
			}
		}
	}
};