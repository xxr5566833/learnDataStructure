#pragma once
#include "Graph.h"
#include "Vector.h"
#include "Queue.h"
template<typename Tv>
struct Vertex{
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;
	//在遍历树中的父节点，优先级数
	int parent;
	int priority;
	Vertex(Tv const& d = (Tv) 0):
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
			dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}

};

template<typename Te>
struct Edge{
	Te data;
	int weight;
	EType type;
	Edge(Te const& d, int w):
	data(d), weight(w), type(UNDETERMINED){}
};
//顶点类型，边类型
template<typename Tv, typename Te>
class GraphMatrix:public Graph<Tv, Te>
{
public:
	//顶点集（向量）
	Vector<Vertex<Tv>>	V;
	//边集（邻接矩阵）
	Vector<Vector<Edge<Te> *>> E;

	GraphMatrix(){n = e = 0;}
	~GraphMatrix(){
		for(int j = 0 ; j < n ; j++)
		{
			for(int k = 0 ; k < n ; k++)
			{
				delete E[j][k];
			}
		}
	}

	//顶点的基本操作：查询第i个顶点
	virtual Tv& vertex(int i){return V[i].data ;}
	virtual int inDegree(int i){return V[i].inDegree;}
	virtual int outDegree(int i){return V[i].outDegree;}
	virtual int firstNbr(int i){return nextNbr(i, n);}
	virtual int nextNbr(int i, int j)//相对于顶点j的下一个邻接顶点
	{
		while((-1 < j) && (!exists(i, --j)));
		return j;
	}
	virtual VStatus& status(int i)
	{
		return V[i].status;
	}
	virtual int& dTime(int i)
	{
		return V[i].dTime;
	}
	virtual int& fTime(int i)
	{
		return V[i].fTime;
	}
	virtual int& parent(int i)
	{
		return V[i].parent;
	}
	virtual int& priority(int i)
	{
		return V[i].priority;
	}

	//顶点的动态操作，插入顶点，返回编号
	virtual int insert(Tv const& vertex)
	{
		for(int j = 0 ; j < n ; j++)
		{
			E[j].insert(NULL);
		}
		n++;
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te> *)NULL));
		return V.insert(Vertex<Tv>(vertex));
	}
	//删除第i个顶点及其关联边
	virtual Tv remove(int i){
		for(int j = 0 ; j < n ; j++)
		{
			if(exists(i, j))
			{
				delete E[i][j];
				V[j].inDegree--;
			}
		}
		E.remove(i);
		n--;
		Tv vBak = vertex(i);
		V.remove(i);
		for(int j = 0 ; j < n ; j++)
		{
			if(Edge<Te> *e = E[j].remove(i)){
				delete e;
				V[j].outDegree--;
			}
		}
		return vBak;
	}

	//边的确认操作
	virtual bool exists(int i, int j)
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}

	virtual EType& type(int i, int j)
	{
		if(exists(i, j))
			return E[i][j]->type;
		std::cout << "边不存在" << std::endl;
		return E[i][j]->type;
	}
	virtual Te& edge(int i, int j)
	{
		return E[i][j]->data;
	}
	virtual int& weight(int i, int j)
	{
		return E[i][j]->weight;
	}

	//边的动态操作
	virtual void insert(Te const& edge, int w, int i, int j)
	{
		if(exists(i, j))	return ;
		E[i][j] = new Edge<Te>(edge, w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}

	virtual Te remove(int i, int j)
	{
		Te eBak = edge(i, j);
		delete E[i][j];
		E[i][j] = NULL;
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
	
};


