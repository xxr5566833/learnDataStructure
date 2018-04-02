#include "stdafx.h"


/*
int findMaxSubarray(int a[], int left, int right, int *maxleftindex, int *maxrightindex)
{
	if(left == right)
	{
		*maxleftindex = *maxrightindex = left;
		return a[left];
	}
	else{
		int mid = (left + right) / 2;
		int lefti, leftj;
		int leftval = findMaxSubarray(a, left, mid, &lefti, &leftj);
		int righti, rightj;
		int rightval = findMaxSubarray(a, mid + 1, right, &righti, &rightj);
		int leftindex = mid;
		int leftsum = 0;
		int leftmax = -10000000;
		int rightindex = mid + 1;
		int rightsum = 0;
		int rightmax = -10000000;
		for(int i = mid ; i >= left ; i --)
		{
			leftsum += a[i];
			if(leftsum > leftmax)
			{
				leftmax = leftsum;
				leftindex = i;
			}
		}
		for(int j = mid + 1; j <= right ; j++)
		{
			rightsum += a[j];
			if(rightsum > rightmax)
			{
				rightmax = rightsum;
				rightindex = j;
			}
		}
		int crosssum = rightmax + leftmax;
		if(crosssum > leftval)
		{
			if(crosssum > rightval)
			{
				*maxleftindex = leftindex;
				*maxrightindex = rightindex;
				return crosssum;
			}
			else{
				*maxleftindex = righti;
				*maxrightindex = rightj;
				return rightval;
			}
		}
		else{
			if(rightval > leftval)
			{
				*maxleftindex = righti;
				*maxrightindex = rightj;
				return rightval;
			}
			else{
				*maxleftindex = lefti;
				*maxrightindex = leftj;
				return leftval;
			}
		}
	}
}
//这里是错误的，动态规划的[0, i]的子问题f(i)表示的是以i为结尾的子数组的最大的和，而不是[0,i]这个数组内最大的子数组的和
//之前的理解是错误的
int findMaxSubarray2(int a[], int size, int *maxindexi, int *maxindexj)
{
	int max = 0x80000001;
	int sum = 0;
	for(int i = 0 ; i < size ; i++)
	{
		int sumj = 0;
		int indexj = -1;
		int maxj = 0x80000001;
		for(int j = i ; j >= 0 ; j--)
		{
			sumj += a[j];
			if(sumj > maxj)
			{
				maxj = sumj;
				indexj = j;
			}
		}
		if(maxj > max)
		{
			*maxindexi = indexj;
			*maxindexj = i;
			max = maxj;
		}
	}
	return max;
}

inline int parent(int i)
{
	return (i + 1) >> 1 < 1 ? 0 : ((i + 1) >> 1) - 1;
}

inline int left(int i)
{
	return ((i + 1) << 1) - 1;
}

inline int right(int i)
{
	return (i + 1) << 1;
}

void maxHeapify(int a[], int heapsize, int index)
{
	while(1)
	{
		int largest = index;
		int l = left(index);
		int r = right(index);
		if(l < heapsize && a[l] > a[index])
		{
			largest = l;
		}
		if(r < heapsize && a[r] > a[largest])
		{
			largest = r;
		}
		if(largest != index)
		{
			a[largest] = a[largest] ^ a[index];
			a[index] = a[largest] ^ a[index];
			a[largest] = a[largest] ^ a[index];
			index = largest;
		}
		else{
			break;
		}
	}
}

void buildMaxHeap(int a[], int size)
{
	for(int i = ((size >> 1)- 1) ; i >= 0 ; i -- )
	{
		maxHeapify(a, size, i);
	}
}
//exchange就不需要另外一个数组了
void heapsort(int a[], int size)
{
	buildMaxHeap(a, size);
	for(int i = size - 1; i >= 1 ; i--)
	{
		a[0] = a[0] ^ a[i];
		a[i] = a[0] ^ a[i];
		a[0] = a[0] ^ a[i];
		maxHeapify(a, i, 0);
	}
}

int maximum(int a[])
{
	return a[0];
}

int heapExtractMax(int a[], int size)
{
	if(size < 1)
	{
		std::cout << "heap size err" << std::endl;
		return -1;
	}
	int max = a[0];
	a[0] = a[size - 1];
	size -= 1;
	maxHeapify(a, size, 0);
	return max;

}

void heapIncreaseKey(int a[], int size, int index, int key)
{
	if(index >= size || key < a[index])
	{
		std::cout << "err" <<std::endl;
	}
	a[index] = key;
	while(index != 0 && a[parent(index)] < a[index])
	{
		int par = parent(index);
		a[par] = a[par] ^ a[index];
		a[index] = a[par] ^ a[index];
		a[par] = a[par] ^ a[index];
		index = par;
	}
}

void maxHeapInsert(int a[], int size, int key)
{
	a[size + 1] = 0x80000001;
	heapIncreaseKey(a, size + 1, size, key);
}




typedef struct Node2{
	int key;
	struct Node2 *next;
	struct Node2 *prev;
}node2;

node2 *NIL;


void insert(int key)
{
	node2 *n = new node2();
	n->key = key;
	
	NIL->next->prev = n;
	n->prev = NIL;
	n->next = NIL->next;
	NIL->next = n;
}

void init()
{
	NIL = new node2();
	NIL->next = NIL;
	NIL->prev = NIL;
}

bool isEmpty()
{
	return NIL->next == 0;
}
//search时不需要检查是否是NIL，只需要把NIL的key域设置为要search的key，然后只需要检查key是否和要search的key相同即可
//循环时，会从NIL的下一个开始，所以只有再重新开始循环时才会遇到NIL
node2 *search(int key)
{
	for(node2 *n = NIL->next ; n != NIL ; n = n -> next)
	{
		if(n->key == key)
		{
			return n;
		}
	}
	return 0;
}

node2 *del(node2 *n)
{
	n->next->prev = n ->prev;
	n->prev->next = n->next;
	return n;
	
}

void converse()
{
	node2 *end = NIL->prev;
	node2 *n = NIL->next;
	NIL->next = end;
	while(n != end)
	{
		node2 *next = n->next;
		n->next = end->next;
		end->next->prev = n;
		end->next = n;
		n->prev = end;
		n = next;

	}

}
typedef struct singleNode{
	int key;
	struct singleNode *next;
}sNode;

sNode *HEAD = 0;


int main(int argc, char *argv[])
{
	int a[10] = {1, 2, 3, 4, 5, 6};
	root = new bTree();
	root->key = 84;
	root->left = new bTree();
	root->left->key = 20;
	root->left->left = new bTree();
	root->left->left->left = 0;
	root->left->left->right = 0;
	root->left->left->key = 12;
	root->left->right = new bTree();
	root->left->right->left = 0;
	root->left->right->right = 0;
	root->left->right->key = 8;

	root->right = new bTree();
	root->right->key = 64;
	root->right->left = 0;
	root->right->right = 0;

	traversal2();
}*/