#pragma once
#include <limits>
#include "Stack.h"
typedef enum{
	UNDISCOVERED,
	DISCOVERED,
	VISITED
}VStatus;//顶点状态

typedef enum{
	UNDETERMINED,
	TREE,
	CROSS,
	FORWARD,
	BACKWARD
}EType;//边在遍历树中所属的类型
template<typename Tv, typename Te>
class Graph{
public:
	//所有顶点，边的辅助信息复位
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

	void BFS(int, int&);	//(连通域)广度优先搜索算法
	void DFS(int, int&);	//(连通域)深度优先搜索算法
	void BCC(int, int&, Stack<int>&);	//(连通域)基于DFS的双连通分量分解算法
	bool TSort(int, int&, Stack<Tv>*);	//(连通域)基于DFS的拓扑排序算法
	template<typename PU> void PFS(int, PU);		//(连通域)优先级搜索框架

	//顶点
	int n;	//顶点总数
	//告诉编译系统这是一个纯虚函数
	virtual int insert(Tv const&) = 0;	//插入顶点，返回编号
	virtual Tv remove(int) = 0;			//删除顶点及其关连边，返回该顶点信息
	virtual Tv& vertex(int) = 0;		//顶点v的数据
	virtual int inDegree(int) = 0;		//顶点v的入度
	virtual int outDegree(int) = 0;		//顶点v的出度
	virtual int firstNbr(int) = 0;		//顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0;	//顶点v的相对于顶点j的下一个邻接顶点
	virtual VStatus& status(int) = 0;	//顶点v的状态
	virtual int& dTime(int) = 0;		//顶点v的时间标签dTime
	virtual int& fTime(int) = 0;		//顶点v的时间标签fTime
	virtual int& parent(int) = 0;		//顶点v在遍历树中的父亲
	virtual int& priority(int) = 0;		//顶点v在遍历树中的优先级数

	//边
	int e;	//边总数
	virtual bool exists(int, int) = 0;	//边（u，v）是否存在
	virtual void insert(Te const&, int, int, int) = 0;	//在顶点v和顶点u之间插入权重为w的边e
	virtual Te remove(int, int) = 0;		//删除顶点v和u之间的边e，返回该边信息
	virtual EType& type(int, int) = 0;		//边(u,v)的类型
	virtual Te& edge(int, int) = 0;			//边(u,v)的数据
	virtual int& weight(int, int) = 0;		//该边的权重

	//算法
	void bfs(int);		//广度优先搜索算法
	void dfs(int);		//深度优先搜索算法
	void bcc(int);		//基于DFS的双连通分量分解算法
	Stack<Tv>* tSort(int);	//基于DFS的拓扑排序算法
	void prim(int);			//最小支撑树Prim算法
	void dijkstra(int);		//最短路径Dijkstra算法
	template<typename PU>	void pfs(int, PU);	//优先级搜索框架

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
	std::cout << "bfs遍历结束" << std::endl;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock)
{
	Queue<int> Q;
	//注意这里设置第一个顶点是discovered
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
		//当所有邻居都加入到队列中后，v被设置为visited
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
	//在递归的开始设置DISCOVERED状态，并开始访问
	std::cout << clock << ":开始访问" << vertex(v) << std::endl;
	status(v) = DISCOVERED;
	for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
	{
		switch(status(u))
		{
		case UNDISCOVERED:
			//u尚未发现，意味着支撑树可以在这里扩展
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			//u被发现但尚未访问完毕，应属于被后代指向的祖先
			type(v, u) = BACKWARD;
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
	std::cout << clock << ":结束访问" << vertex(v) << std::endl;

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
				//这里还要把S清空
				//如果有一个连通分量不是DAG那么就不能做拓扑排序
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
			//和dfs一样设置一下parent和tree
			parent(u) = v;
			type(v, u) = TREE;
			//一旦下一次递归结果为false，那么最后结果肯定是false
			if(!TSort(u, clock, S))
				return false;
			break;
		case DISCOVERED:
			//说明有环，因为后代又指向了祖先
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
			//遍历返回后，弹出栈中最后一个顶点——当前连通域的起点
			S.pop();
		}
	}while(s != (v = (++v) % n));
}
#define hca(x) (fTime(x))
template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int>& S){
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	//v被发现并入栈
	S.push(v);
	for(int u = firstNbr(v) ; u > -1 ; u = nextNbr(v, u))
	{
		switch(status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);
			//发现u通过后向边可以指向v的真祖先
			//dTime 可以认为是递归深度，或者说是树的层数了
			if(hca(u) < dTime(v))
				hca(v) = hca(v) < hca(u) ? hca(v) : hca(u);
			else{
				//u之后不能通过后向边连接到v的真祖先，那么一旦v断掉，那么u以下的树的顶点无法与v以上的顶点和v的其他分支顶点联系
				//那么说明以v为关节点（u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部）
				while(v != S.pop());
				S.push(v);
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			//为什么u不能为parent是因为无向图吗
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
	std::cout << "优先级遍历结束" << std::endl;
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
			//更新顶点w的优先级及其父节点
			prioUpdater(this, s, w);
		}
		
		for(int shortest = INT_MAX , w = 0 ; w < n ; w++)
		{
			//从尚未加入遍历树的顶点中
			if(status(w) == UNDISCOVERED)
			{
				//选出下一个
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
		//不能对任意的邻居设置优先级，就像之前加入队列那样，这里仅仅把UNDISCOVERED的设置优先级即可,所以DISCOVERED这个状态还是没用
		if(g->status(v) == UNDISCOVERED && g->priority(v) > g->priority(uk) + 1){
			//这里相当于设置每条边的权重都是1
			g->priority(v) = g->priority(uk) + 1;
			g->parent(v) = uk;	
			
		}
		
	}
};

template<typename Tv, typename Te>
struct DfsPU{
	//深度优先搜索可以认为是越晚被发现，越早visit，之前理解有误，以为优先级搜索可以确定“结束”访问的顺序，但是其实只能确定开始访问的顺序
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
		//只要有一个可以修改就返回
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
			//此时优先级数表示到Tk的距离
			if(g->priority(v) > g->weight(uk, v))
			{
				g->priority(v) = g->weight(uk, v);
				//这里parent不是设置了就不能改了，如果一旦在之后被选中，那么这个parent设置就是有效的，如果没被选中，parent就会被改
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
			//此时优先级表示到源点s的距离
			if(g->priority(v) > g->weight(uk, v) + g->priority(uk))
			{
				g->priority(v) = g->weight(uk, v) + g->priority(uk);
				g->parent(v) = uk;
			}
		}
	}
};