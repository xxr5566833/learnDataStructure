#pragma once
#include "stdafx.h"
#include "Stack.h"
//原始可用的，在当前路径上的，所有方向均尝试失败后回溯的，不可使用的（墙）
typedef enum{AVAILABLE, ROUTE, BACKTRACKED, WALL} Status;	//迷宫单元状态

//单元的相对邻接方向
typedef enum {UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;

inline ESWN nextESWN(ESWN eswn) {return ESWN(eswn + 1);}

struct Cell{
	int x, y;
	Status status;
	ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];//迷宫


//查询当前位置的相邻格点
inline Cell *neighbor(Cell *cell)
{
	switch(cell->outgoing)
	{
		//格点迷宫 竖直方向是x轴， 水平方向是y轴
	case EAST:	return cell + LABY_MAX;
	case SOUTH: return cell + 1;
	case WEST:	return cell - LABY_MAX;
	case NORTH:	return cell - 1;
	default:	exit(-1);
	}
}

//从当前位置转入相邻格点
inline Cell *advance(Cell *cell)
{
	Cell *next;
	switch(cell->outgoing)
	{
	case EAST:	next = cell + LABY_MAX;	next->incoming = WEST;	break;
	case SOUTH:	next = cell + 1;		next->incoming = NORTH;	break;
	case WEST:	next = cell - LABY_MAX;	next->incoming = EAST;	break;
	case NORTH:	next = cell - 1;		next->incoming = SOUTH;	break;
	default:	exit(-1);
	}
	return next;
}

//迷宫寻径算法：在单元格s至t之间规划一条通路（如果的确存在）
bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t)
{
	if((AVAILABLE != s->status) || (AVAILABLE != t->status))	return false;
	//线绳
	Stack<Cell *> path;
	s->incoming = UNKNOWN;
	//我觉得这里少了一个对outgoing的初始化
	s->outgoing = UNKNOWN;

	s->status = ROUTE;
	path.push(s);
	do{
		Cell *c = path.top();
		if(c == t)	return true;
		while(NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
			if(AVAILABLE == neighbor(c)->status)	break;
		if(NO_WAY <= c->outgoing)
		{
			c->status = BACKTRACKED;
			c = path.pop();
		}
		else{
			path.push(c = advance(c));
			c->outgoing = UNKNOWN;
			c->status = ROUTE;
		}
	}while(!path.empty());
	return false;
}